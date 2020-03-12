#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone4Cube(int side){
//start at protect zone cube, get 4 cubes

//First Row
//flipout();
setintakeState(intakeStates::on, 12000);
drive(25, 150);
if(side == red) turnTo(-100, 190);
if(side == blue) turnTo(100, 190);

drive(20,150);
if(side == red) turnTo(-125, 190);
if(side == blue) turnTo(125, 190);

setintakeState(intakeStates::toFrontSensor);
drive(15, 190);


//Score in Zone
stackSmall();

setstackerState(stackerStates::toBottomQuick);
pros::delay(200);
setintakeState(intakeStates::on, -6000);
drive(-10, 190);


}
