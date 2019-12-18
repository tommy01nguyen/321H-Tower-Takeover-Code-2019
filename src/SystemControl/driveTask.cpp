#include "321Hlib/SystemControl/driveTask.h"

static driveStates currentdriveState = driveStates::on; //Defaulted Off

double drivePercent = 1;

void setdriveState(driveStates newState){ //Set State of drive
  currentdriveState = newState;
}
void setdriveState(driveStates newState, double requestedPercent){
  currentdriveState = newState;
  drivePercent = requestedPercent;
}


void task_driveControl(void*){ //State Machine Task for Catapult Control
  while(true){

    switch(currentdriveState){

      case driveStates::on:{  //drive at velocity
        if(mg_driveR.getBrakeMode() == AbstractMotor::brakeMode::hold){ //Change from Hold to Coast
          mg_driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
          mg_driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
        }
        pidChassis.tank(j_master.getAnalog(ControllerAnalog::leftY), //Tank control Normal
                        j_master.getAnalog(ControllerAnalog::rightY));
        break;
      }

      case driveStates::hold:{ //Brake And Hold
        mg_driveR.setBrakeMode(AbstractMotor::brakeMode::hold);
        mg_driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
        mg_driveR.moveVelocity(0);
        mg_driveL.moveVelocity(0);
        break;
      }
    }
    pros::delay(20);
  }
}
