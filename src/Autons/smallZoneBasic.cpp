#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void smallZoneBasic(int side){
// 
// mg_driveL.moveDistance(10_in);
// mg_driveR.moveDistance(10_in);
// //flipout();
// // Intake and Drive Forward
// setintakeState(intakeStates::on, 12000);
// pidChassis->setMaxVelocity(200);
//
// pidChassis->moveDistance(43_in); //Up until past stack
// //Drive Backwards
// pidChassis->setMaxVelocity(3000);
// pidChassis->moveDistance(-30_in);
// // Turn Towards Goal zone
// pidChassis->setMaxVelocity(150);
// if(side == red) pidChassis->turnAngle(130_deg);
// if(side == blue) pidChassis->turnAngle(-140_deg);
// //Drive to Goal Zone
// pidChassis->moveDistance(15_in);
//
// // Score

//setintakeState(intakeStates::untilSensed, -12000);

// setstackerState(stackerStates::stackMacro); //Stack that
// pros::delay(500);
// pidChassis->moveDistance(-10_in);
setdriveState(driveStates::outOfStack);

}
