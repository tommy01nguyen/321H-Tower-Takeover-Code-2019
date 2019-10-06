#include "321Hlib/initialize.h"

int autonNumber = 0;
int autonSide = 0;
int autonPark = 0;
int autonDelay = 0;
int page = 0;

/*
Pages:
0 = homescreen
Red Auton----
1 = Red Auton 1
2 = Red Auton 2
3 = Red Auton 3
4 = Red Auton 4
5 = Red Auton 5
Blue Auton----
6 = Blue Auton 1
7 = Blue Auton 2
8 = Blue Auton 3
9 = Blue Auton 4
10 = Blue Auton 5

-----------
new:
Scroll.
Homepage : Red None Blue
Red Page: Home Select Next
Blue Page: Home Select Next

Autons:
*/

void autonSelector(){

}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {


	initializeRobot(); //Sensors, Motor Brakes
	//Tasks
	/*
  pros::Task liftTask (task_liftControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lift Task");
	pros::Task intakeTask (task_intakeControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");
	pros::Task stackerTask (task_stackerControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Stacker Task");
	pros::Task driveTask (task_driveControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Drive Task");
	*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this tasSk will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}
