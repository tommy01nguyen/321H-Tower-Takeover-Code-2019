#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/SystemControl/systemControl.h"

enum class intakeStates{
  off, //0
  in, //1...
  out,
  waitIn,
  inWait,
  waitOut,
  waitOutSlow,
  untilBallSensed,
  untilFilled,
};

extern int intakeWaitTime;
void task_intakeControl(void*);
void setIntakeState(intakeStates newIntakeState);
