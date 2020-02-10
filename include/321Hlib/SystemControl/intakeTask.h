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
  hold,
  cubeLockMacro,

};

extern int intakeWaitTime;
extern int intakeVoltage;
void task_intakeControl(void*);
void setintakeState(intakeStates newState);
void setintakeState(intakeStates newState, int requestedVoltage);
void setintakeState(intakeStates newState, int requestedWaitTime, int requestedVoltage);
