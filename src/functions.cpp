#include "321Hlib/functions.h"

using namespace okapi;
/*
double tileToIn(double tiles){ //Converts Tiles to inches (1 Tile = 24inches)
  double inches = tiles * 24;
  return inches;
}

QLength tilesToInches(double tiles){ //Converts Tiles To Inches
  return tiles*24*inch ;
}
*/

// void driveWall(int voltage){ //Drives until it hits a wall
//   mg_driveR.moveVoltage(voltage);
//   mg_driveL.moveVoltage(voltage);
//   while(isDriving()){
//     pros::delay(20);
//   }
//   mg_driveR.moveVoltage(0);
//   mg_driveL.moveVoltage(0);
// }
//
// void vectorWall(double voltage, double yaw){ //voltage -1 to 1. left + yaw, Right - yaw
//   pidChassis->getModel()->driveVector(voltage, yaw);
//   waitUntilStopped(20);
//   mg_driveR.moveVoltage(0);
//   mg_driveL.moveVoltage(0);
// }

void driveTest(int distance, int speed){
  m_driveRB.tarePosition();
  m_driveLB.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveLF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRB.setBrakeMode(AbstractMotor::brakeMode::brake);


  if(distance < 0){
    while(m_driveRB.getPosition() > distance){
      m_driveLB.moveVelocity(speed);
      m_driveLF.moveVelocity(speed);
      m_driveRB.moveVelocity(speed);
      m_driveRF.moveVelocity(speed);
    }
  }
  else{
    while(m_driveRB.getPosition() < distance){
      m_driveLB.moveVelocity(speed);
      m_driveLF.moveVelocity(speed);
      m_driveRB.moveVelocity(speed);
      m_driveRF.moveVelocity(speed);
    }

  }
  m_driveLB.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveLF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRB.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveLB.moveVelocity(0);
  m_driveLF.moveVelocity(0);
  m_driveRB.moveVelocity(0);
  m_driveRF.moveVelocity(0);

// pidChassis->moveDistance(10_in);
}
void turn(int distance, int speed){
  m_driveRB.tarePosition();
  m_driveLB.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveLF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRB.setBrakeMode(AbstractMotor::brakeMode::brake);


  if(distance < 0){
    while(m_driveRB.getPosition() < -distance){
      m_driveLB.moveVelocity(speed);
      m_driveLF.moveVelocity(speed);
      m_driveRB.moveVelocity(-speed);
      m_driveRF.moveVelocity(-speed);
    }
  }
  else{
    while(m_driveRB.getPosition() > -distance){
      m_driveLB.moveVelocity(speed);
      m_driveLF.moveVelocity(speed);
      m_driveRB.moveVelocity(-speed);
      m_driveRF.moveVelocity(-speed);
    }

  }
  m_driveLB.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveLF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRF.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveRB.setBrakeMode(AbstractMotor::brakeMode::brake);
  m_driveLB.moveVelocity(0);
  m_driveLF.moveVelocity(0);
  m_driveRB.moveVelocity(0);
  m_driveRF.moveVelocity(0);

}

void resetEncoders(){
  m_stacker.tarePosition();
  m_lift.tarePosition();
}

void flipout(){
  setstackerState(stackerStates::raisedPreset);
  setliftState(liftStates::highTower);
  pros::delay(800);
  setstackerState(stackerStates::toBottom);
  setliftState(liftStates::noTower);
  pros::delay(400);
  setliftState(liftStates::on,0);
}

void outOfStack(){
  setintakeState(intakeStates::on,-6000);
  driveTest(-100,-200);
  setintakeState(intakeStates::on, 0);
}

void stack(){

}
