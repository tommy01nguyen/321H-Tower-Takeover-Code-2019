#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone4Cube(int side){
//start at protect zone cube, get 4 cubes

//First Row
//flipout();
setintakeState(intakeStates::on, 12000);
drive(30, 150);
if(side == red) turnTo(-135, 190);
if(side == blue) turnTo(135, 190);

drive(20,150);
if(side == red) turnTo(-260, 190);
if(side == blue) turnTo(260, 190);

drive(35, 150);
if(side == red) turnTo(-225, 190);
if(side == blue) turnTo(225, 190);


setintakeState(intakeStates::toFrontSensor);
drive(10, 190);

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
