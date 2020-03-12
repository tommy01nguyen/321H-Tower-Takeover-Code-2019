#include "321Hlib/functions.h"

using namespace okapi;

void resetEncoders(){
  m_stacker.tarePosition();
  m_lift.tarePosition();
}

void skillFlipout(){
  setliftState(liftStates::highTower);
  //setintakeState(intakeStates::cubeLockMacro); //rotate
  setstackerState(stackerStates::raisedPreset);
  pros::delay(0);
  setintakeState(intakeStates::move);
  pros::delay(200);
  setstackerState(stackerStates::toBottomQuick);
  pros::delay(800);
  setliftState(liftStates::lowTower);
}

void flipout(){
  setliftState(liftStates::highTower);
  //setintakeState(intakeStates::cubeLockMacro); //rotate
  setstackerState(stackerStates::raisedPreset);
  pros::delay(0);
  setintakeState(intakeStates::move);
  pros::delay(200);
  setstackerState(stackerStates::toBottomQuick);
  pros::delay(800);
  setliftState(liftStates::noTower);
  pros::delay(500);//testing
}

void stack(){
  intakeStackMacroOn = true;
  setintakeState(intakeStates::readyToStack);
  pros::delay(300); //wait for intake to drop
  stackMacroOn = true;
  setstackerState(stackerStates::stackMacro);
  while(stackMacroOn){
    pros::delay(20);
  }
}

void stackSmall(){
  intakeStackMacroOn = true;
  setintakeState(intakeStates::readyToStackSmall);
  pros::delay(200); //wait for intake to drop
  stackMacroOn = true;
  setstackerState(stackerStates::autonMacro);
  while(stackMacroOn){
    pros::delay(20);
  }
}
void stackEleven(){

}

void waitForLift(int height){ //625, 490
  while(m_lift.getPosition() < height){
    pros::delay(20);
  }
}
