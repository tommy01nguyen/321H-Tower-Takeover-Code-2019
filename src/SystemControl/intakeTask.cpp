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
int getFrontSensorVal(){
  return s_frontIntakeSensor.get_value_calibrated();
}
int getBackSensorVal(){
  return s_backIntakeSensor.get_value_calibrated();
}


int cubeSensValueFront = 2850;
int cubeSensValueBack = 2850;
bool tare = false;
bool intakeStackMacroOn = false;
bool movePassed = false;
bool lockMacroFinished = true;

void task_intakeControl(void*){ //State Machine Task for Catapult Control
  while(true){
    switch(currentintakeState){

      case intakeStates::on:{  //intake at velocity
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        mg_intake.moveVoltage(intakeVoltage);
        break;
      }
      case intakeStates::waitOn:{ //Wait and then intake
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        pros::delay(intakeWaitTime);
        setintakeState(intakeStates::on);
        break;
      }

      case intakeStates::onWait:{ //intake in and then stop
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        mg_intake.moveVoltage(intakeVoltage);
        pros::delay(intakeWaitTime);
        setintakeState(intakeStates::on, 0);
        break;
      }
      case intakeStates::untilSensed:{ //Meant picking up a cube to score in towers
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        if(getBackSensorVal() > cubeSensValueBack){ //While the cube is not in the sensor
          mg_intake.moveVoltage(12000);
        }
        else{
          mg_intake.moveVoltage(0);
        }
        break;
      }

      case intakeStates::toFrontSensor:{
          mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
          if(getFrontSensorVal() > cubeSensValueFront){
            mg_intake.moveVelocity(-80);
          }
          else{
            mg_intake.moveVoltage(0);
          }
        break;
      }
      case intakeStates::readyToStack:{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
        while(intakeStackMacroOn){

          if(intakeStackMacroOn == false){
            break;
          }
          else if((getFrontSensorVal() > cubeSensValueFront) && (tare == false) ){//cube is not in the sensor
            mg_intake.moveVelocity(-150);
          }
          else{
            if(tare == false){
              m_intakeR.tarePosition();
              tare = true;
            }
            if(m_intakeR.getPosition() >= -370){
              m_intakeR.moveVelocity(-50);
              m_intakeL.moveVelocity(-50);
            }
            else{
              tare = false;
              intakeStackMacroOn = false;
              mg_intake.moveVoltage(0);
              mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
            }
          }
          pros::delay(20);
        }
        break;
      }
      case intakeStates::readyToStackSmall:{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
        while(intakeStackMacroOn){

          if(intakeStackMacroOn == false){
            break;
          }
          else if((getFrontSensorVal() > cubeSensValueFront) && (tare == false) ){//cube is not in the sensor
            mg_intake.moveVelocity(-150);
          }
          else{
            if(tare == false){
              m_intakeR.tarePosition();
              tare = true;
            }
            if(m_intakeR.getPosition() >= -520){
              m_intakeR.moveVelocity(-70);
              m_intakeL.moveVelocity(-70);
            }
            else{
              tare = false;
              intakeStackMacroOn = false;
              mg_intake.moveVoltage(0);
              mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
            }
          }
          pros::delay(20);
        }
        break;
      }
      case intakeStates::cubeLockMacro:{
        //Assumes cubes are past the back roller
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
        pros::delay(0);
        if((!lockMacroFinished) && (getFrontSensorVal() > cubeSensValueFront)){//cube is not in the sensor
          mg_intake.moveVelocity(-200); 
        }
        else{
          lockMacroFinished = true;
          mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
          mg_intake.moveVoltage(0);
        }
        break;
      }
      case intakeStates::hold:{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        mg_intake.moveVelocity(0);
        break;
      }
      case intakeStates::move:{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        if(!movePassed){
          mg_intake.moveRelative(-700, 200);
          movePassed = true;
        }
        break;
      }
    }
    pros::delay(20);
  }
}
