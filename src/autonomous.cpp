#include "321Hlib/Autons/auton.h"
/*
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
using namespace okapi;

void autonomous() {
//Red 1, -1 blue
//autonSide = -1;

//Case
autonNumber = 1;

  switch(autonNumber){ //ex: autonNumber 1 will make case 1 run
    case 1:
      basicAuton(-1);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
    flexible(autonSide);
      break;
    case 0: //Do Nothing
      break;
  }
}
