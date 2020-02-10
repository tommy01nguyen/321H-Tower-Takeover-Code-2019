#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void flexible(int side){ //Flexible Unused, can be used for testing
  //IMU TESTING
  //turnTo(90);
  //pros::delay(500);
  //turnTo(-90);
  // pros::delay(500);
  // turnTo(90);

  //TESTING MOTION PROFILING
  // chassisProfile->generatePath({{0_in, 0_in, 0_deg},  {40_in, 0_in, 0_deg}},"A");
  // pros::delay(500);
  // chassisProfile->setTarget("A");
  // chassisProfile->waitUntilSettled();

  //TESTING PID
// pidChassis->setMaxVelocity(160);
// pidChassis->moveDistance(20_in);
// pros::delay(500);
// pidChassis->moveDistance(10_in);

  // pidChassis->turnAngle(90_deg);
  // pros::delay(500);
  // pidChassis->turnAngle(-90_deg);


}
