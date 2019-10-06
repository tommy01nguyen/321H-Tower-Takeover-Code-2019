#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class driveStates{
  off, //0
  on, //1...
  automatic,
  loading,
  fireLoad,
};

void task_driveControl(void*);
void setDriveState(driveStates newDriveState);
