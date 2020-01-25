#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void nearZone8Cube(int side){ //This the op op on
  //flipout();
  //pros::delay(300);
  // Intake and Drive Forward
  setintakeState(intakeStates::on, 12000);
  driveTest(1900, 140);
  pros::delay(300);
  if(side == red) turn(-40,-50);
  if(side == blue) turn(300,50);
  pros::delay(300);
  driveTest(1300, 200);
  pros::delay(300);
   //if(side == red) turn(1000,50);
  if(side == blue) turn(700,50);
  pros::delay(300);
  //
  // driveTest(1300,150);
  //
  // setintakeState(intakeStates::on, 0);
  // //Stack that
  // while (m_stacker.getPosition() <= 250){
  //   m_stacker.moveVoltage(10000);
  // }
  // //reverse intake
  // while ((m_stacker.getPosition() <= 400) && m_stacker.getPosition() > 250) {
  //   m_stacker.moveVoltage(5000);
  // }
  //  while ((m_stacker.getPosition() <= 550) && m_stacker.getPosition() > 400) {
  //    m_stacker.moveVoltage(3500);
  //  }
  //  while ((m_stacker.getPosition() <= 700) && m_stacker.getPosition() > 550) {
  //    m_stacker.moveVoltage(2500);
  //  }
  //
  // pros::delay(100);
  // setintakeState(intakeStates::on,-12000);
  // driveTest(-1500,-160);
  // setintakeState(intakeStates::on, 0);













  // flipout();
  // pros::delay(300);
  // // Intake and Drive Forward
  // setintakeState(intakeStates::on, 12000);
  // driveTest(3000, 80);
  // pros::delay(200);
  // driveTest(-1750, -120);
  //
  // pros::delay(100);
  // setintakeState(intakeStates::untilSensed, -12000);
  // if(side == red) turn(1000,50);
  // if(side == blue) turn(-900,-50);
  //
  // driveTest(1300,150);
  //
  // setintakeState(intakeStates::on, 0);
  // //Stack that
  // while (m_stacker.getPosition() <= 250){
  //   m_stacker.moveVoltage(10000);
  // }
  // //reverse intake
  // while ((m_stacker.getPosition() <= 400) && m_stacker.getPosition() > 250) {
  //   m_stacker.moveVoltage(5000);
  // }
  //  while ((m_stacker.getPosition() <= 550) && m_stacker.getPosition() > 400) {
  //    m_stacker.moveVoltage(3500);
  //  }
  //  while ((m_stacker.getPosition() <= 700) && m_stacker.getPosition() > 550) {
  //    m_stacker.moveVoltage(2500);
  //  }
  //
  // pros::delay(100);
  // setintakeState(intakeStates::on,-12000);
  // driveTest(-1500,-160);
  // setintakeState(intakeStates::on, 0);
  //




  // turn(500,120);
  // pros::delay(500);
  // turn(-500,-120);



   // // Turn Towards Goal zone
   // if(side == red)
   // if(side == blue) pidChassis->turnAngle(-140_deg);
   // //Drive to Goal Zone
   // pidChassis->moveDistance(15_in);
   //
   // // Score
   //
   // setintakeState(intakeStates::untilSensed, -12000);
   //
   // setstackerState(stackerStates::stackMacro); //Stack that
   // pros::delay(500);
   // pidChassis->moveDistance(-10_in);
   //


  // pros::delay(500);
  // pidChassis->moveDistance(10_in);
  // turn(1000,200);
  // flipout();



  //
  // //Start Up
  // chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {50_in, 0_in, 0_deg}}, "through first row");
  // flipout(); //flipout
  // setintakeState(intakeStates::on, 12000);
  //
  // //First Row
  // chassisProfile->setTarget("to first row");
  // if(side == red) chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 20_in, 0_deg}}, "spline to second row");
  // if(side == blue) chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, -20_in, 0_deg}}, "spline to second row");
  // chassisProfile->waitUntilSettled();
  //
  // //Second Row
  // chassisProfile->setTarget("spline to second row", true);
  // chassisProfile->removePath("to first row");
  // chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "through second row");
  // chassisProfile->waitUntilSettled();
  // chassisProfile->setTarget("through second row");
  // chassisProfile->removePath("spline to second row");
  // chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "out of second row");
  // chassisProfile->waitUntilSettled();
  //
  // //Align with Zone
  // chassisProfile->setTarget("out of second row", true);
  // chassisProfile->removePath("through second row");
  // chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {40_in, 0_in, 0_deg}}, "align with zone");
  // setintakeState(intakeStates::on, 0);
  // chassisProfile->waitUntilSettled();
  // if(side == red) pidChassis->turnAngle(-83_deg);
  // if(side == blue) pidChassis->turnAngle(91_deg);
  // chassisProfile->setTarget("align with zone");
  // chassisProfile->removePath("out of second row");
  // chassisProfile->waitUntilSettled();
  //
  // //This better not fall
  // stack();
  // chassisProfile->removePath("align with zone");
  // pidChassis->moveDistance(-10_in);
}
