#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class liftStates{
  on,
  waitOn,
  onWait,
  lowTower,
  highTower,
  noTower,
};

extern int liftWaitTime;
extern int liftVoltage;
void task_liftControl(void*);
void setliftState(liftStates newState);
void setliftState(liftStates newState, int requestedVoltage);
void setliftState(liftStates newState, int requestedWaitTime, int requestedVoltage);
