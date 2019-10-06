#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class liftStates{
  off, //0
  on, //1...
  automatic,
  loading,
  fireLoad,
};

void task_liftControl(void*);
void setLiftState(liftStates newLiftState);
