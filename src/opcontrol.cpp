#include "321Hlib/opcontrol.h"
// If no competition control is connected, this function will run immediately following initialize().

using namespace okapi;
/*
Notes
Drivetrain task
Intake Task
lift Task
Rotator Task
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
	pros::lcd::initialize();

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
