#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "SystemControl/intakeTask.h"
#include "SystemControl/liftTask.h"
#include "SystemControl/stackerTask.h"
#include "SystemControl/driveTask.h"

using namespace okapi;

void resetEncoders();
void flipout();
void outOfStack();
void stack();
void waitForLift(int height);
