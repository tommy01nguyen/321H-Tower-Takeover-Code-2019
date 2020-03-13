#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZone9Cube2Row(int side){
  flipout();
  setintakeState(intakeStates::on,12000);
  variableDrive(28, 26, 180, 70, 2, 5);
  setliftState(liftStates::topCube);
  pros::delay(150);
  drive(5,100);
  setliftState(liftStates::noTower);
  pros::delay(200);

  drive(14,190);

  if(side == red) turnTo(90, 190);
  if(side == blue) turnTo(-90, 190);
  drive(22, 190,3,3); //increase
  if(side == red) turnTo(180, 190,3,3);
  if(side == blue) turnTo(-180, 190);
  drive(22, 190,3,3);
  if(side == red) turnTo(135, 190);
  if(side == blue) turnTo(-135, 190);

  setintakeState(intakeStates::toFrontSensor);
  drive(20, 190,3,3);

  //Score in Zone
  stackSmall();

  setstackerState(stackerStates::toBottomQuick);
  setintakeState(intakeStates::on, -6000);
  drive(-10, 160);
}
