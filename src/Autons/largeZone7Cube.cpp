#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone7Cube(int side){
//Start in red square, preload aligned with nearby cube, S curve to side of 4 stack, take 4 stack, go back and get the aligned cubes, get the cube near the zone, and score. 7 cubes.

//First Row
//flipout();
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {43_in, -15_in, 0_deg}}, "move1");
pros::delay(500);
setintakeState(intakeStates::on, 12000);
chassisProfile->setTarget("move1");
chassisProfile->waitUntilSettled();
chassisProfile->removePath("move1");
turnTo(-90, 150);
setintakeState(intakeStates::on, 12000);
drive(21,150);
turnTo(-185, 190);
drive(30, 150);
turnTo(-283, 190);
drive(24, 150);
turnTo(-240,190);

setintakeState(intakeStates::toFrontSensor);
drive(8, 190);

//Score in Zone
intakeStackMacroOn = true;
setintakeState(intakeStates::readyToStack);
stackMacroOn = true;
setstackerState(stackerStates::stackMacro);
while(stackMacroOn){
  pros::delay(20);
}

setstackerState(stackerStates::toBottom);
setintakeState(intakeStates::on, -6000);
drive(-10, 190);


}
