#include "321Hlib/opcontrol.h"
// If no competition control is connected, this function will run immediately following initialize().

using namespace pros;

void opcontrol() {

	Odometry myOdom(12);
	lcd::initialize();

	while (true) {
		myOdom.update();
		if(j_master.getDigital(ControllerDigital::A)){
			lcd::print(2, "x: %f\n y: %f\n", myOdom.getX() , myOdom.getY() );
			lcd::print(3, "y: %f\n", myOdom.getY());
			lcd::print(4, "theta: %f\n", myOdom.getTheta());
		}
		pros::delay(5);
  }
}
