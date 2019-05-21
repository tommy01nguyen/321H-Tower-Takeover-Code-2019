#include "321Hlib/odometry/odometry.h"

using namespace okapi;

class Odometry{
  private:
    double x, y, theta, perpL, prevL, prevR, prevTheta;

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
  this->prevL = 0;
  this->prevR = 0;
  this->prevTheta = 0;

  this->perpL = 10; //Perpendicular distance to tracking wheels
}

void Odometry::update(){
  //double curL, curR, dl, dr, curTheta, dTheta
  double curL = getL_in();
  double curR = getR_in();

  double dl = curL - prevL;
  double dr = curR - prevR;

  //find dx, dy
  //ouble dx =

  double curTheta = (dl - dr) / perpL ;
  double dTheta = curTheta - prevTheta;


  theta += dTheta;


  prevL = curL;
  prevR = curR;
  prevTheta = curTheta;

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
