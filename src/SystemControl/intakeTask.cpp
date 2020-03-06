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


int cubeSensValueFront = -40;
int cubeSensValueBack = -40;
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
        //std::cout << getBackSensorVal() << std:: endl;
        std::cout << getFrontSensorVal() << std:: endl;
        if(getBackSensorVal() > cubeSensValueBack){ //While the cube is not in the sensor
          mg_intake.moveVoltage(12000);
        }
        else{
          mg_intake.moveVoltage(0);
        }
        break;
      }
      case intakeStates::holdEleventh:{ //Meant for picking up the 11th cube and holding it so it doesn't pop out the back.
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        //std::cout << getFrontSensorVal() << std:: endl;
        if(getFrontSensorVal() < cubeSensValueFront){ //while cube is in the sensor, intake in
          mg_intake.moveVoltage(12000);
        }
        else{ //hold when the cube is just outside the sensor
          mg_intake.moveVoltage(0);
        }
      }

      case intakeStates::toFrontSensor:{
          mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
          //std::cout << getFrontSensorVal() << std:: endl;
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
          mg_intake.moveVelocity(-130); //tune speed
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
