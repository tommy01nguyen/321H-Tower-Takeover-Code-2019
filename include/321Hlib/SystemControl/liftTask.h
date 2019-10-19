#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class liftStates{
  on,
  waitOn,
  onWait,
};

extern int liftWaitTime;
extern int liftVoltage;
void task_liftControl(void*);
void setLiftState(liftStates newState);
void setLiftState(liftStates newState, int requestedWaitTime, int requestedVoltage);
