#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class driveStates{
  tank,
  hold,
  turnPID,
  outOfStack,
};

extern double drivePercent;
void task_driveControl(void*);
void setdriveState(driveStates newState);
void setdriveState(driveStates newState, double requestedPercent);
