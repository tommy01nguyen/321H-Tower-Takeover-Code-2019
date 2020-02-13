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

int frontSensorVal;
int backSensorVal;
int cubeSensValue = -100; //adjust for no calibration
void task_intakeControl(void*){ //State Machine Task for Catapult Control
  while(true){
    //sensorVal = s_intakeSensor.get_value();
  frontSensorVal = s_frontIntakeSensor.get_value_calibrated();
  backSensorVal = s_backIntakeSensor.get_value_calibrated();
    switch(currentintakeState){

      case intakeStates::on:{  //intake at velocity
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        mg_intake.moveVoltage(intakeVoltage);
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
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
      //  std::cout << backSensorVal << std:: endl;
        if(backSensorVal > cubeSensValue){ //While the cube is not in the sensor
          mg_intake.moveVoltage(12000);
        }
        else{
          mg_intake.moveVoltage(0);
        }
        break;
      }
      case intakeStates::readyToStack:{ //Tune sensor vals with flipout
        //Assumes cubes are past the back roller
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
        //std::cout << frontSensorVal << std:: endl;
        if(frontSensorVal > cubeSensValue ){//cube is not in the sensor
          mg_intake.moveVoltage(-4000);
        }
        else{
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
          mg_intake.moveVoltage(0);
        }
        break;
      }
      case intakeStates::cubeLockMacro:{
        //Assumes cubes are past the back roller
        mg_intake.setBrakeMode(AbstractMotor::brakeMode::brake);
        //std::cout << frontSensorVal << std:: endl;
        if(frontSensorVal > cubeSensValue ){//cube is not in the sensor
          mg_intake.moveVoltage(-8000); //tune speed
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
