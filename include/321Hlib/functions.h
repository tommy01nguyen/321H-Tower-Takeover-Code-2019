#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"

using namespace okapi;

double getL_in();
double getR_in();
void driveWall(int voltage);

//QLength tilesToInches(double tiles);
void waitUntilStopped(int thresh);
bool isStopped(int thresh);
bool isDriving();
bool isLeftDriving();
bool isRightDriving();
void vectorWall(double voltage, double yaw);
