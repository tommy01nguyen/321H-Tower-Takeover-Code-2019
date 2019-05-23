#pragma once
#include "main.h"
#include "321Hlib/robotConfig.h"
#include "321Hlib/functions.h"

using namespace okapi;
class Odometry{
  private:
    double x, y, theta, perpLen, prevL, prevR, prevTheta;

  public:
    Odometry(double perpL);
    double getX();
    double getY();
    double getTheta();
    void setX(double xNew);
    void setY(double yNew);
    void setTheta(double thetaNew);
    void resetState();
    void update();
};
