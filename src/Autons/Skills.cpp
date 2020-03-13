

#include "321Hlib/Autons/auton.h"

using namespace okapi;

void skillsPartOne(){
  //Drive through 9 line, score alliance tower, place the stack down

  flipout();
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000);
  drive(115,65);
  //variableDrive(115,70,80,60);
  //Score in zone
  turnTo(45, 200);
  pros::delay(100);
  setintakeState(intakeStates::toFrontSensor);
  drive(15, 150);
  stack();
  pros::delay(1000); //in case stack tips back

}

void skillsPartTwo(){
  //Back out, score first high tower, and line up with next cube line
  setintakeState(intakeStates::on, -6000);
  setstackerState(stackerStates::toBottomQuick);
  pros::delay(200);
  drive(-18, 180); //bruh why so much slop here... may need to increase a bit?
  setintakeState(intakeStates::untilSensed);
  turnTo(-90, 200);

  //To High Tower & Score
  drive(28, 150);
  pros::delay(400);
  setliftState(liftStates::highTower);
  //pros::delay(800);
  waitForLift(625); //TESTING
  drive(5,150);

  setintakeState(intakeStates::on, -12000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  setintakeState(intakeStates::on, 12000);

  //Out and line up with wall and cube line
  drive(-8, 180);
  turnTo(-180, 180, 1 , 6); //2,5
}

void skillsPartThree(){
  //Drive through first part of L intake line, score the small tower, intake second part, score a tower

  //L line
  setintakeState(intakeStates::on,12000);
  drive(11, 70);
  pros::delay(500); //500 is super extra, just to be safe
  setliftState(liftStates::topCube);
  pros::delay(200);
  drive(5,50);
  //pros::delay(50);
  setliftState(liftStates::noTower);
  pros::delay(200);
  drive(13,190);
  pros::delay(100);

  //mid tower
  setliftState(liftStates::lowTower);
  lockMacroFinished = false;
  setintakeState(intakeStates::cubeLockMacro);
  turnTo(-220, 200); //-220,-40  Real, practice //adjust
  drive(9, 150);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  drive(-11, 180);
  setliftState(liftStates::noTower);
  lockMacroFinished = true;
  //Realign, drive through line
  setintakeState(intakeStates::on,12000);
  turnTo(-180, 200); //-180,0

  //2nd L
  drive(23, 150);
  setliftState(liftStates::topCube);
  pros::delay(150);
  drive(5,50);
  //pros::delay(50);
  setliftState(liftStates::noTower);
  pros::delay(200);
  drive(39,70); //slightly shorter?



  //Score high tower
  pros::delay(100); //increase in case we dont process cubes quickly
  setliftState(liftStates::highTower);
  lockMacroFinished = false;
  setintakeState(intakeStates::cubeLockMacro);
  turnTo(-90, 200); //-90, 90
  //pros::delay(500);
  drive(8, 150);
  pros::delay(200);
  setintakeState(intakeStates::on, -8000);
  pros::delay(1000);
  setliftState(liftStates::noTower);
  lockMacroFinished = true;
  setintakeState(intakeStates::on, 12000);
}
void skillsPartFour(){ //starts at offset -90 (adding +- 90 to all turns)

  drive(-33,200);
  //score alliance tower, place stack down
  setliftState(liftStates::lowTower); //slightly lwer? or lower intake speed
  setintakeState(intakeStates::cubeLockMacro);
  lockMacroFinished = false;
  turnTo(60, 200); //60 //tune angle

  //alliance tower
  drive(17, 190); //decrease?
  setintakeState(intakeStates::on, -6000);
  pros::delay(500);
  drive(-15,180);
  setliftState(liftStates::noTower);
  lockMacroFinished = true;
  setintakeState(intakeStates::on, 12000);

  turnTo(115, 200); //115
  setintakeState(intakeStates::toFrontSensor);
  drive(25,150);
  stackSmall();
  setstackerState(stackerStates::toBottomQuick);
  pros::delay(100);
  setintakeState(intakeStates::on, -6000);
  drive(-15, 200);
  setintakeState(intakeStates::on, 0);

}

void skills(){
  //Starts at Red, 4 line
  skillsPartOne();
  skillsPartTwo();
  skillsPartThree();
  skillsPartFour(); 

}
