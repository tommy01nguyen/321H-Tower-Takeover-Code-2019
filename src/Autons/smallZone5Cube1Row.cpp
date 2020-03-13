#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZone5Cube1Row(int side){
  //Starts in 4 cube row, goes forward, picks up the 4 cubes. Goes back and scores. 5 Cubes.
  //First Row
  flipout();
  setintakeState(intakeStates::on, 12000);
  drive(40, 70);

  //Back to zone
  drive(-25, 190);
  setintakeState(intakeStates::on, 0);
  if(side == red) turnTo(135, 190);
  if(side == blue) turnTo(-135, 190);
  setintakeState(intakeStates::toFrontSensor);
  drive(15, 150);

  //Score in Zone
  stackSmall();

  setstackerState(stackerStates::toBottomQuick);
  setintakeState(intakeStates::on, -6000);
  drive(-10, 160);
}
