#include "main.h"

using namespace okapi;
int autonNumber = 0;
int autonSide = 0;
int page = 0;
/*
Pages:
1: homescreen
2-10: Auton pages
11: Color chooser

Buttons:
Start: Select, Back, Next
On Select: Red     Back      Blue

Page == Auton Number
*/

// void clear(){ //Clears all 7 lines
// 	for(int i = 0; i <= 7; i++){
// 		pros::lcd::set_text(i, "");
// 	}
// }

void displayPage(int page){

	if(page != 11){ //Assuming no more than 10 different autons
		pros::lcd::set_text(7, "Select         Previous            Next");
	}

	switch(page){
		case 1://Home Screen
			pros::lcd::set_text(1, "321H Auton Selector");
			pros::lcd::set_text(4, "");
			break;
		case 2:
			pros::lcd::set_text(4, "Small Zone 8 Cubes");
			break;
		case 3:
			pros::lcd::set_text(4, "Large Zone 8 Cubes");
			break;
		case 4:
			pros::lcd::set_text(4, "Small Zone 4 Cubes");
			break;
		case 5:
			pros::lcd::set_text(4, "Large Zone 4 Cubes");
		case 6:
			pros::lcd::set_text(4, "Flexible 1");
			break;
		case 7:
			pros::lcd::set_text(4, "Flexible 2");
			break;
		case 8:
			pros::lcd::set_text(4, "Skills 1");
			break;
		case 9:
			pros::lcd::set_text(4, "Nothing");
		case 11: //Select Side Menu
			pros::lcd::set_text(7, "Back          Red            Blue");
		case 0: //Do Nothing
			break;
	}

}

void leftButtonClicked(){
	//Either Select or Back
	if((page != 1) && (page <= 10)){ //Select
		autonNumber = page;
		page = 11; //Go to Color Chooser
		displayPage(page);

	}
	else if(page == 11){ //Back
		page = 1; //Go back to Home
		displayPage(page);
	}
}
void middleButtonClicked(){
	//Either Previous or Red
	if(page == 1){ // Previous
		page = 9; //Last Auton Page
		displayPage(page);
	}
	else if(page <= 10){
		page--;
		displayPage(page);
	}

	if(page == 11){ //Red
		//Select Red
		autonSide = 1;
		pros::lcd::set_text(5, "SELECTED RED");
	}
}
void rightButtonClicked(){
	//Either Next or Blue
	if(page == 9){ // Next
		page = 2;
		displayPage(page);
	}
	else if(page <= 10){
		page++;
		displayPage(page);
	}

	if(page == 11){ //Blue
		//Select Blue
		autonSide = -1;
		pros::lcd::set_text(5, "SELECTED BLUE");
	}
}




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
		pros::delay(500); //Give the legacy ports time to start up

		//Initialize Sensors
		initializeSensors();


		//Tasks
		pros::Task driveTask (task_driveControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Drive Task");
	  pros::Task liftTask (task_liftControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lift Task");
		pros::Task intakeTask (task_intakeControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");
		pros::Task stackerTask (task_stackerControl, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Stacker Task");

		//Auton Selector
		pros::lcd::initialize();
		pros::lcd::register_btn0_cb(leftButtonClicked);
		pros::lcd::register_btn1_cb(middleButtonClicked);
		pros::lcd::register_btn2_cb(rightButtonClicked);

		displayPage(1);//Homescreen
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

	//Pre-sets
	autonNumber = 3;//4
	autonSide = -1;

	  switch(autonNumber){
	    case 2:
				basicAuton(autonSide);
	      break;
	    case 3:
				nearZone8Cube(autonSide);
	      break;
	    case 4:
			  smallZoneBasic(autonSide);
	      break;
	    case 5:
	      break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				skills();
				break;
			case 9:
				break;
	    case 0: //Do Nothing
	      break;
	  }
}


 void opcontrol() {
	 setdriveState(driveStates::tank);//change from turning in auton to tank;
 	while (true) {
 		if(b_debug.isPressed()){//right main controller
			//flipout();
 			//autonomous();
			//std::cout << "hi" << std::endl;
 		}
		systemControl(); //Runs subsystem Controls
 		pros::delay(20);
 	}
 }
