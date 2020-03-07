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
double kpDrive = .3; //.24
double kdDrive = .5; //.2
static double driveTarget;

bool turnPIDOn = false;
double kp = .98;//.7
double kd = .1; //.1
static double turnTarget;

static double maxSpeed = 195;
static int yaw = 0; //Used for arcing

double getImuRotation(){ //(-infinity, infinity)
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

//slew control
const int accel_step = 9; //9
const int deccel_step = 200; // no decel slew
static int leftSpeed = 0;
static int rightSpeed = 0;

void leftSlew(int leftTarget){
  int step;

  if(abs(leftSpeed) < abs(leftTarget)){
    step = accel_step;
  }
  else{
    step = deccel_step;
  }
  if(leftTarget > leftSpeed + step)
    leftSpeed += step;
  else if(leftTarget < leftSpeed - step)
    leftSpeed -= step;
  else
    leftSpeed = leftTarget;

  mg_driveL.moveVelocity(leftSpeed);
  //std::cout << "step: " << step << std::endl;
  //std::cout << "slewspeed: " << leftSpeed << std::endl;
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
void reset(){
  //turnTarget = 0;
  //driveTarget = 0;
  yaw = 0;
  maxSpeed = 195;
  leftSpeed = 0;
  rightSpeed = 0;
  m_driveLF.tarePosition();
  m_driveLB.tarePosition();
  m_driveRF.tarePosition();
  m_driveRB.tarePosition();
  mg_driveR.moveVelocity(0);
  mg_driveL.moveVelocity(0);
}
void setMaxSpeed(int speed){
  maxSpeed = speed;
}
bool isTurning_encoder(int threshInput, int iterationExit){ //isMoving, different inputs for thresh and iteration
  static int iteration = 0;
  static double lastPos = 0;
  static double lastTarget = 0;
  static int thresh = threshInput; //2

  double curPos = getEncRotation();
  double target = turnTarget;
  if(currentdriveState == driveStates::drivePID){
    target = driveTarget;
  }
  if(abs(lastPos-curPos) < thresh){ //3 robot degree threshold for change in Angle NEEDS TUNING
    iteration++;
  }
  else{
    iteration = 0;
  }
  if(target != lastTarget){ //If changing target, restart iterating
    iteration = 0;
  }
      // std::cout << "//////////////////////////////" << std::endl;
      // std::cout << "lastPos: " << lastPos << std::endl;
      // std::cout << "curPos: " << curPos << std::endl;
      // std::cout << "count: " << count << std::endl;
      // std::cout << "angle:" << getImuRotation() << std::endl;
  lastTarget = target;
  lastPos = curPos;

  if(iteration >= iterationExit){ //If iterated iterationExit times, 5
    return false; //Not Turning
  }
  else{
    return true; //Turning
  }
}

void turnTo(double newHeading, int speed, int threshInput, int iterationExit){ //Heading in degrees (0,360) default: 195,2,5
    reset();
    setMaxSpeed(speed);
    turnTarget = newHeading;
    setdriveState(driveStates::turnPID);
    turnPIDOn = true;

    pros::delay(200); //Assuming no super short turns
    while(isTurning_encoder(threshInput, iterationExit)){ //Wait until settled
      setdriveState(driveStates::turnPID);
      pros::delay(20);
    }

    //Movement over
    setdriveState(driveStates::tank);
    //std::cout << "turnTo Over!!" << std::endl;
    turnPIDOn = false;
}


void drive(double distance, int speed, int threshInput, int iterationExit, int yawInput){//arc  default: 195,0, 2,5 . for fast settle, 2,3
  reset();
  yaw = yawInput;
  setMaxSpeed(speed);
  driveTarget = inchesToTicks(distance);
  setdriveState(driveStates::drivePID);
  drivePIDOn = true;
  pros::delay(200);
  while(isTurning_encoder(threshInput, iterationExit)){
    setdriveState(driveStates::drivePID);
    pros::delay(20);
  }
  setdriveState(driveStates::tank);
  drivePIDOn = false;
}



//Two speed drive
void variableDrive(double distance, double changeDistanceOne, int v1, int v2, int threshInput, int iterationExit){
  reset();

  driveTarget = inchesToTicks(distance);
  int changeDistanceOneCP = inchesToTicks(changeDistanceOne);
  setdriveState(driveStates::drivePID);
  drivePIDOn = true;

  //Drive at this speed until this point
  setMaxSpeed(v1);
  if(distance > 0){
    while(getDrivePos() < changeDistanceOneCP){
      pros::delay(20);
      setdriveState(driveStates::drivePID);
    }
  }
  else{
    while(getDrivePos() > changeDistanceOneCP) {
      pros::delay(20);
      setdriveState(driveStates::drivePID);
    }
  }

  //Drive at a slower speed
  setMaxSpeed(v2);
  while(isTurning_encoder(threshInput, iterationExit)) {
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
          double target = driveTarget * 2.48;
          double current = getEncRotation();
          double error = target-current;
          double derivative = error - prevError;
          prevError = error;
          double speed = error*kpDrive + derivative*kdDrive;

          if(speed > maxSpeed)
            speed = maxSpeed;
          if(speed < -maxSpeed)
            speed = -maxSpeed;

          //Angle Straightening
          double curAngle = getImuRotation();
          double angleError = turnTarget - curAngle;
          double straightenPower = angleError * 1;//1 kP
           //std::cout << "driveTarget: " << target << std::endl;
          // std::cout << "rotation: " << current << std::endl;
           //std::cout << "error: " << error << std::endl;
           // std::cout << "turnTarget:" << turnTarget << std::endl;
           // std::cout << "curAngle:" << curAngle << std::endl;


           //mg_driveL.moveVelocity(speed + yaw + straightenPower);
          // mg_driveR.moveVelocity(speed - yaw - straightenPower);
          leftSlew(speed + yaw + straightenPower);
          rightSlew(speed - yaw - straightenPower);

          // std::cout << "////////" << std::endl;
          // std::cout << "yaw: " << yaw << std::endl;
          // std::cout << "straightenPower:" << straightenPower << std::endl;
          //  std::cout << "speed: " << speed << std::endl;

          //leftSlew(speed + yaw );
          //rightSlew(speed - yaw);
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
           //std::cout << "error: " << error << std::endl;
           //std::cout << "speed: " << speed << std::endl;


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
