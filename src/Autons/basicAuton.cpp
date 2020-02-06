#include "321Hlib/Autons/auton.h"

using namespace okapi;
#define red 1
#define blue -1
// pidChassis = ChassisControllerBuilder()
//                     .withMotors({mg_driveL},{mg_driveR})
//                     .withGains({.0003, 0, 0},{0, 0, 0},{0,0,0})//.0021, 0, 0.0000008
//                     .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 11.5_in}, imev5GreenTPR})
//                     .build();

void basicAuton(int side){
  //IMU TESTING
  // while(true){
  //   std::cout << "rotation: " << s_imu.get_rotation() << std::endl;
  //   std::cout << "heading: " <<  s_imu.get_heading()  << "!!!!!"<< std::endl;
  //   pros::delay(100);
  // }
  turnTo(90);
  //pros::delay(500);
  turnTo(-90);
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



// flipout();
// // Intake and Drive Forward
// setintakeState(intakeStates::on, 12000);
// pidChassis->moveDistance(35_in); //Up until past stack
// pros::delay(500);
// pidChassis->moveDistance(9_in);
// setintakeState(intakeStates::on, 0);
// //Drive Backwards
// pidChassis->moveDistance(-43_in);
// // Turn Towards Goal zone
// if(side == red) pidChassis->turnAngle(-83_deg);
// if(side == blue) pidChassis->turnAngle(91_deg);
// //Drive to Goal Zone
// pidChassis->moveDistance(28_in);
//
// // Score
// mg_intake.moveRelative(-50, 100);
// pros::delay(500);
// setstackerState(stackerStates::stackMacro); //Stack that
// pros::delay(500);
// pidChassis->moveDistance(-20_in);
}
