#include "321Hlib/functions.h"

using namespace okapi;
/*
double tileToIn(double tiles){ //Converts Tiles to inches (1 Tile = 24inches)
  double inches = tiles * 24;
  return inches;
}

QLength tilesToInches(double tiles){ //Converts Tiles To Inches
  return tiles*24*inch ;
}
*/


double getL_in(){
  return wheelD;
}

bool isDriving(){
  static int count = 0;
  static int lastPos = 0;
  int thresh = 5; //Tick Threshold tuning...
  int curPos = (abs(m_driveLF.getPosition() + abs(m_driveRF.getPosition()))/2); //Current Position
  if(abs(lastPos-curPos) < thresh){ //If change in position small enough
    count++;
  }
  else{
    count = 0;
  }
  lastPos = curPos;
  if(count > 4){ //If iterated for more than 4 counts
    return false; //Drive has stopped
  }
  else{
    return true;
  }
}


void waitUntilStopped(int thresh){
  pros::delay(200); //time to start movement
  while(!isStopped(thresh)){
    pros::delay(20);
  }
}

void driveWall(int voltage){ //Drives until it hits a wall
  mg_driveR.moveVoltage(voltage);
  mg_driveL.moveVoltage(voltage);
  while(isDriving()){
    pros::delay(20);
  }
  mg_driveR.moveVoltage(0);
  mg_driveL.moveVoltage(0);
}

void vectorWall(double voltage, double yaw){ //voltage -1 to 1. left + yaw, Right - yaw
  pidChassis.driveVector(voltage, yaw);
  waitUntilStopped(20);
  mg_driveR.moveVoltage(0);
  mg_driveL.moveVoltage(0);
}
