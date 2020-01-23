#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void basicAuton(int side){

flipout();
// Intake and Drive Forward
setintakeState(intakeStates::on, 12000);
pidChassis->moveDistance(35_in); //Up until past stack
pros::delay(500);
pidChassis->moveDistance(9_in);
setintakeState(intakeStates::on, 0);
//Drive Backwards
pidChassis->moveDistance(-43_in);
// Turn Towards Goal zone
if(side == red) pidChassis->turnAngle(-83_deg);
if(side == blue) pidChassis->turnAngle(91_deg);
//Drive to Goal Zone
pidChassis->moveDistance(28_in);

// Score
mg_intake.moveRelative(-50, 100);
pros::delay(500);
setstackerState(stackerStates::stackMacro); //Stack that
pros::delay(500);
pidChassis->moveDistance(-20_in);
}
