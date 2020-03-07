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
//bool autonStackMacroOn = false;

int cpAutonMacro[] = {240,400,500,700};    //1-9 cubes
int velAutonMacro[] = {200,150,100,80};
//
// int cpMacro[] = {250,400,500,700}; //7 under Cubes
// int velMacro[] = {200,150,80,50};

int cpMacro[] = {250,400,500,700}; //5-11 Cubes
int velMacro[] = {200,90,60,40};

void task_stackerControl(void*){ //State Machine Task for Stacker Control
  while(true){

    switch(currentstackerState){
      case stackerStates::stackMacro:{

        while(stackMacroOn){
          //std::cout << stackMacroOn << std::endl;
          if(stackMacroOn == false){
            break;
          }
          else if(m_stacker.getPosition() <= cpMacro[0]){
            m_stacker.moveVelocity(velMacro[0]);
            setintakeState(intakeStates::hold);
            //setintakeState(intakeStates::on, 4000);
          }
          else if((m_stacker.getPosition() <= cpMacro[1]) && m_stacker.getPosition() > cpMacro[0]) {
            m_stacker.moveVelocity(velMacro[1]);
            setintakeState(intakeStates::hold);
              //setintakeState(intakeStates::on, 6000);
          }
          else if((m_stacker.getPosition() <= cpMacro[2]) && m_stacker.getPosition() > cpMacro[1]) {
            m_stacker.moveVelocity(velMacro[2]);
           setintakeState(intakeStates::hold);
             //setintakeState(intakeStates::on, 12000);
          }
          else if((m_stacker.getPosition() <= cpMacro[3]) && m_stacker.getPosition() > cpMacro[2]) {
            m_stacker.moveVelocity(velMacro[3]);
            setintakeState(intakeStates::on, 12000);
          }
          else{
            m_stacker.moveVoltage(0);
            stackMacroOn = false;
          }
          pros::delay(20);
        }
        break;
      }
      case stackerStates::autonMacro:{

              while(stackMacroOn){
                //std::cout << stackMacroOn << std::endl;
                if(stackMacroOn == false){
                  break;
                }
                else if(m_stacker.getPosition() <= cpAutonMacro[0]){
                  m_stacker.moveVelocity(velAutonMacro[0]);
                  setintakeState(intakeStates::hold);
                  //setintakeState(intakeStates::on, 4000);
                }
                else if((m_stacker.getPosition() <= cpAutonMacro[1]) && m_stacker.getPosition() > cpAutonMacro[0]) {
                  m_stacker.moveVelocity(velAutonMacro[1]);
                  setintakeState(intakeStates::hold);
                    //setintakeState(intakeStates::on, 6000);
                }
                else if((m_stacker.getPosition() <= cpAutonMacro[2]) && m_stacker.getPosition() > cpAutonMacro[1]) {
                  m_stacker.moveVelocity(velAutonMacro[2]);
                 setintakeState(intakeStates::hold);
                   //setintakeState(intakeStates::on, 12000);
                }
                else if((m_stacker.getPosition() <= cpAutonMacro[3]) && m_stacker.getPosition() > cpAutonMacro[2]) {
                  m_stacker.moveVelocity(velAutonMacro[3]);
                  setintakeState(intakeStates::on, 12000);
                }
                else{
                  m_stacker.moveVoltage(0);
                  stackMacroOn = false;
                }
                pros::delay(20);
              }
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
      case stackerStates::toBottomQuick:{
        m_stacker.moveAbsolute(0, 190);
      }


    }
    pros::delay(20);
  }
}
