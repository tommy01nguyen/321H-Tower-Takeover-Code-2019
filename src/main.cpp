#include "main.h"

using namespace okapi;
int autonNumber = 0;
int autonSide = 0;
int page = 1;
/*
Pages:
1-7: Auton pages
11: Color chooser

Buttons:
Auton List: Select, Previous,  Next
Color Chooser: Back, Red, Blue

autonNumber = page
*/

void displayPage(int page){

	if(page != 11){ //Assuming no more than 10 different autons
		pros::lcd::set_text(7, "Select      Previous       Next");
	}

	pros::lcd::print(0, "Number:%i Side:%i (R1:B-1)", autonNumber, autonSide);
	switch(page){
		case 1://Initial Screen
			pros::lcd::set_text(3, "Program: Nothing");
			break;
		case 2:
			pros::lcd::print(3, "Program: smallZone6Cube1Row");
			break;
		case 3:
			pros::lcd::set_text(3, "Program: largeZone4Cube");
			break;
		case 4:
			pros::lcd::set_text(3, "Program: smallZone5Cube1Row");
			break;
		case 5:
			pros::lcd::set_text(3, "Program: Filler 1");
		case 6:
			pros::lcd::set_text(3, "Program: Filler 2");
			break;
		case 7:
			pros::lcd::set_text(3, "Program: Filler 3");
			break;
		case 8:
			pros::lcd::set_text(3, "Program: Skills");
			break;
		case 11: //Select Side Menu
			pros::lcd::set_text(7, "Back          Red          Blue");
			break;
	}
}

void leftButtonClicked(){
	//Either Select or Back
	if(page <= 10){ //Select
		autonNumber = page;
		page = 11; //Go to Color Chooser
	}
	else if(page == 11){ //Back
		page = 1; //Go back to Auton List
		pros::lcd::set_text(5, "");
	}
	displayPage(page);
}
void middleButtonClicked(){
	//Either Previous or Red
	if(page == 1){ // Previous
		page = 8; //Last Auton Page
	}
	else if(page <= 10){
		page--;
	}
	if(page == 11){ //Select Red
		autonSide = 1;
		pros::lcd::set_text(5, "Color: Red");
	}
	displayPage(page);
}
void rightButtonClicked(){
	//Either Next or Blue
	if(page == 8){ // Next
		page = 1;
	}
	else if(page <= 10){
		page++;
	}

	if(page == 11){ //Select Blue
		autonSide = -1;
		pros::lcd::set_text(5, "Color: Blue");
	}
	displayPage(page);
}




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 std::shared_ptr<okapi::ChassisController> pidChassis;
 std::shared_ptr<okapi::AsyncMotionProfileController> chassisProfile;
void initialize() {
		pros::delay(500); //Give the legacy ports time to start up

		//Initialize Sensors
		initializeSensors();

		pidChassis = ChassisControllerBuilder()
												.withMotors({mg_driveL},{mg_driveR})
												.withGains({.00090, 0, .000001},{.0012, 0, 0.00002})//.000008 and .0000008 || .00072 ||0000001
												.withDimensions(AbstractMotor::gearset::green, {{4.05_in, 10.5_in}, imev5GreenTPR})
												.build();
	  chassisProfile = AsyncMotionProfileControllerBuilder() //Async 2D Motion Profile Controller
 											 	.withLimits({1.0, 2.0, 10.0})//3,5,10
												.withOutput(pidChassis)
												.buildMotionProfileController();

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
	autonNumber = 8;//4
	autonSide = 1;

	  switch(autonNumber){
			case 1: //Do Nothing
				break;
	    case 2:
				smallZone5Cube1Row(autonSide);
	      break;
	    case 3:
				//largeZone4Cube(autonSide);
				smallZone6Cube1Row(autonSide);
	      break;
	    case 4:
				smallZone7Cube1Row(autonSide);
	      break;
	    case 5:
				flexible(autonSide);
				//smallZone9Cube2Row(autonSide);
	      break;
			case 6:
				largeZone4Cube(autonSide);
				//smallZone7Cube1Row(autonSide);
				break;
			case 7:
				largeZone7Cube(autonSide);
				break;
			case 8:
				skills();
				break;
	  }
}


 void opcontrol() {
	 setdriveState(driveStates::tank);//change from turning in auton to tank;
 	while (true) {
		systemControl(); //Runs subsystem Controls
 		pros::delay(20);
 	}
 }
