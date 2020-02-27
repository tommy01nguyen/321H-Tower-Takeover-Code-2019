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


int cubeSensValueFront = -100;
int cubeSensValueBack = -100;
bool tare = false;
bool intakeStackMacroOn = false;
void task_intakeControl(void*){ //State Machine Task for Catapult Control
  while(true){
    switch(currentintakeState){

      case intakeStates::on:{  //intake at velocity
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        mg_intake.moveVoltage(intakeVoltage);
        //std::cout << "Sensor:" << frontSensorVal << std::endl;
        break;
      }
      case intakeStates::waitOn:{ //Wait and then intake
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        //intake off?
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
      case intakeStates::untilSensed:{ //Meant picking up a cube to score in towers //Tune sensor vals with flipout
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
      //  std::cout << backSensorVal << std:: endl;
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
      case intakeStates::readyToStack:{ //Tune sensor vals with flipout
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
        while(intakeStackMacroOn){

          if(intakeStackMacroOn == false){
            break;
          }
          else if((getFrontSensorVal() > cubeSensValueFront) && (tare == false) ){//cube is not in the sensor
            mg_intake.moveVelocity(-100);
            //std::cout << m_intakeR.getPosition() << std::endl;
            //std::cout << "Sensor:" << getFrontSensorVal() << std::endl;
          }
          else{
            if(tare == false){
              //std::cout << "TARED"<< std::endl;
              m_intakeR.tarePosition();
              tare = true;
            }
            if(m_intakeR.getPosition() >= -400){
              //std::cout << "LOOPING"<< std::endl;
              //std::cout << m_intakeR.getPosition() << std::endl;
              m_intakeR.moveVelocity(-30);
              m_intakeL.moveVelocity(-30);
            }
            else{
              //std::cout << "END"<< std::endl;
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
        //std::cout << frontSensorVal << std:: endl;
        if(getFrontSensorVal() > cubeSensValueFront){//cube is not in the sensor
          mg_intake.moveVoltage(-12000); //tune speed
        }
        else{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
          mg_intake.moveVoltage(0);
        }
        break;

      }
      case intakeStates::hold:{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        mg_intake.moveVelocity(0);
      }


    }
    pros::delay(20);
  }
}
