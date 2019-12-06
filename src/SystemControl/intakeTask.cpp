#include "321Hlib/SystemControl/intakeTask.h"

static intakeStates currentintakeState = intakeStates::on; //Defaulted Off

int intakeVoltage = 0;
int intakeWaitTime = 0;

void setintakeState(intakeStates newState){ //Set State of intake
  currentintakeState = newState;
}

void setintakeState(intakeStates newState, int requestedVoltage){
  currentintakeState = newState;
  intakeVoltage = requestedVoltage;
}

void setintakeState(intakeStates newState, int requestedWaitTime, int requestedVoltage){
  currentintakeState = newState;
  intakeWaitTime = requestedWaitTime;
  intakeVoltage = requestedVoltage;
}


void task_intakeControl(void*){ //State Machine Task for Catapult Control
  while(true){

    switch(currentintakeState){

      case intakeStates::on:{  //intake at velocity
        m_intakeL.moveVoltage(intakeVoltage);
        m_intakeR.moveVoltage(intakeVoltage);
        break;
      }

      case intakeStates::waitOn:{ //Wait and then intake
        pros::delay(intakeWaitTime);
        setintakeState(intakeStates::on);
        break;
      }

      case intakeStates::onWait:{ //intake in and then stop

        m_intakeL.moveVoltage(intakeVoltage);
        m_intakeR.moveVoltage(intakeVoltage);
        pros::delay(intakeWaitTime);
        m_intakeL.moveVoltage(0);
        m_intakeR.moveVoltage(0);
        break;
      }
    }
    pros::delay(20);
  }
}
