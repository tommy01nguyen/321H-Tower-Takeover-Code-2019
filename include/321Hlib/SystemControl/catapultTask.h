#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/SystemControl/systemControl.h"

enum class catapultStates{
  off, //0
  on, //1...
  automatic,
  loading,
  fireLoad,
};

void task_catapultControl(void*);
void setCatapultState(catapultStates newCatapultState);
