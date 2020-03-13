#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZone6Cube1Row(int side){
//Starts in 4 cube row, goes forward, picks up all the cubes 6 cubes.
flipout();
//First Row
setintakeState(intakeStates::on, 12000);
drive(40, 70);

//Back to zone
if(side == red) turnTo(-30, 200);
if(side == blue) turnTo(30, 200);
drive(10, 150);

drive(-27, 190);
setintakeState(intakeStates::on, 0);
if(side == red) turnTo(150, 200);
if(side == blue) turnTo(-150, 200);
setintakeState(intakeStates::toFrontSensor);
drive(15, 190);

//Score in Zone
stackSmall();

setstackerState(stackerStates::toBottomQuick);
setintakeState(intakeStates::on, -6000);
drive(-10, 160);
}
