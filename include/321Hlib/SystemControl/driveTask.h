#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "systemControl.h"

enum class driveStates{
  tank,
  hold,
  turnPID,
  drivePID,
  outOfStack,
};

extern double drivePercent;
void task_driveControl(void*);
void setdriveState(driveStates newState);
void setdriveState(driveStates newState, double requestedPercent);

void turnTo(double newHeading, int speed = 195, int threshInput = 2, int iterationExit = 5);
void variableDrive(double distance, double changeDistanceOne, int v1, int v2, int threshInput = 2, int iterationExit = 5);
void drive(double distance, int speed = 195, int yawInput = 0, int threshInput = 2, int iterationExit = 5 );
