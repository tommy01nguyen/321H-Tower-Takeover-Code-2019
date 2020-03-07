#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZone9Cube2Row(int side){
  setintakeState(intakeStates::on,12000);
  drive(28, 70); //variable drive?
  //variableDrive(28, 25, 180, 70, 2, 5);
  setliftState(liftStates::topCube);
  pros::delay(150);
  drive(5,50);
  pros::delay(100);
  setliftState(liftStates::noTower);
  pros::delay(300);

  drive(13,190); //increase

  if(side == red) turnTo(90, 190);
  if(side == blue) turnTo(-90, 190);
  drive(20, 190); //increase
  if(side == red) turnTo(180, 190);
  if(side == blue) turnTo(-180, 190);
  drive(20, 190);
  if(side == red) turnTo(135, 190);
  if(side == blue) turnTo(-135, 190);

  setintakeState(intakeStates::toFrontSensor);
  drive(15, 190);

  //Score in Zone
  intakeStackMacroOn = true;
  setintakeState(intakeStates::readyToStack);
  stackMacroOn = true;
  setstackerState(stackerStates::stackMacro);
  while(stackMacroOn){
    pros::delay(20);
  }

  setstackerState(stackerStates::toBottomQuick);
  setintakeState(intakeStates::on, -6000);
  drive(-10, 160);
}
