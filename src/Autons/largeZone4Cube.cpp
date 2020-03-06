#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone4Cube(int side){
//start at protect zone cube, get 4 cubes

//First Row
//flipout();
setintakeState(intakeStates::on, 12000);
drive(5, 150);
if(side == red) turnTo(75, 190);
if(side == blue) turnTo(-75, 190);



if(side == red) turnTo(75, 190);
if(side == blue) turnTo(-75, 190);
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

setstackerState(stackerStates::toBottom);
setintakeState(intakeStates::on, -6000);
drive(-10, 190);


}
