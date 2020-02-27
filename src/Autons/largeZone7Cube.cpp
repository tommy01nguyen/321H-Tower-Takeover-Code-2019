#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone7Cube(int side){
//Start in red square, preload aligned with nearby cube, S curve to side of 4 stack, take 4 stack, go back and get the aligned cubes, get the cube near the zone, and score. 7 cubes.

//First Row
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "move1");
flipout();
setintakeState(intakeStates::on, 12000);
chassisProfile->setTarget("move1");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {30_in, 0_in, 0_deg}}, "4stack");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("move1");
if(side == red) turnTo(90);
if(side == blue) turnTo(-90);
pros::delay(100);
chassisProfile->setTarget("4stack");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {20_in, 0_in, 0_deg}}, "alignedCubes");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("4stack");


//Back to zone
chassisProfile->setTarget("alignedCubes");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {25_in, 0_in, 0_deg}}, "lastCube");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("alignedCubes");
if(side == red) turnTo(-45);
if(side == blue) turnTo(45);

chassisProfile->setTarget("lastCube");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {10_in, 0_in, 0_deg}}, "align");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("lastCube");


if(side == red) turnTo(-135);
if(side == blue) turnTo(135);

pidChassis->setMaxVelocity(150);
setintakeState(intakeStates::toFrontSensor);
chassisProfile->setTarget("align");
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
pidChassis->moveDistance(-10_in); //Too long, if auton ends before this ends, would need to restart program.






}
