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
//Dear 574C, thank you.
double kp = .1;
double kd = .1;
static double turnTarget;
static double maxSpeed = 200;

double getImuValue(){
  return 2.0;
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

//slew control
const int accel_step = 9;
const int deccel_step = 256; // no decel slew
static int leftSpeed = 0;
static int rightSpeed = 0;

void leftSlew(int leftTarget){
  int step;

  if(abs(leftSpeed) < abs(leftTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(leftTarget > leftSpeed + step)
    leftSpeed += step;
  else if(leftTarget < leftSpeed - step)
    leftSpeed -= step;
  else
    leftSpeed = leftTarget;

  mg_driveL.moveVelocity(leftSpeed);
}

void rightSlew(int rightTarget){
  int step;

  if(abs(rightSpeed) < abs(rightTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(rightTarget > rightSpeed + step)
    rightSpeed += step;
  else if(rightTarget < rightSpeed - step)
    rightSpeed -= step;
  else
    rightSpeed = rightTarget;

  mg_driveR.moveVelocity(rightSpeed);
}

void setSpeed(int speed){
  maxSpeed = speed;
}

bool isTurning(){
  static int count = 0;
  static int lastAngle = 0;
  static int lastTarget = 0;

  int curAngle = getImuValue(); //CHANGE TO IMU VALUES************
  int target = turnTarget;

  if(abs(lastAngle-curAngle) < 3) //3 degree encoder unit threshold for change in Angle NEEDS TUNING
    count++;
  else
    count = 0;

  if(target != lastTarget) //If changing target, restart iterating
    count = 0;

  lastTarget = target;
  lastAngle = curAngle;

  if(count > 4) //If iterated 4 times
    return false; //Not Turning
  else
    return true; //Turning
}

double headingToTarget(double heading){//Turn heading(degrees) into angle needed to travel
  return heading;
}

void turnTo(double newHeading){ //Heading in degrees
    reset();
    turnTarget = headingToTarget(newHeading);
    setdriveState(driveStates::turnPID);

    pros::delay(300); //Assuming no super short turns
    while(isTurning()){ //Wait until settled
      pros::delay(20);
    }
    //Movement over
    setdriveState(driveStates::tank);
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

      case driveStates::turnPID:{
        int prevError;

        while(1){
          double pv = turnTarget; //Process Variable  //Currently, PV and SV are not in the same units

          //convert pv into sv units or other way around
          double sv = getImuValue(); //Set Point Variable

          double error = pv-sv;
          double derivative = error - prevError;
          prevError = error;

          double speed = error*kp + derivative*kd;

          if(speed > maxSpeed)
            speed = maxSpeed;
          if(speed < -maxSpeed)
            speed = -maxSpeed;

          mg_driveL.moveVelocity(-speed);
          mg_driveR.moveVelocity(speed);
          // leftSlew(-speed);
          // rightSlew(speed);
          pros::delay(20);
          }

      }
    }
    pros::delay(20);
  }
}
