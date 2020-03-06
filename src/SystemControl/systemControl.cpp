#include "321Hlib/SystemControl/systemControl.h"
using namespace okapi;

//Controller Buttons

//Master Controller: L trigger does intake, R trigger does drive functions. Right set of buttons is stacking. left set
//ControllerButton b_debug(ControllerDigital::right);//extern

//ControllerButton b_driveHold(ControllerDigital::left);
ControllerButton b_driveSlower(ControllerDigital::R1);
ControllerButton b_driveOutOfStack(ControllerDigital::B);//Move to stacker macro side

ControllerButton b_stackerUpSlow(ControllerDigital::X);
ControllerButton b_stackerDown(ControllerDigital::R2); //shared
ControllerButton b_stackMacro(ControllerDigital::Y); //extern
ControllerButton b_stackerRaisedPreset(ControllerDigital::A); //Up for deletion

ControllerButton b_intakeIn(ControllerDigital::L1); //shared
ControllerButton b_intakeOut(ControllerDigital::L2); //shared
ControllerButton b_intakeReadyToStack(ControllerDigital::right);

ControllerButton b_noTowerMacro(ControllerDigital::down);
ControllerButton b_highCubeLockMacro(ControllerDigital::up);
ControllerButton b_lowCubeLockMacro(ControllerDigital::left);

// ControllerButton b_test1(ControllerDigital::up);
// ControllerButton b_test2(ControllerDigital::left);

//Partner Controller: Triggers do intake and towers. Right button set does tower presets, left button set does intake presets
// ControllerButton b_lowTowerMacroP(ControllerId::partner, ControllerDigital::R2); //Up for deletion
// ControllerButton b_highTowerMacroP(ControllerId::partner, ControllerDigital::R1); //Up for deletion

ControllerButton b_liftUpP(ControllerId::partner, ControllerDigital::R1);
ControllerButton b_liftDownP(ControllerId::partner, ControllerDigital::R2);

ControllerButton b_intakeInP(ControllerId::partner, ControllerDigital::L2);
ControllerButton b_intakeOutP(ControllerId::partner, ControllerDigital::L1);

ControllerButton b_noTowerMacroP(ControllerId::partner, ControllerDigital::B);
ControllerButton b_highCubeLockMacroP(ControllerId::partner, ControllerDigital::X);
ControllerButton b_lowCubeLockMacroP(ControllerId::partner, ControllerDigital::A);
ControllerButton b_descoreMacroP(ControllerId::partner ,ControllerDigital::Y);

ControllerButton b_intakeEleventh(ControllerId::partner, ControllerDigital::right);
ControllerButton b_intakeUntilSensed(ControllerId::partner, ControllerDigital::down);
ControllerButton b_intakeOutSlow(ControllerId::partner, ControllerDigital::up);
ControllerButton b_intakeUntilFront(ControllerId::partner, ControllerDigital::left);

// ControllerButton b_test1P(ControllerId::partner, ControllerDigital::left);
// ControllerButton b_test2P(ControllerId::partner, ControllerDigital::right);


void systemControl(){ //State Machine for all Subsystems | In Opcontrol While Loop
  //TESTING

  // if(b_test1.isPressed()){
  //   //turnTo(0);
  //   drive(20, 190);
  //   //pros::delay(500);
  //   //drive(10, 150);
  //   // turnTo(90);
  //   // pros::delay(500);
  //   // turnTo(0);
  //   // drive(5, 150);
  //
  // }
  // else if(b_test2.isPressed()){
  //   drive(5, 190);
  //   //turnTo(90);
  // }

  //INTAKE
  if(b_intakeReadyToStack.isPressed()){
    setintakeState(intakeStates::readyToStack);
    intakeStackMacroOn = true;
  }
  else if(b_intakeUntilSensed.isPressed()){
    setintakeState(intakeStates::untilSensed);
  }
  else if(b_intakeOutSlow.isPressed()){
    setintakeState(intakeStates::on, -8000);
  }
  else if(b_intakeInP.isPressed() || b_intakeIn.isPressed()){
    setintakeState(intakeStates::on, 12000);
  }
  else if(b_intakeOutP.isPressed() || b_intakeOut.isPressed()){
    setintakeState(intakeStates::on, -12000);
  }
  else{
    setintakeState(intakeStates::on, 0); //Off
  }

  //LIFT

  if(b_highCubeLockMacroP.isPressed() || b_highCubeLockMacro.isPressed()){
    setliftState(liftStates::highTower);
    setintakeState(intakeStates::cubeLockMacro);//implement waitTime inside ready to Stack?
    //setintakeState(intakeStates::toFrontSensor);
    if(!((b_intakeOutSlow.isPressed() || b_intakeOutP.isPressed()))){
      setintakeState(intakeStates::cubeLockMacro);
    }
  }
  else if(b_lowCubeLockMacroP.isPressed() || b_lowCubeLockMacro.isPressed()){
    setliftState(liftStates::lowTower);
    if(!((b_intakeOutSlow.isPressed() || b_intakeOutP.isPressed()))){
      setintakeState(intakeStates::cubeLockMacro);
    }
  }
  // else if(b_lowTowerMacroP.isPressed()){
  //   setliftState(liftStates::lowTower);
  // }
  // else if(b_highTowerMacroP.isPressed()){
  //   setliftState(liftStates::highTower);
  // }
  else if(b_noTowerMacro.isPressed() || b_noTowerMacroP.isPressed()){
    setliftState(liftStates::noTower);
  }
  else if(b_liftUpP.isPressed()){
    setliftState(liftStates::on, 12000);
  }
  else if(b_liftDownP.isPressed()){
    setliftState(liftStates::on, -12000);
  }
  else{
    setliftState(liftStates::holdBottom);
  //  setliftState(liftStates::on, 0); //Off
  }

  //STACKER

  if(b_stackMacro.changedToReleased()){
    stackMacroOn = false;
    //std::cout << "released" << std::endl;
  }
  else if(b_stackMacro.isPressed()){
    setstackerState(stackerStates::stackMacro);
    stackMacroOn = true;
  }
  else if(b_stackerRaisedPreset.isPressed()){
    setstackerState(stackerStates::raisedPreset);
  }
  else if(b_stackerUpSlow.isPressed()){
    setstackerState(stackerStates::on, 5000);
  }
  else if(b_stackerDown.isPressed()){
    setstackerState(stackerStates::on, -12000);
  }
  else{
    setstackerState(stackerStates::on, 0); //Off
  }

  //DRIVE
  if(b_driveSlower.isPressed()){
    setdriveState(driveStates::tank, 0.45);
    drive(20, 180, -90);
  }
  // else if(b_driveHold.isPressed()){
  //   setdriveState(driveStates::hold);
  // }
  else if(b_driveOutOfStack.isPressed()){
    setdriveState(driveStates::outOfStack);
  }
  else{
    setdriveState(driveStates::tank, 1); //full speed
  }

}
