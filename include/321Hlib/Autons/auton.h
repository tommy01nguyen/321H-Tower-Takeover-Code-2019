#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/functions.h"
#include "321Hlib/SystemControl/intakeTask.h"
#include "321Hlib/SystemControl/liftTask.h"
#include "321Hlib/SystemControl/stackerTask.h"
#include "321Hlib/SystemControl/driveTask.h"

extern int autonNumber;
extern int autonSide; //1 Red, -1 Blue
void smallZone5Cube1Row(int side);
void smallZone6Cube1Row(int side);
void smallZone7Cube1Row(int side);
void smallZone9Cube2Row(int side);

void flexible(int side);
void skills();
void largeZone4Cube(int side);
void largeZone7Cube(int side);
