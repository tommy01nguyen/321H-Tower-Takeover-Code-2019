#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void nearZone8Cube(int side){ //This the op op one

  //Start Up
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {50_in, 0_in, 0_deg}}, "through first row");
  flipout(); //flipout
  setintakeState(intakeStates::on, 12000);

  //First Row
  chassisProfile->setTarget("to first row");
  if(side == red) chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 20_in, 0_deg}}, "spline to second row");
  if(side == blue) chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, -20_in, 0_deg}}, "spline to second row");
  chassisProfile->waitUntilSettled();

  //Second Row
  chassisProfile->setTarget("spline to second row", true);
  chassisProfile->removePath("to first row");
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "through second row");
  chassisProfile->waitUntilSettled();
  chassisProfile->setTarget("through second row");
  chassisProfile->removePath("spline to second row");
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "out of second row");
  chassisProfile->waitUntilSettled();

  //Align with Zone
  chassisProfile->setTarget("out of second row", true);
  chassisProfile->removePath("through second row");
  chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "align with zone");
  setintakeState(intakeStates::on, 0);
  chassisProfile->waitUntilSettled();
  if(side == red) pidChassis->turnAngle(-83_deg);
  if(side == blue) pidChassis->turnAngle(91_deg);
  chassisProfile->setTarget("align with zone");
  chassisProfile->removePath("out of second row");
  chassisProfile->waitUntilSettled();

  //This better not fall
  stack();
  chassisProfile->removePath("align with zone");
  pidChassis->moveDistance(-10_in);
}
