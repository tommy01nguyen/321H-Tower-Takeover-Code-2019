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
int cp1 = 250;
int cp2 = 400;
int cp3 = 550;
int cp4 = 700;
void task_stackerControl(void*){ //State Machine Task for Stacker Control
  while(true){

    switch(currentstackerState){
      case stackerStates::stackMacro:{

        while (m_stacker.getPosition() <= cp1){
          m_stacker.moveVoltage(12000);
          setintakeState(intakeStates::hold);
        }
        while ((m_stacker.getPosition() <= cp2) && m_stacker.getPosition() > cp1) {
          m_stacker.moveVoltage(9000);
          setintakeState(intakeStates::hold);
        }
         while ((m_stacker.getPosition() <= cp3) && m_stacker.getPosition() > cp2) {
           m_stacker.moveVoltage(6000);//4500
          setintakeState(intakeStates::hold);
         }
         while ((m_stacker.getPosition() <= cp4) && m_stacker.getPosition() > cp3) {
           m_stacker.moveVoltage(4000);//2500
           setintakeState(intakeStates::on, 12000);
         }
         m_stacker.moveVoltage(0);
        break;
      }
      case stackerStates::bigStackMacro:{

        while (m_stacker.getPosition() <= cp1){
          m_stacker.moveVoltage(10000);
          setintakeState(intakeStates::hold);
        }
        while ((m_stacker.getPosition() <= cp2) && m_stacker.getPosition() > cp1) {
          m_stacker.moveVoltage(5000);
          setintakeState(intakeStates::hold);
        }
         while ((m_stacker.getPosition() <= cp3) && m_stacker.getPosition() > cp2) {
           m_stacker.moveVoltage(4500);
          setintakeState(intakeStates::hold);
         }
         while ((m_stacker.getPosition() <= cp4) && m_stacker.getPosition() > cp3) {
           m_stacker.moveVoltage(2500);
           setintakeState(intakeStates::on, 12000);
         }
         m_stacker.moveVoltage(0);
        break;
      }

      case stackerStates::on:{  //stacker at velocity
        m_stacker.moveVoltage(stackerVoltage);
        stackMacroOn = false;
        //std::cout << stackerVoltage << std::endl;
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
        m_stacker.setBrakeMode(AbstractMotor::brakeMode::hold);
        m_stacker.moveAbsolute(200, 100);
        break;
      }
      case stackerStates::toBottom:{//Rename
        m_stacker.moveAbsolute(0, 30);
        break;
      }


    }
    pros::delay(20);
  }
}
