#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void flexible(int side){ //Flexible Unused, can be used for testing
setintakeState(intakeStates::on,12000);
drive(28, 70); //variable drive?
setliftState(liftStates::topCube);
pros::delay(150);
drive(5,50);
pros::delay(100);
setliftState(liftStates::noTower);
pros::delay(300);

drive(13,190); //increase

if(side == red) turnTo(90, 190);
if(side == blue) turnTo(-90, 190);
drive(20, 190);
if(side == red) turnTo(180, 190);
if(side == blue) turnTo(-180, 190);
drive(20, 190);
if(side == red) turnTo(135, 190);
if(side == blue) turnTo(-135, 190);
//Score stack

}
