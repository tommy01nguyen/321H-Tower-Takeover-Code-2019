#include "321Hlib/opcontrol.h"
// If no competition control is connected, this function will run immediately following initialize().

using namespace okapi;

void opcontrol() {


	while (true) {


    //Subsystem Controls
    driveControl();
    catapultControl();
    intakeControl();
    macroControl();


		pros::delay(20);
  }
}
