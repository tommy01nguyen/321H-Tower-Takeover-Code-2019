#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZone5Cube1Row(int side){
  //Starts in 4 cube row, goes forward, picks up the 4 cubes. Goes back and scores. 5 Cubes.
  // if(side == red) turnTo(135);
  // if(side == blue) turnTo(-135);


  //First Row
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {120_in, 0_in, 0_deg}}, "throughFirstRow");
  //flipout();
  setintakeState(intakeStates::on, 12000);
  pidChassis->setMaxVelocity(80);
  chassisProfile->setTarget("throughFirstRow");
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {24_in, 0_in, 0_deg}}, "out of row");
  chassisProfile->waitUntilSettled();
  chassisProfile->removePath("throughFirstRow");
  //pros::delay(200);

  //Back to zone
  pidChassis->setMaxVelocity(200);
  chassisProfile->setTarget("out of row", true);
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {25_in, 0_in, 0_deg}}, "to goal zone");
  chassisProfile->waitUntilSettled();
  chassisProfile->removePath("out of row");
  setintakeState(intakeStates::on, 0);
  if(side == red) turnTo(135);
  if(side == blue) turnTo(-135);
  pidChassis->setMaxVelocity(150);
  chassisProfile->setTarget("to goal zone");
  setintakeState(intakeStates::readyToStack);
  chassisProfile->waitUntilSettled();
  chassisProfile->removePath("to goal zone");

  //Score in Zone
  setintakeState(intakeStates::hold);
  setstackerState(stackerStates::stackMacro);
  pros::delay(100);
  while(stackMacroOn){
    pros::delay(20);
  }
  pidChassis->setMaxVelocity(160);
  pidChassis->moveDistance(-10_in);
  setstackerState(stackerStates::toBottom);
  setintakeState(intakeStates::on, -6000);

}
