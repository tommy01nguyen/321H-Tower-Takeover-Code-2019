#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/functions.h"
#include "321Hlib/SystemControl/intakeTask.h"
#include "321Hlib/SystemControl/liftTask.h"
#include "321Hlib/SystemControl/stackerTask.h"
#include "321Hlib/SystemControl/driveTask.h"
#include "321Hlib/Autons/auton.h"

using namespace okapi;

void driveControl();
void catapultControl();
void intakeControl();
void macroControl();
void task_intakeControl(void*);
