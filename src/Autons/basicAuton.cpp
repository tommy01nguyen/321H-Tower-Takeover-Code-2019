#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1

void basicAuton(int side){
side = -1;
// Flip out
setstackerState(stackerStates::towerScoring);
setliftState(liftStates::highTower);
pros::delay(1500);
setstackerState(stackerStates::noTowerScoring);
setliftState(liftStates::noTower);
pros::delay(1000);
setliftState(liftStates::on,0);
setstackerState(stackerStates::on,0);
// Intake and Drive Forward
setintakeState(intakeStates::on, 12000);
pidChassis.moveDistance(35_in); //Up until past stack
pros::delay(500);
pidChassis.moveDistance(9_in);
setintakeState(intakeStates::on, 0);
//Drive Backwards
pidChassis.moveDistance(-43_in);
// Turn Towards Goal zone
//if(side == red) pidChassis.turnAngle(-83_deg);
//if(side == blue) pidChassis.turnAngle(91_deg);


//pidChassis.turnAngle(-83_deg); //RED
pidChassis.turnAngle(91_deg); //BLUE


//Drive to Goal Zone
pidChassis.moveDistance(28_in);

// Score
setstackerState(stackerStates::stackMacro); //Intake out a tiny bit, then moves stack up
pros::delay(2000);
pidChassis.moveDistance(-20_in);


}
