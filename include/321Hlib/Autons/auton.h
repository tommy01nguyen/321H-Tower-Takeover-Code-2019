#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/functions.h"
#include "321Hlib/SystemControl/intakeTask.h"
#include "321Hlib/SystemControl/liftTask.h"
#include "321Hlib/SystemControl/stackerTask.h"
#include "321Hlib/SystemControl/driveTask.h"

extern int autonNumber; //1 front auton
extern int autonSide; //1 Red, -1 Blue
void basicAuton(int side);
void farAuton(int side, int park); //nonexistent
void flexible(int side);
void skills();
