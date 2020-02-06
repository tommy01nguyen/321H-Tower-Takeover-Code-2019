#include "321Hlib/SystemControl/driveTask.h"

/**************************************************/
//Drive State Machine Methods
static driveStates currentdriveState = driveStates::tank; //Defaulted tank
double drivePercent = 1.0;

void setdriveState(driveStates newState){ //Set State of drive
  currentdriveState = newState;
}
void setdriveState(driveStates newState, double requestedPercent){
  currentdriveState = newState;
  drivePercent = requestedPercent;
}
/**************************************************/
//IMU PID
bool turnPIDOn = false;
double kp = 1.25;//.7
double kd = .1;//.1
static double turnTarget;
static double maxSpeed = 200;

double getImuHeading(){ //Convert 0-359 to 0-179, -179,-1
  return s_imu.get_rotation();
}

void reset(){
  turnTarget = 0;
  maxSpeed = 200;
  m_driveLF.tarePosition();
  m_driveLB.tarePosition();
  m_driveRF.tarePosition();
  m_driveRB.tarePosition();
  mg_driveR.moveVelocity(0);
  mg_driveL.moveVelocity(0);
}
//
// //slew control
// const int accel_step = 9;
// const int deccel_step = 256; // no decel slew
// static int leftSpeed = 0;
// static int rightSpeed = 0;
//
// void leftSlew(int leftTarget){
//   int step;
//
//   if(abs(leftSpeed) < abs(leftTarget))
//     step = accel_step;
//   else
//     step = deccel_step;
//
//   if(leftTarget > leftSpeed + step)
//     leftSpeed += step;
//   else if(leftTarget < leftSpeed - step)
//     leftSpeed -= step;
//   else
//     leftSpeed = leftTarget;
//
//   mg_driveL.moveVelocity(leftSpeed);
// }
//
// void rightSlew(int rightTarget){
//   int step;
//
//   if(abs(rightSpeed) < abs(rightTarget))
//     step = accel_step;
//   else
//     step = deccel_step;
//
//   if(rightTarget > rightSpeed + step)
//     rightSpeed += step;
//   else if(rightTarget < rightSpeed - step)
//     rightSpeed -= step;
//   else
//     rightSpeed = rightTarget;
//
//   mg_driveR.moveVelocity(rightSpeed);
// }

void setSpeed(int speed){
  maxSpeed = speed;
}

bool isTurning(){

  static int count = 0;
  static double lastAngle = 0;
  static double lastTarget = 0;

  double curAngle = getImuHeading(); //CHANGE TO IMU VALUES************
  double target = turnTarget;

  if(abs(lastAngle-curAngle) < .01) //3 robot degree threshold for change in Angle NEEDS TUNING
    count++;
  else
    count = 0;

  if(target != lastTarget) //If changing target, restart iterating
    count = 0;

    std::cout << "lastAngle: " << lastAngle << std::endl;
    std::cout << "curAngle: " << curAngle << std::endl;
    std::cout << "count: " << count << std::endl;

  lastTarget = target;
  lastAngle = curAngle;


  if(count > 4) //If iterated 4 times
    return false; //Not Turning
  else
    return true; //Turning
}

// double headingToTarget(double heading){//Turn heading(degrees) into angle needed to travel
//   return heading;
// }

void turnTo(double newHeading){ //Heading in degrees (0,360)
    reset();

    // turnTarget = headingToTarget(newHeading);
    turnTarget = newHeading;
    setdriveState(driveStates::turnPID);
    turnPIDOn = true;

    pros::delay(300); //Assuming no super short turns
    while(isTurning()){ //Wait until settled
      setdriveState(driveStates::turnPID);
      pros::delay(20);
    }
    //Movement over
    setdriveState(driveStates::tank);
    std::cout << "turnTo Over!!" << std::endl;
    turnPIDOn = false;
}

/**************************************************/
//State Machine Task for Drive Control
void task_driveControl(void*){
  while(true){

    switch(currentdriveState){

      case driveStates::tank:{
        if(mg_driveR.getBrakeMode() == AbstractMotor::brakeMode::hold){ //Change from Hold to Coast
          mg_driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
          mg_driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
        }
        pidChassis->getModel()->tank(j_master.getAnalog(ControllerAnalog::leftY),
                                     j_master.getAnalog(ControllerAnalog::rightY));//Add threshold?
        break;
      }

      case driveStates::hold:{
        mg_driveR.setBrakeMode(AbstractMotor::brakeMode::hold);
        mg_driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
        mg_driveR.moveVelocity(0);
        mg_driveL.moveVelocity(0);
        break;
      }
      case driveStates::outOfStack:{
          mg_driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
          mg_driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
        setintakeState(intakeStates::on,-6000);
        pidChassis->moveDistance(-2_in);
        setintakeState(intakeStates::on, 0);
      }
      case driveStates::turnPID:{
        int prevError;

        while(turnPIDOn){
          double target = turnTarget;
          double current = getImuHeading();

          double error = target-current;
          double derivative = error - prevError;
          prevError = error;

          double speed = error*kp + derivative*kd;

          if(speed > maxSpeed)
            speed = maxSpeed;
          if(speed < -maxSpeed)
            speed = -maxSpeed;

          // std::cout << "turnTarget: " << target << std::endl;
          // std::cout << "rotation: " << current << std::endl;
          // std::cout << "error: " << error << std::endl;
          // std::cout << "speed: " << speed << std::endl;
          //PV 90, SV 360. //PV 270, SV 360
          // if(turnTarget > 180){
          //   speed = -speed;
          // }

          mg_driveL.moveVelocity(speed);
          mg_driveR.moveVelocity(-speed);
          // leftSlew(-speed);
          // rightSlew(speed);
          //std::cout << "PIDis on!" << std::endl;
          pros::delay(20);
          }

      }
    }
    pros::delay(20);
  }
}
