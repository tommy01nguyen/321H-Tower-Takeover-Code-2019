#include "321Hlib/SystemControl/stackerTask.h"

static stackerStates currentstackerState = stackerStates::on; //Defaulted Off

int stackerVoltage = 0;
int stackerWaitTime = 0;
void setstackerState(stackerStates newState){ //Set State of stacker
  currentstackerState = newState;
}
void setstackerState(stackerStates newState, int requestedVoltage){
  currentstackerState = newState;
  stackerVoltage = requestedVoltage;
}
void setstackerState(stackerStates newState, int requestedWaitTime, int requestedVoltage){
  currentstackerState = newState;
  stackerWaitTime = requestedWaitTime;
  stackerVoltage = requestedVoltage;
}


bool stackMacroOn = false;
void task_stackerControl(void*){ //State Machine Task for Stacker Control
  while(true){

    switch(currentstackerState){

      case stackerStates::on:{  //stacker at velocity
        m_stacker.moveVoltage(stackerVoltage);
        stackMacroOn = false;
        std::cout << stackerVoltage << std::endl;
        break;
      }

      case stackerStates::waitOn:{ //Wait and then stacker
        pros::delay(stackerWaitTime);
        setstackerState(stackerStates::on);
        stackMacroOn = false;
        break;
      }

      case stackerStates::onWait:{ //stacker in and then stop
        m_stacker.moveVoltage(stackerVoltage);
        pros::delay(stackerWaitTime);
        m_stacker.moveVoltage(0);
        stackMacroOn = false;
        break;
      }
      case stackerStates::towerScoring:{ //Rename
        m_stacker.moveAbsolute(140, 100);
        break;
      }
      case stackerStates::noTowerScoring:{//Rename
        pros::delay(300);
        m_stacker.moveAbsolute(0, 30);
        break;
      }

      case stackerStates::stackMacro:{


        m_stacker.moveAbsolute(300,100);
        while (!((m_stacker.getPosition() < 305) && (m_stacker.getPosition() > 295))) {
          pros::delay(2);//try 20?
        }
        m_stacker.moveAbsolute(400, 50);
        //reverse intake
        while (!((m_stacker.getPosition() < 405) && (m_stacker.getPosition() > 395))) {
          pros::delay(2);
        }
        //hold intake or cruise
        m_stacker.moveAbsolute(500, 20);

        /*Hold a button to start macro, release to end.
        if(stackMacroOn == false){ //Only runs when case is switched to stackMacro
          // pidStacker.setTarget(200); //Rapid Movement Up (Degrees)
          // pidStacker.waitUntilSettled();
          m_stacker.moveVoltage(2000); //Finishing Slow Voltage
        }
        if(b_stackMacro.changedToReleased()){
          setstackerState(stackerStates::on, 0); //Off
        }
        stackMacroOn = true;
        */
        break;
      }
    }
    pros::delay(20);
  }
}
