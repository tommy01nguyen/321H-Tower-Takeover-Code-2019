#include "321Hlib/SystemControl/systemControl.h"
using namespace okapi;

//Controller Buttons

//Master Controller
ControllerButton b_debug(ControllerDigital::A);
ControllerButton b_driveHold(ControllerDigital::B);
ControllerButton b_driveSlower(ControllerDigital::L1);

ControllerButton b_stackMacro(ControllerDigital::X); //extern

//Low Tower Macro
//High Tower Macro
//No Tower Macro
//Stacking Macro



//Partner Controller
ControllerButton b_intakeInP(ControllerId::partner, ControllerDigital::L2);
ControllerButton b_intakeOutP(ControllerId::partner, ControllerDigital::L1);

ControllerButton b_liftUpP(ControllerId::partner, ControllerDigital::R1);
ControllerButton b_liftDownP(ControllerId::partner, ControllerDigital::R2);

ControllerButton b_stackerUpP(ControllerId::partner, ControllerDigital::A);
ControllerButton b_stackerDownP(ControllerId::partner, ControllerDigital::X);


void systemControl(){ //State Machine for all Subsystems | In Opcontrol While Loop

  //INTAKE
  if(b_intakeInP.isPressed()){
    setintakeState(intakeStates::on, 12000);
  }
  else if(b_intakeOutP.isPressed()){
    setintakeState(intakeStates::on, -12000);
  }
  else{
    setintakeState(intakeStates::on, 0); //Off
  }

  //LIFT
  if(b_liftUpP.isPressed()){
    setliftState(liftStates::on, 12000);
  }
  else if(b_liftDownP.isPressed()){
    setliftState(liftStates::on, -12000);
  }
  else{
    setliftState(liftStates::on, 0); //Off
  }

  //STACKER
  if(b_stackerUpP.isPressed()){
    setstackerState(stackerStates::on, 12000);
  }
  else if(b_stackerDownP.isPressed()){
    setstackerState(stackerStates::on, -12000);
  }
  else{
    setstackerState(stackerStates::on, 0); //Off
  }

  //DRIVE
  if(b_driveSlower.isPressed()){
    setdriveState(driveStates::on, 0.65);
  }
  else if(b_driveHold.isPressed()){
    setdriveState(driveStates::hold);
  }
  else{
    setdriveState(driveStates::on, 1); //Off
  }

}
