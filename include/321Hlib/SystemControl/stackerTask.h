#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class stackerStates{
  on,
  waitOn,
  onWait,
  raisedPreset,
  toBottom,
  stackMacro,
  bigStackMacro,
};

extern int stackerWaitTime;
extern int stackerVoltage;
extern bool stackMacroOn;
void task_stackerControl(void*);
void setstackerState(stackerStates newState);
void setstackerState(stackerStates newState, int requestedVoltage);
void setstackerState(stackerStates newState, int requestedWaitTime, int requestedVoltage);
