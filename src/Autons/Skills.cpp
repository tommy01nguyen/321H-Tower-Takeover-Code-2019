#include "321Hlib/Autons/auton.h"

using namespace okapi;

void skillsPartOne(){
  //Drive through 9 line, score alliance tower, place the stack down

  //flipout();
  setintakeState(intakeStates::on, 12000);
  drive(130, 100); //To end

  drive(-10, 150);
  turnTo(135, 150);

  //score tower
  setliftState(liftStates::lowTower);
  setintakeState(intakeStates::cubeLockMacro);
  drive(10, 150);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000);

  //Score in zone
  drive(-10, 150);
  turnTo(45, 190);
  drive(10, 150);

  stack();


}
void skillsPartTwo(){
  //Back out, score first high tower, and line up with next cube line
  setintakeState(intakeStates::on, -6000);
  drive(-20, 150);
  setintakeState(intakeStates::on, 12000);
  turnTo(-90, 150);

  //To High Tower & Score
  drive(40, 150);
  pros::delay(500);
  setliftState(liftStates::highTower);
  setintakeState(intakeStates::cubeLockMacro);
  pros::delay(1000);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000);

  //Out and line up with wall and cube line
  drive(-15, 150);
  turnTo(-180, 150);
  drive(-20, 150);
}

void skillsPartThree(){
  //Drive through first part of L intake line, score the small tower, intake second part, score a tower
  drive(50, 150);
  turnTo(-225, 150);

  //score tower
  setliftState(liftStates::highTower);
  setintakeState(intakeStates::cubeLockMacro);
  drive(10, 150);
  pros::delay(500);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000);

  //Realign, drive through line
  drive(-10, 150);
  turnTo(-180, 150);
  drive(80, 150);

  //Score high tower
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
  //Intake more cubes, score alliance tower, place stack down
}

void skills(){
  //Starts at Red, 4 line
  skillsPartOne();
  skillsPartTwo();
  skillsPartThree();
  skillsPartFour();

}
