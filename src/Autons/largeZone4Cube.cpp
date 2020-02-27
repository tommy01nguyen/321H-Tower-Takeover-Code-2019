#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone4Cube(int side){
//start at protect zone cube, get 4 cubes

//First Row
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {20_in, 0_in, 0_deg}}, "move1");
//flipout();
setintakeState(intakeStates::on, 12000);
chassisProfile->setTarget("move1");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {30_in, 0_in, 0_deg}}, "getCubes");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("move1");
if(side == red) turnTo(90);
if(side == blue) turnTo(-90);
pros::delay(100);
chassisProfile->setTarget("getCubes");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {20_in, 0_in, 0_deg}}, "outOfTower");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("getCubes");


//Back to zone
pidChassis->setMaxVelocity(200);
chassisProfile->setTarget("outOfTower", true);
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {25_in, 0_in, 0_deg}}, "to goal zone");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("outOfTower");
if(side == red) turnTo(-90);
if(side == blue) turnTo(90);

pidChassis->setMaxVelocity(150);
chassisProfile->setTarget("to goal zone");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {10_in, 0_in, 0_deg}}, "align");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("to goal zone");


if(side == red) turnTo(-135);
if(side == blue) turnTo(135);

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
