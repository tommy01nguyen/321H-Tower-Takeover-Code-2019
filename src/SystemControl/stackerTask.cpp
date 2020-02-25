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
bool autonStackMacroOn = false;

int cpBigMacro[] = {240,400,500,700};    //2-11 Cubes
int velBigMacro[] = {12000,9000,6000,4000};

int cpSmallMacro[] = {250,400,500,700}; //7 Cubes and under
int velSmallMacro[] = {12000,9000,6000,4000};

void task_stackerControl(void*){ //State Machine Task for Stacker Control
  while(true){

    switch(currentstackerState){
      case stackerStates::stackMacro:{

        while(stackMacroOn){
          //std::cout << stackMacroOn << std::endl;
          if(stackMacroOn == false){
            break;
          }
          else if(m_stacker.getPosition() <= cpSmallMacro[0]){
            m_stacker.moveVelocity(velSmallMacro[0]);
            setintakeState(intakeStates::hold);
            //setintakeState(intakeStates::on, 4000);
          }
          else if((m_stacker.getPosition() <= cpSmallMacro[1]) && m_stacker.getPosition() > cpSmallMacro[0]) {
            m_stacker.moveVoltage(velSmallMacro[1]);
            setintakeState(intakeStates::hold);
              //setintakeState(intakeStates::on, 6000);
          }
          else if((m_stacker.getPosition() <= cpSmallMacro[2]) && m_stacker.getPosition() > cpSmallMacro[1]) {
            m_stacker.moveVoltage(velSmallMacro[2]);//4500
           setintakeState(intakeStates::hold);
             //setintakeState(intakeStates::on, 12000);
          }
          else if((m_stacker.getPosition() <= cpSmallMacro[3]) && m_stacker.getPosition() > cpSmallMacro[2]) {
            m_stacker.moveVoltage(velSmallMacro[3]);//2500
            setintakeState(intakeStates::on, 12000);
          }
          else{
            m_stacker.moveVoltage(0);
            //setdriveState(driveStates::outOfStack);
            //pros::delay(2000);
            stackMacroOn = false;
          }
          pros::delay(20);
        }
        break;
      }
      case stackerStates::bigMacro:{

              while(stackMacroOn){
                //std::cout << stackMacroOn << std::endl;
                if(stackMacroOn == false){
                  break;
                }
                else if(m_stacker.getPosition() <= cpBigMacro[0]){
                  m_stacker.moveVelocity(velBigMacro[0]);
                  setintakeState(intakeStates::hold);
                  //setintakeState(intakeStates::on, 4000);
                }
                else if((m_stacker.getPosition() <= cpBigMacro[1]) && m_stacker.getPosition() > cpBigMacro[0]) {
                  m_stacker.moveVoltage(velBigMacro[1]);
                  setintakeState(intakeStates::hold);
                    //setintakeState(intakeStates::on, 6000);
                }
                else if((m_stacker.getPosition() <= cpBigMacro[2]) && m_stacker.getPosition() > cpBigMacro[1]) {
                  m_stacker.moveVoltage(velBigMacro[2]);//4500
                 setintakeState(intakeStates::hold);
                   //setintakeState(intakeStates::on, 12000);
                }
                else if((m_stacker.getPosition() <= cpBigMacro[3]) && m_stacker.getPosition() > cpBigMacro[2]) {
                  m_stacker.moveVoltage(velBigMacro[3]);//2500
                  setintakeState(intakeStates::on, 12000);
                }
                else{
                  m_stacker.moveVoltage(0);
                  //setdriveState(driveStates::outOfStack);
                  //pros::delay(2000);
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


    }
    pros::delay(20);
  }
}
