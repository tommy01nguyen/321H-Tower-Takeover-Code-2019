#include "321Hlib/SystemControl/intakeTask.h"

static intakeStates currentIntakeState = intakeStates::on; //Defaulted Off

int intakeVoltage = 0;
int intakeWaitTime = 0;
void setIntakeState(intakeStates newState){ //Set State of intake
  currentIntakeState = newState;
}
void setIntakeState(intakeStates newState, int requestedWaitTime, int requestedVoltage){
  currentIntakeState = newState;
  intakeWaitTime = requestedWaitTime;
  intakeVoltage = requestedVoltage;
}


void task_intakeControl(void*){ //State Machine Task for Catapult Control
  while(true){

    switch(currentIntakeState){

      case intakeStates::on:{  //Intake at velocity
        m_intake.moveVoltage(intakeVoltage);
        break;
      }

      case intakeStates::waitOn:{ //Wait and then Intake
        pros::delay(intakeWaitTime);
        setIntakeState(intakeStates::on);
        break;
      }

      case intakeStates::onWait:{ //Intake in and then stop

        m_intake.moveVoltage(intakeVoltage);
        pros::delay(intakeWaitTime);
        m_intake.moveVoltage(0);
        break;
      }
    }
    pros::delay(20);
  }
}
