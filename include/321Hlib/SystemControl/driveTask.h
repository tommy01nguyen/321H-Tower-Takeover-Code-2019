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

void turnTo(double newHeading);
void drive(double distance, int speed);
void drive(double distance, int speed, int yawInput);
void variableDrive(double distance, double dropDistance, int vi, int vf);
