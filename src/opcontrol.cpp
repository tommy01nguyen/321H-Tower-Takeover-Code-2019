#include "321Hlib/opcontrol.h"
// If no competition control is connected, this function will run immediately following initialize().

using namespace pros;
/*
Notes
Drivetrain task
Intake Task
lift Task
Rotator Task
*/

void opcontrol() {

	bool partner = true; //2 Controllers or nah

	pros::lcd::initialize();
	lcd::set_text(1, "Odometry...");

	while (true) {
		pidChassis.tank(j_master.getAnalog(ControllerAnalog::leftY), j_master.getAnalog(ControllerAnalog::rightY));
		//Angler
		if(j_master.getDigital(ControllerDigital::R1)){
			m_angler.moveVoltage(-12000);
		}
		else if(j_master.getDigital(ControllerDigital::R2)){
			m_angler.moveVoltage(12000);
		}
		else{
			m_angler.moveVoltage(0);
		}


		if(partner == false){
			//Intake
			if(j_master.getDigital(ControllerDigital::L1)){
				m_intake.moveVoltage(12000);
			}
			else if(j_master.getDigital(ControllerDigital::L2)){
				m_intake.moveVoltage(-12000);
			}
			else{
				m_intake.moveVoltage(0);
			}

			//Lift
			if(j_master.getDigital(ControllerDigital::R1)){
				m_liftL.moveVoltage(12000);
				m_liftR.moveVoltage(12000);
			}
			else if(j_master.getDigital(ControllerDigital::R2)){
				m_liftL.moveVoltage(-12000);
				m_liftR.moveVoltage(-12000);
			}
			else{
				m_liftL.moveVoltage(0);
				m_liftR.moveVoltage(0);
			}

			//Angler
			if(j_master.getDigital(ControllerDigital::X)){
				m_angler.moveVoltage(12000);
			}
			else if(j_master.getDigital(ControllerDigital::B)){
				m_angler.moveVoltage(-12000);
			}
			else{
				m_angler.moveVoltage(0);
			}
		}
		else{ //****************************************************** Partner controls
			//Intake
			if(j_partner.getDigital(ControllerDigital::L1)){
				m_intake.moveVoltage(12000);
			}
			else if(j_partner.getDigital(ControllerDigital::L2)){
				m_intake.moveVoltage(-12000);
			}
			else{
				m_intake.moveVoltage(0);
			}

			//Lift
			if(j_partner.getDigital(ControllerDigital::R2)){
				m_liftL.moveVoltage(12000);
				m_liftR.moveVoltage(12000);
			}
			else if(j_partner.getDigital(ControllerDigital::R1)){
				m_liftL.moveVoltage(-12000);
				m_liftR.moveVoltage(-12000);
			}
			else{
				m_liftL.moveVoltage(0);
				m_liftR.moveVoltage(0);
			}
		}
		pros::delay(200);
	}
}
