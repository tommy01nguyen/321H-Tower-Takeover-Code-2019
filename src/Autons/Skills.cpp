#include "321Hlib/Autons/auton.h"

using namespace okapi;

void skills(){
  //Starts at Red, 4 line

  //Drive through 9 line

  flipout();
  setintakeState(intakeStates::on, 12000);
  pidChassis->setMaxVelocity(100);
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {28_in, 0_in, 0_deg}}, "out of row");
  pidChassis->moveDistance(140_in);

  //Score in Zone
  pidChassis->setMaxVelocity(200);
  turnTo(45);
  pidChassis->moveDistance(10_in);

  intakeStackMacroOn = true;
  setintakeState(intakeStates::readyToStack);
  stackMacroOn = true;
  setstackerState(stackerStates::stackMacro);
  while(stackMacroOn){
    pros::delay(20);
  }

  pidChassis->setMaxVelocity(160);
  setstackerState(stackerStates::toBottom);
  setintakeState(intakeStates::on, -6000);
  pidChassis->moveDistance(-20_in); //To tower line up




  chassisProfile->setTarget("out of row", true);
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {25_in, 0_in, 0_deg}}, "to goal zone");
  chassisProfile->waitUntilSettled();
  chassisProfile->removePath("out of row");
  setintakeState(intakeStates::on, 0);
  turnTo(135);
  pidChassis->setMaxVelocity(150);
  chassisProfile->setTarget("to goal zone");
  setintakeState(intakeStates::toFrontSensor);
  chassisProfile->waitUntilSettled();
  chassisProfile->removePath("to goal zone");

  //Score in Zone
  intakeStackMacroOn = true;
  setintakeState(intakeStates::readyToStack);
  stackMacroOn = true;
  setstackerState(stackerStates::stackMacro);
  while(stackMacroOn){
    pros::delay(20);
  }

  pidChassis->setMaxVelocity(160);
  setstackerState(stackerStates::toBottom);
  setintakeState(intakeStates::on, -6000);
  pidChassis->moveDistance(-10_in);
}
