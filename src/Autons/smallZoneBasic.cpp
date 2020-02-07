#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZoneBasic(int side){
//Starts in 4 cube row, goes forward, picks up all the cubes, turns and gets the cube by the tower, then scores. 7 cubes.

//First Row
flipout();
setintakeState(intakeStates::on, 12000);
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {16_in, 0_in, 0_deg}}, "out of row");
pidChassis->setMaxVelocity(150);
pidChassis->moveDistance(55_in);

//Get tower cube
chassisProfile->setTarget("out of row", true);
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {16_in, 0_in, 0_deg}}, "through tower cube");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("out of row");
turnTo(-50);
chassisProfile->setTarget("through tower cube");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {50_in, 0_in, 0_deg}}, "to goal zone");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("through tower cube");

//Get to zone
turnTo(-40);
setintakeState(intakeStates::on, 6000);
chassisProfile->setTarget("to goal zone", true);
chassisProfile->waitUntilSettled();
chassisProfile->removePath("to goal zone");
turnTo(135);

//Score in Zone
setintakeState(intakeStates::readyToStack);
pidChassis->setMaxVelocity(80); //Tune speed so it is impossible to climb over zone
pidChassis->moveDistance(10_in);
setstackerState(stackerStates::bigStackMacro);
setdriveState(driveStates::outOfStack);
pros::delay(1000);
setdriveState(driveStates::tank);

}
