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

/**
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

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


 //Controller Buttons
 ControllerButton b_driveHold(ControllerDigital::B);
 ControllerButton b_driveSlower(ControllerDigital::L1);

 ControllerButton b_anglerUp(ControllerId::partner, ControllerDigital::A);
 ControllerButton b_anglerDown(ControllerId::partner, ControllerDigital::X);

 //Partner
 ControllerButton b_intakeIn(ControllerId::partner, ControllerDigital::L2);
 ControllerButton b_intakeOut(ControllerId::partner, ControllerDigital::L1);

 ControllerButton b_liftUp(ControllerId::partner, ControllerDigital::R1);
 ControllerButton b_liftDown(ControllerId::partner, ControllerDigital::R2);

 ControllerButton b_debug(ControllerDigital::A);


 void opcontrol() {
 	while (true) {
 		//if(b_debug.isPressed()){
 		//	autonomous();
 		//}
 		if(b_driveHold.isPressed()){ //Hold Position
 			mg_driveR.setBrakeMode(AbstractMotor::brakeMode::hold);
 			mg_driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
 			mg_driveR.moveVelocity(0);
 			mg_driveL.moveVelocity(0);
 		}
 			else if(b_driveSlower.isPressed()){
 					pidChassis.tank(j_master.getAnalog(ControllerAnalog::leftY)*.65, //Tank Control half speed
 								 j_master.getAnalog(ControllerAnalog::rightY)*.65);
 			}
 					else{
 						if(mg_driveR.getBrakeMode() == AbstractMotor::brakeMode::hold){ //Change from Hold to Coast
 							mg_driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
 							mg_driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
 						}
 						pidChassis.tank(j_master.getAnalog(ControllerAnalog::leftY), //Tank control Normal
 													  j_master.getAnalog(ControllerAnalog::rightY));
 					 }

 		//Angler
 		if(b_anglerUp.isPressed()){
 			m_angler.moveVoltage(12000);
 		}
 		else if(b_anglerDown.isPressed()){
 			m_angler.moveVoltage(-12000);
 		}
 		else{
 			m_angler.moveVoltage(0);
 		}

 		//Intake
 		if(b_intakeIn.isPressed()){
 			m_intakeL.moveVoltage(12000);
 			m_intakeR.moveVoltage(12000);
 		}
 		else if(b_intakeOut.isPressed()){
 			m_intakeR.moveVoltage(-12000);
 			m_intakeL.moveVoltage(-12000);
 		}
 		else{
 			m_intakeR.moveVoltage(0);
 			m_intakeL.moveVoltage(0);
 		}

 		//Lift
 		if(b_liftUp.isPressed()){
 			m_lift.moveVoltage(12000);
 		}
 		else if(b_liftDown.isPressed()){
 			m_lift.moveVoltage(-12000);
 		}
 		else{
 			m_lift.moveVoltage(0);
 		}
 		pros::delay(20);
 	}
 }
