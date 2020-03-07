#include "321Hlib/Autons/auton.h"

using namespace okapi;

void skillsPartOne(){
  //Drive through 9 line, score alliance tower, place the stack down

  //flipout();
  setintakeState(intakeStates::on, 12000);
  drive(110, 70);

  //Score in zone
  turnTo(45, 190);
  drive(10, 150);
  stack();

}

void skillsPartTwo(){
  //Back out, score first high tower, and line up with next cube line
  setintakeState(intakeStates::on, -6000);
  drive(-15, 150);
  setintakeState(intakeStates::untilSensed);
  turnTo(-90, 150);

  //To High Tower & Score
  drive(40, 150);
  pros::delay(500);
  setliftState(liftStates::highTower);
  pros::delay(1000);
  //waitForLift(625);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000);

  //Out and line up with wall and cube line
  drive(-20, 150);
  turnTo(-180, 150);
}

void skillsPartThree(){
  //Drive through first part of L intake line, score the small tower, intake second part, score a tower

  //L line
  setintakeState(intakeStates::on,12000);
  drive(10, 70);
  setliftState(liftStates::topCube);
  pros::delay(150);
  drive(5,50);
  pros::delay(100);
  setliftState(liftStates::noTower);
  pros::delay(300);
  drive(13,190);

  //mid tower
  turnTo(-225, 150);
  setliftState(liftStates::lowTower);
  setintakeState(intakeStates::cubeLockMacro);
  drive(10, 150);
  setintakeState(intakeStates::on, -8000);
  pros::delay(500);
  setliftState(liftStates::noTower);

  //Realign, drive through line
  setintakeState(intakeStates::on, -8000);
  drive(-10, 150);
  turnTo(-180, 150);

  //2nd L
  drive(23, 150);
  setintakeState(intakeStates::on,12000);
  setliftState(liftStates::topCube);
  pros::delay(150);
  drive(5,50);
  pros::delay(100);
  setliftState(liftStates::noTower);
  pros::delay(300);
  drive(35,70);



  //Score high tower
  //get cube on bottom first?
  turnTo(-90, 150);
  setliftState(liftStates::highTower);
  setintakeState(intakeStates::cubeLockMacro);
  drive(10, 150);
  pros::delay(500);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000); //watch out for cube underneath tower

}
void skillsPartFour(){

  //score alliance tower, place stack down
  drive(-40, 190);
  turnTo(45, 150);

  //alliance tower
  setliftState(liftStates::lowTower);
  setintakeState(intakeStates::cubeLockMacro);
  drive(20, 190);
  setintakeState(intakeStates::on, -8000);
  pros::delay(500);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000); //watch out for cube underneath tower

  //place stack down
  drive(-20,190);
  turnTo(135, 190);
  drive(20,150);
  stack();
  setintakeState(intakeStates::on, -6000);
  drive(-15, 150);

}

void skills(){
  //Starts at Red, 4 line


  //skillsPartOne();
  //skillsPartTwo();
  skillsPartThree();
  //skillsPartFour();

}
