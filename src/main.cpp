#include "main.h"

using namespace okapi;
int autonNumber = 0;
int autonSide = 0;
int autonPark = 0;
int autonDelay = 0;
int page = 0;

void autonSelector(){

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
		//pros::delay(500); //Give the legacy ports time to start up

		initializeRobot(); //Sensors

		//Tasks
	  pros::Task liftTask (task_liftControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lift Task");
		pros::Task intakeTask (task_intakeControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");
		pros::Task stackerTask (task_stackerControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Stacker Task");
		pros::Task driveTask (task_driveControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Drive Task");

		//Auton Selector


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
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
void competition_initialize() {}

void autonomous() {
	//Red 1, -1 blue

	//Pre-set
	autonNumber = 1;
	autonSide =-1;

	  switch(autonNumber){ //ex: autonNumber 1 will make case 1 run
	    case 1:
	      basicAuton(autonSide);
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


 void opcontrol() {
 	while (true) {
 		//if(b_debug.isPressed()){
 		//	autonomous();
 		//}

		systemControl(); //Runs subsystem Controls
 		pros::delay(20);
 	}
 }
