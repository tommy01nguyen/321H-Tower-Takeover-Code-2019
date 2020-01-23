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
      case stackerStates::raisedPreset:{ //Rename
        m_stacker.moveAbsolute(140, 100);
        break;
      }
      case stackerStates::toBottom:{//Rename
        m_stacker.moveAbsolute(0, 30);
        break;
      }

      case stackerStates::stackMacro:{
        std::cout << m_stacker.getPosition() << std::endl;
        while (m_stacker.getPosition() < 250){
          m_stacker.moveVoltage(12000);
        }
        //reverse intake
        std::cout << m_stacker.getPosition() << std::endl;
        while (m_stacker.getPosition()< 400) {
          m_stacker.moveVoltage(7000);
        }
        //hold intake or cruise
        std::cout << m_stacker.getPosition() << std::endl;
        m_stacker.moveAbsolute(600, 20);

        break;
      }
    }
    pros::delay(20);
  }
}
