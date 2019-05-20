#include "321Hlib/odometry/odometry.h"

using namespace okapi;

class Odometry{
  private:
    double x, y, theta, perpL, chassisL;

  public:
    Odometry();
    double getX();
    double getY();
    double getTheta();
    void setX(double xNew);
    void setY(double yNew);
    void setTheta(double thetaNew);
    void resetState();
    void update();
};

Odometry::Odometry(){
  this->x = 0; //inches
  this->y = 0;
  this->theta = 0; //radians

  this->perpL = 10;
  this->chassisL = 10;
}

void Odometry::update(){
  double L = encL.get_value();
  
}

double Odometry::getX(){
  return this->x;
}
double Odometry::getY(){
  return this->y;
}
double Odometry::getTheta(){
  return this->theta;
}
void Odometry::setX(double xNew){
  this->x = xNew;
}
void Odometry::setY(double yNew){
  this->x = yNew;
}
void Odometry::setTheta(double thetaNew){
  this->x = thetaNew;
}
void Odometry::resetState(){
  this->x = 0;
  this->y = 0;
  this -> theta = 0;
}
