#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZoneBasic(int side){

flipout();
// Intake and Drive Forward
setintakeState(intakeStates::on, 12000);
pidChassis->setMaxVelocity(100);
pidChassis->moveDistance(43_in); //Up until past stack

//Drive Backwards
pidChassis->moveDistance(-30_in);
// Turn Towards Goal zone
if(side == red) pidChassis->turnAngle(83_deg);
if(side == blue) pidChassis->turnAngle(-91_deg);
//Drive to Goal Zone
pidChassis->moveDistance(15_in);

// Score
mg_intake.moveRelative(-50, 100);
pros::delay(500);
setstackerState(stackerStates::stackMacro); //Stack that
pros::delay(500);
pidChassis->moveDistance(-10_in);
}
