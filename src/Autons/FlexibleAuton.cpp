#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void flexible(int side){ //Flexible Unused, can be used for testing
    setintakeState(intakeStates::on, 12000);
    //variableDrive(28, 25, 180, 70, 2, 5);
    drive(20, 190, 2, 3);
    turnTo(90);

  }
