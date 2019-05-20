#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/functions.h"
#include "321Hlib/SystemControl/intakeTask.h"
#include "321Hlib/SystemControl/catapultTask.h"
#include "321Hlib/auton.h"

using namespace okapi;

void driveControl();
void catapultControl();
void intakeControl();
void macroControl();
void task_intakeControl(void*);
