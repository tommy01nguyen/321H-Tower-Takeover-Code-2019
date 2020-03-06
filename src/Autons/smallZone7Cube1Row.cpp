#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZone7Cube1Row(int side){
//Starts in 4 cube row, goes forward, picks up all the cubes, turns and gets the cube by the tower, then scores. 7 cubes.

//First Row
//flipout();
setintakeState(intakeStates::on, 12000);
drive(45, 105);
drive(13, 150);
drive(-18, 190);
//pros::delay(200);

//Back to zone
if(side == red) turnTo(-30, 190);
if(side == blue) turnTo(30, 190);
drive(10, 150);

drive(-20, 190);
setintakeState(intakeStates::on, 0);
if(side == red) turnTo(150, 190);
if(side == blue) turnTo(-150, 190);
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
