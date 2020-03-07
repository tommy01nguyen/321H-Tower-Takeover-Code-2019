#include "321Hlib/functions.h"

using namespace okapi;

void resetEncoders(){
  m_stacker.tarePosition();
  m_lift.tarePosition();
}

void flipout(){

  setliftState(liftStates::highTower);
  //setintakeState(intakeStates::cubeLockMacro); //rotate
  //setstackerState(stackerStates::raisedPreset);
  pros::delay(0);
  setintakeState(intakeStates::move);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  pros::delay(500);//testing
}

void stack(){
  intakeStackMacroOn = true;
  setintakeState(intakeStates::readyToStack);
  stackMacroOn = true;
  setstackerState(stackerStates::stackMacro);
  while(stackMacroOn){
    pros::delay(20);
  }
  setstackerState(stackerStates::toBottom);
}

void waitForLift(int height){ //625, 490
  while(m_lift.getPosition() < height){
    pros::delay(20);
  }
}
