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
extern int autonPark; //1 Park, 0 Not Parking
extern int autonDelay; //Adjusts auton to delay 1, 0
void Flag3Cap2Park(int side, int park, int delay);
void farAuton(int side, int park);
void flexible(int side);
void skills();
