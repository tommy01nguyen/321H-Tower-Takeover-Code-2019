#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "SystemControl/intakeTask.h"
#include "SystemControl/liftTask.h"
#include "SystemControl/stackerTask.h"
#include "SystemControl/driveTask.h"

using namespace okapi;

void resetEncoders();
double getL_in();
double getR_in();
double getM_in();
void driveWall(int voltage);

//QLength tilesToInches(double tiles);
void waitUntilStopped(int thresh);
bool isStopped(int thresh);
bool isDriving();
bool isLeftDriving();
bool isRightDriving();
void vectorWall(double voltage, double yaw);
