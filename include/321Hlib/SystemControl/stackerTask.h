#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class stackerStates{
  off, //0
  on, //1...
  automatic,
  loading,
  fireLoad,
};

void task_stackerControl(void*);
void setStackerState(stackerStates newStackerState);
