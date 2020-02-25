#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone4Cube(int side){
//start at protect zone cube, get 4 cubes

//First Row
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {20_in, 0_in, 0_deg}}, "firstCube");
//flipout();
setintakeState(intakeStates::on, 12000);
chassisProfile->setTarget("firstCube");
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {10_in, 0_in, 0_deg}}, "getTowerCube");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("firstCube");
if(side == red) turnTo(90);
if(side == blue) turnTo(-90);

pros::delay(100);
chassisProfile->setTarget("getTowerCube");
chassisProfile->waitUntilSettled();


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
