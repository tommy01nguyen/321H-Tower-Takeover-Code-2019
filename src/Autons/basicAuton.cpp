#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1
void basicAuton(int side){

//Back up, pushing preload into the zone, get out and align with the wall.
pidChassis.moveDistance(-10_in);
pidChassis.moveDistance(10_in);
if(side == red) mg_driveL.moveDistance(22_in); //Sweeping turn to get out of touching the wall.
if(side == blue) mg_driveR.moveDistance(22_in);
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

}
