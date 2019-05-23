#include "321Hlib/odometry/odometry.h"

using namespace okapi;

Odometry::Odometry(double perpL){
  this->x = 0; //inches
  this->y = 0;
  this->theta = 0; //radians
  this->prevL = 0;
  this->prevR = 0;
  this->prevTheta = 0;

  this->perpLen = perpL; //Perpendicular distance to tracking wheels
}

void Odometry::update(){

  double curL = getL_in();
  double curR = getR_in();

  //Change in left and right encoders
  double dl = curL - prevL;
  double dr = curR - prevR;
  double ds = (dl + dr) / 2; //Assumes tracking wheels are equidistant from center point
  //Change in angle

  double curTheta = (dl - dr) / perpLen;
  double dTheta = curTheta - prevTheta;

  //find x and y component of chord
  double arcRadius = ds / dTheta; //  alt:(dr / dTheta) + (perpLen / 2); no need for ds
  double chordLen = 2 * arcRadius * sin(dTheta / 2); //Hypotenuse
  double dy = arcRadius * sin(dTheta); //Side Length 1
  double dx = sqrt(pow(chordLen, 2) - pow(dy,2)); // Pythagorean Thereom

  //update position
  x += dx;
  y += dy;
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
  this->theta = 0;
  this->prevL = 0;
  this->prevR = 0;
  this->prevTheta = 0;
}
