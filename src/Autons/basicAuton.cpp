#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1
void basicAuton(int side){

//Back up, pushing preload into the zone, get out and align with the wall.

pidChassis.moveDistance(-12_in);
pros::delay(100);
pidChassis.moveDistance(10_in);
pros::delay(100);
if(side == red) pidChassis.driveVector(8000, -100);//Sweeping turn to get out of touching the wall.
if(side == blue) pidChassis.driveVector(8000, 100);
pros::delay(900);
pidChassis.stop();
pros::delay(200);
driveWall(-6000);
pros::delay(500);
pidChassis.moveDistance(-5_in);
pros::delay(500);
pidChassis.moveDistance(45_in);
pros::delay(100);
if(side == red) pidChassis.turnAngle(80_deg);
if(side == blue) pidChassis.turnAngle(-90_deg);
pros::delay(200);
pidChassis.moveDistance(-50_in);
pros::delay(200);
pidChassis.moveDistance(20_in);
/*
pidChassis.moveDistance(-5_in); //Back up against the Wall


//Drive Out, turn, and head towards the second goalzone.
pidChassis.moveDistance(44_in);
if(side == red) pidChassis.turnAngle(-90_deg);
if(side == blue) pidChassis.turnAngle(90_deg);
pidChassis.moveDistance(115_in);

//Turn and drive into the goal zone, pushing cubes into the zone.
if(side == red) pidChassis.turnAngle(-35_deg);
if(side == blue) pidChassis.turnAngle(35_deg);
pidChassis.moveDistance(54_in); //Push into the zone
pros::delay(500);
pidChassis.moveDistance(-20_in); //Out
*/
}
