#include "321Hlib/SystemControl/systemControl.h"
using namespace okapi;

//Controller Buttons

//Master Controller
ControllerButton b_debug(ControllerDigital::right);//extern

ControllerButton b_driveHold(ControllerDigital::left);
ControllerButton b_driveSlower(ControllerDigital::L1);

ControllerButton b_stackerUpSlow(ControllerDigital::X);
ControllerButton b_stackerUpVerySlow(ControllerDigital::A);
ControllerButton b_stackerDown(ControllerDigital::B); //shared
ControllerButton b_stackMacro(ControllerDigital::Y); //extern

ControllerButton b_intakeIn(ControllerDigital::R1); //shared
ControllerButton b_intakeOut(ControllerDigital::R2); //shared

ControllerButton b_liftUp(ControllerDigital::up);
ControllerButton b_liftDown(ControllerDigital::down);

//Partner Controller
ControllerButton b_lowTowerMacro(ControllerId::partner, ControllerDigital::R2);
ControllerButton b_highTowerMacro(ControllerId::partner, ControllerDigital::R1);
ControllerButton b_noTowerMacro(ControllerId::partner, ControllerDigital::A);

ControllerButton b_intakeInP(ControllerId::partner, ControllerDigital::L2);
ControllerButton b_intakeOutP(ControllerId::partner, ControllerDigital::L1);

ControllerButton b_liftUpP(ControllerId::partner, ControllerDigital::X);
ControllerButton b_liftDownP(ControllerId::partner, ControllerDigital::B);

ControllerButton b_stackerUpP(ControllerId::partner, ControllerDigital::up);
ControllerButton b_stackerDownP(ControllerId::partner, ControllerDigital::down);


void systemControl(){ //State Machine for all Subsystems | In Opcontrol While Loop

  //INTAKE
  if(b_intakeInP.isPressed() || b_intakeIn.isPressed()){
    setintakeState(intakeStates::on, 12000);
  }
  else if(b_intakeOutP.isPressed() || b_intakeOut.isPressed()){
    setintakeState(intakeStates::on, -12000);
  }
  else{
    setintakeState(intakeStates::on, 0); //Off
  }

  //LIFT
  if(b_liftUpP.isPressed() || b_liftUp.isPressed()){
    setliftState(liftStates::on, 12000);
  }
  else if(b_liftDownP.isPressed() || b_liftDown.isPressed()){
    setliftState(liftStates::on, -12000);
  }
  else if(b_lowTowerMacro.isPressed()){
    setliftState(liftStates::lowTower);
  }
  else if(b_highTowerMacro.isPressed()){
    setliftState(liftStates::highTower);
  }
  else if(b_noTowerMacro.isPressed()){
    setliftState(liftStates::noTower);
  }
  else{
    setliftState(liftStates::on, 0); //Off
  }

  //STACKER
  if(b_stackerUpSlow.isPressed()){
    setstackerState(stackerStates::on, 8000);
  }
  else if(b_stackerUpVerySlow.isPressed()){
    setstackerState(stackerStates::on, 6000);
  }
  else if(b_stackerUpP.isPressed()){
    setstackerState(stackerStates::on, 12000);
  }
  else if((b_stackerDownP.isPressed() || b_stackerDown.isPressed())){
    setstackerState(stackerStates::on, -12000);
  }
  else{
    setstackerState(stackerStates::on, 0); //Off
  }

  //DRIVE
  if(b_driveSlower.isPressed()){
    setdriveState(driveStates::tank, 0.45);
  }
  else if(b_driveHold.isPressed()){
    setdriveState(driveStates::hold);
  }
  else{
    setdriveState(driveStates::tank, 1); //full speed
  }

}
