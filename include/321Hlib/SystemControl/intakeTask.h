#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class intakeStates{
  on,
  waitOn,
  onWait,
  untilSensed,
  readyToStack,
  readyToStackSmall,
  hold,
  cubeLockMacro,
  toFrontSensor,
  move,

};
extern bool intakeStackMacroOn;
extern bool lockMacroFinished;

extern int intakeWaitTime;
extern int intakeVoltage;
extern int cubeSensValueFront;
extern int cubeSensValueBack;


void task_intakeControl(void*);
void setintakeState(intakeStates newState);
void setintakeState(intakeStates newState, int requestedVoltage);
void setintakeState(intakeStates newState, int requestedWaitTime, int requestedVoltage);
