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

bool drivePIDOn = false;
double kpDrive = 1;
double kdDrive = .1;
static double driveTarget;

bool turnPIDOn = false;
double kp = 1.25;//.7
double kd = .1;//.1
static double turnTarget;

static double maxSpeed = 200;
static int yaw = 0; //Used for arcing

double getImuRotation(){ //()-infinity, infinity)
  return s_imu.get_rotation();
}

double getEncRotation(){
  return m_driveRB.getPosition();
}

double getDrivePos(){
  return (m_driveRB.getPosition() + m_driveLB.getPosition())/2;
}
double inchesToTicks(double inches){
  double rev = inches/3.1415/4;
  double ticks = rev * 360;
  return ticks;
}

void reset(){
  turnTarget = 0;
  driveTarget = 0;
  yaw = 0;
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
//   mg_driveL.moveVoltage(leftSpeed);
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
//   mg_driveR.moveVoltage(rightSpeed);
// }

void setMaxSpeed(int speed){
  maxSpeed = speed;
}
bool isTurning_encoder(){

  static int count = 0;
  static double lastPos = 0;
  static double lastTarget = 0;

  double curPos = getEncRotation();
  double target = turnTarget;
  if(currentdriveState == driveStates::drivePID){
    target = driveTarget;
  }

  if(abs(lastPos-curPos) < 3){ //3 robot degree threshold for change in Angle NEEDS TUNING
    count++;
  }
  else{
    count = 0;
  }

  if(target != lastTarget){ //If changing target, restart iterating
    count = 0;
  }

     // std::cout << "lastAngle: " << lastAngle << std::endl;
     // std::cout << "curAngle: " << curAngle << std::endl;
     // std::cout << "count: " << count << std::endl;

  lastTarget = target;
  lastPos = curPos;


  if(count > 4){ //If iterated 5 times
    return false; //Not Turning
  }
  else{
    return true; //Turning
  }
}

bool isTurning(){

  static int count = 0;
  static double lastPos = 0;
  static double lastTarget = 0;

  double curPos = getImuRotation();
  double target = turnTarget;
  if(currentdriveState == driveStates::drivePID){
    target = driveTarget;
  }

  if(abs(lastPos-curPos) < .05){ //3 robot degree threshold for change in Angle NEEDS TUNING
    count++;
  }
  else{
    count = 0;
  }

  if(target != lastTarget){ //If changing target, restart iterating
    count = 0;
  }

     // std::cout << "lastAngle: " << lastAngle << std::endl;
     // std::cout << "curAngle: " << curAngle << std::endl;
     // std::cout << "count: " << count << std::endl;

  lastTarget = target;
  lastPos = curPos;


  if(count > 4){ //If iterated 5 times
    return false; //Not Turning
  }
  else{
    return true; //Turning
  }
}

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
    //std::cout << "turnTo Over!!" << std::endl;
    turnPIDOn = false;
}

void drive(double distance, int speed){ //Inchess
  reset();
  setMaxSpeed(speed);
  driveTarget = inchesToTicks(distance);
  setdriveState(driveStates::drivePID);
  drivePIDOn = true;
  pros::delay(300);
  while(isTurning()){
    setdriveState(driveStates::drivePID);
    pros::delay(20);
  }
  setdriveState(driveStates::tank);
  drivePIDOn = false;
}

void drive(double distance, int speed, int yawInput){//Arc
  reset();
  yaw = yawInput;
  setMaxSpeed(speed);
  driveTarget = inchesToTicks(distance);
  setdriveState(driveStates::drivePID);
  drivePIDOn = true;
  pros::delay(300);
  while(isTurning()){
    setdriveState(driveStates::drivePID);
    pros::delay(20);
  }
  setdriveState(driveStates::tank);
  drivePIDOn = false;
}



//Two speed drive
void variableDrive(double distance, double dropDistance, int vi, int vf){
  reset();

  driveTarget = inchesToTicks(distance);
  int dropDistanceCP = inchesToTicks(dropDistance);
  setdriveState(driveStates::drivePID);
  drivePIDOn = true;

  //Drive at this speed until this point
  setMaxSpeed(vi);
  if(distance > 0){
    while(getDrivePos() < dropDistanceCP){
      pros::delay(20);
      setdriveState(driveStates::drivePID);
    }
  }
  else{
    while(getDrivePos() > dropDistanceCP) {
      pros::delay(20);
      setdriveState(driveStates::drivePID);
    }
  }

  //For 4 iterations, drive forward at high speed, slow down.. would need to implement slew control
  //for(int i = 0; i < 4; i++){
  //}

  //Drive at a slower speed
  setMaxSpeed(vf);
  while(isTurning()) {
    setdriveState(driveStates::drivePID);
    pros::delay(20);
  }
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
        pidChassis->getModel()->tank(j_master.getAnalog(ControllerAnalog::leftY)*drivePercent,
                                     j_master.getAnalog(ControllerAnalog::rightY)*drivePercent);//Add threshold?
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
          setintakeState(intakeStates::on,-12000);
          mg_driveR.moveVelocity(-30);
          mg_driveL.moveVelocity(-30);
      }
      case driveStates::drivePID:{
        int prevError;

        while(drivePIDOn){
          double target = driveTarget;
          double current = getEncRotation();

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


          mg_driveL.moveVelocity(speed + yaw);
          mg_driveR.moveVelocity(speed - yaw);
          // leftSlew(-speed);
          // rightSlew(speed);
          //std::cout << "PID is on!" << std::endl;
          pros::delay(20);
          }

      }
      case driveStates::turnPID:{
        int prevError;

        while(turnPIDOn){
          double target = turnTarget; //Set in turnTo method
          double current = getImuRotation();

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


          mg_driveL.moveVelocity(speed);
          mg_driveR.moveVelocity(-speed);
          // leftSlew(-speed);
          // rightSlew(speed);
          //std::cout << "PID is on!" << std::endl;
          pros::delay(20);
          }

      }
    }
    pros::delay(20);
  }
}
