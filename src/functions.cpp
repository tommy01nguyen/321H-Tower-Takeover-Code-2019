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
void resetEncoders(){
  m_stacker.tarePosition();
  m_lift.tarePosition();
}

void flipout(){
  setliftState(liftStates::highTower);
  pros::delay(1500);
  setliftState(liftStates::noTower);
  pros::delay(1000);
  setliftState(liftStates::on,0);
}

void stack(){

}
