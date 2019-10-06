#include "321Hlib/odometry/odometry.h"

using namespace pros;

Odometry::Odometry(double perpLen, double centerToBackWheelLen){
  this->x = 0; //inches
  this->y = 0;
  this->theta = 0; //radians
  this->prevL = 0;
  this->prevR = 0;
  this->prevM = 0;
  this->prevTheta = 0;
  this->perpLen = perpLen;
  this->centerToBackWheelLen = centerToBackWheelLen;
}

double rollAngle180(double theta) { //thanks theo
  return theta - 6.2831 * std::floor((theta + 3.1415) / 6.2831);
}

void Odometry::update(){
    //Assumes robot moves in small arcs

    //Left and Right Distances
    double curL = getL_in();
    double curR = getR_in();
    double dl = curL - prevL;
    double dr = curR - prevR;
    double ds = (dl + dr) / 2; //Assumes tracking wheels are equidistant from center point

    //Change in angle
    double curTheta = (dl - dr) / perpLen;
    double dTheta = curTheta - prevTheta;
    lcd::print(4, "dl: %f\n dr: %f\n", dl,dr);
    dTheta = rollAngle180(dTheta);

    //Sideways Drift
    double curM = getM_in();
    double dm = curM - prevM; //total distance tracked
    double dmExtra = dTheta * centerToBackWheelLen;
    if(dm > 0){
      dm-= dmExtra; //Actual drift
    }
    else if(dm < 0){
      dm += dmExtra;
    }

    //find x and y component of chord
    double chordLen;
    double arcRadius;
    double dy;
    if(dTheta == 0){
      arcRadius = ds;
      chordLen = ds;
      dy = ds;
    }
    else{
      arcRadius = ds / dTheta; //  alt:(dr / dTheta) + (perpLen / 2); no need for ds
      chordLen = 2 * arcRadius * sin(dTheta / 2); //Hypotenuse
      dy = arcRadius * sin(dTheta); //Side Length 1 (finding dy)
    }

    double dx = sqrt(pow(chordLen, 2) - pow(dy,2)); // Pythagorean Thereom to find dx
    if((dy < 0 && dTheta > 0) || (dy > 0 && dTheta < 0)) {
      dx = -dx;
    }

    dy += dm * sin(dTheta); //Account for sideways drift
    dx += dm * cos(dTheta);

    if(chordLen == 0){ //uuhh delete? messes up 3rd encoder
      //dy = dx = 0;
    }
    //update position
    setX(getX() + dx);
    setY(getY() + dy);
    setTheta(getTheta() + dTheta);
    this->prevL = curL;
    this->prevR = curR;
    this->prevM = curM;
    this->prevTheta = curTheta;
    //lcd::clear();
    //lcd::print(2, "x: %f\n y: %f\n", getX() , getY());
    //lcd::print(4, "theta: %f\n", getTheta());
    lcd::print(1, "reL: %f\n reR: %f\n reM: %f\n", encL.get() , encR.get() , encM.get());
    lcd::print(2, "eL: %f\n eR: %f\n eM: %f\n", getL_in() , getR_in() , getM_in());
    lcd::print(3, "dx: %f\n dy: %f\n dTh: %f\n", dx, dy, dTheta);

    lcd::print(5, "x: %f\n y: %f\n th: %f\n", getX() , getY() , getTheta());
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
  this->y = yNew;
}
void Odometry::setTheta(double thetaNew){
  this->theta = thetaNew;
}
void Odometry::resetState(){
  this->x = 0;
  this->y = 0;
  this->theta = 0;
  this->prevL = 0;
  this->prevR = 0;
  this->prevM = 0;
  this->prevTheta = 0;
  resetEncoders();
}
