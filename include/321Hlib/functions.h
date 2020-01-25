#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "SystemControl/intakeTask.h"
#include "SystemControl/liftTask.h"
#include "SystemControl/stackerTask.h"
#include "SystemControl/driveTask.h"

using namespace okapi;

void resetEncoders();

void driveWall(int voltage);

//QLength tilesToInches(double tiles);
void waitUntilStopped(int thresh);
bool isStopped(int thresh);

bool isLeftDriving();
bool isRightDriving();
void vectorWall(double voltage, double yaw);

void driveTest(int distance, int speed);
void turn(int distance, int speed);

void flipout();
void outOfStack();
void stack();
