#include "321Hlib/SystemControl/liftTask.h"

static liftStates currentliftState = liftStates::on; //Defaulted Off

int liftVoltage = 0;
int liftWaitTime = 0;
void setliftState(liftStates newState){ //Set State of lift
  currentliftState = newState;
}
void setliftState(liftStates newState, int requestedVoltage){
  currentliftState = newState;
  liftVoltage = requestedVoltage;
}
void setliftState(liftStates newState, int requestedWaitTime, int requestedVoltage){
  currentliftState = newState;
  liftWaitTime = requestedWaitTime;
  liftVoltage = requestedVoltage;
}

void task_liftControl(void*){ //State Machine Task for Catapult Control
  while(true){

    switch(currentliftState){

      case liftStates::on:{  //lift at velocity
        m_lift.moveVoltage(liftVoltage);
        break;
      }

      case liftStates::waitOn:{ //Wait and then lift
        pros::delay(liftWaitTime);
        setliftState(liftStates::on);
        break;
      }

      case liftStates::onWait:{ //lift in and then stop
        m_lift.moveVoltage(liftVoltage);
        pros::delay(liftWaitTime);
        m_lift.moveVoltage(0);
        break;
      }
      case liftStates::noTower:{
        m_lift.moveAbsolute(0, 150);
        break;
      }
      case liftStates::lowTower:{
        m_lift.moveAbsolute(600, 200);
        break;
      }
      case liftStates::highTower:{
        m_lift.moveAbsolute(650, 200);
        break;
      }
    }
    pros::delay(20);
  }
}
