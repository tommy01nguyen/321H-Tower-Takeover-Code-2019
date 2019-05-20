
#include "321Hlib/SystemControl/systemControl.h"
using namespace okapi;

//Controller Buttons
ControllerButton b_intakeIn(ControllerDigital::L2);
ControllerButton b_intakeOut(ControllerDigital::L1);
ControllerButton b_intakeToTop(ControllerDigital::R1);
ControllerButton b_intakeInPartner(ControllerId::partner, ControllerDigital::L2);
ControllerButton b_intakeOutPartner(ControllerId::partner, ControllerDigital::L1);

ControllerButton b_cataDown(ControllerDigital::X);
ControllerButton b_cataLoad(ControllerDigital::B);
ControllerButton b_cataToggle(ControllerDigital::Y);
//Automatic Catapult Shot is A

ControllerButton b_driveHold(ControllerId::partner, ControllerDigital::A);
ControllerButton b_driveSlower(ControllerId::partner, ControllerDigital::R2);

ControllerButton b_platformShoot(ControllerId::partner, ControllerDigital::X);
//ControllerButton b_debug(ControllerId::partner, ControllerDigital::Y);

void driveControl(){ //Drivetrain Control
  if(b_driveHold.isPressed()){ //Hold, to prevent other robots from pushing us
    mg_driveR.setBrakeMode(AbstractMotor::brakeMode::hold);
    mg_driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
    mg_driveR.moveVelocity(0);
    mg_driveL.moveVelocity(0);
  }
    else if(b_driveSlower.isPressed()){
      pidChassis.tank(j_partner.getAnalog(ControllerAnalog::leftY)*.65, //Tank Control half speed
                   j_partner.getAnalog(ControllerAnalog::rightY)*.65);
    }
    else{
      if(mg_driveR.getBrakeMode() == AbstractMotor::brakeMode::hold){ //Change from Hold to Coast
        mg_driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
        mg_driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
      }
      pidChassis.tank(j_partner.getAnalog(ControllerAnalog::leftY), //Tank control
                   j_partner.getAnalog(ControllerAnalog::rightY));
    }
}
bool toggle = false;
void catapultControl(){ //Catapult Control | State Machine

  if(b_cataToggle.changedToPressed()){
    toggle = !toggle;
  }

  if(toggle){
    setCatapultState(catapultStates::automatic);
  }
    else if(b_cataLoad.isPressed()){
      setCatapultState(catapultStates::loading);
    }
      else if(b_cataDown.isPressed()){
        setCatapultState(catapultStates::on);
      }
        else{
          setCatapultState(catapultStates::off);
        }
  }

//Intake Control
void intakeControl(){ //In a while loop
  if(b_intakeInPartner.isPressed()){//Partner
    setIntakeState(intakeStates::in);
  }
  else if(b_intakeOutPartner.isPressed()){
    setIntakeState(intakeStates::out);
  }
  else if(b_intakeIn.isPressed()){
    setIntakeState(intakeStates::in);
  }
  else if(b_intakeOut.isPressed()){
    setIntakeState(intakeStates::out);
  }
  else if(b_intakeToTop.isPressed()){
    setIntakeState(intakeStates::untilBallSensed);
  }
  else{
    setIntakeState(intakeStates::off);
  }
}

bool isMacroRunning = false;
void macroControl(){
  /*
  if(b_platformShoot.changedToPressed()){ //Aligned With Platform Far Shot
    isMacroRunning = true;
    while(abs(j_partner.getAnalog(ControllerAnalog::leftY)) < .1 && abs(j_partner.getAnalog(ControllerAnalog::rightY)) < .1 && (isMacroRunning == true) ){
      if(autonSide != -1){ //If Red
        //mg_driveL.moveRelative(50, 400); //Turn
        pidChassis.turnAngle(20_deg);
      }
      else if(autonSide == 1){ // Blue
        //mg_driveR.moveRelative(50, 400);
        pidChassis.turnAngle(-20_deg);
      }
      isMacroRunning = false;
    }
  }
  */
}
