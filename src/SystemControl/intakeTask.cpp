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

double sensorVal;
int cubeSensValue = -300;
void task_intakeControl(void*){ //State Machine Task for Catapult Control
  while(true){
    //sensorVal = s_intakeSensor.get_value();
  sensorVal = s_intakeSensor.get_value_calibrated();
    switch(currentintakeState){

      case intakeStates::on:{  //intake at velocity
        m_intakeR.setBrakeMode(AbstractMotor::brakeMode::coast);
        m_intakeL.setBrakeMode(AbstractMotor::brakeMode::coast);
        m_intakeL.moveVoltage(intakeVoltage);
        m_intakeR.moveVoltage(intakeVoltage);
        break;
      }

      case intakeStates::waitOn:{ //Wait and then intake
        m_intakeR.setBrakeMode(AbstractMotor::brakeMode::coast);
        m_intakeL.setBrakeMode(AbstractMotor::brakeMode::coast);
        pros::delay(intakeWaitTime);
        setintakeState(intakeStates::on);
        break;
      }

      case intakeStates::onWait:{ //intake in and then stop
        m_intakeR.setBrakeMode(AbstractMotor::brakeMode::coast);
        m_intakeL.setBrakeMode(AbstractMotor::brakeMode::coast);
        m_intakeL.moveVoltage(intakeVoltage);
        m_intakeR.moveVoltage(intakeVoltage);
        pros::delay(intakeWaitTime);
        m_intakeL.moveVoltage(0);
        m_intakeR.moveVoltage(0);
        break;
      }
      case intakeStates::untilSensed:{
       m_intakeR.setBrakeMode(AbstractMotor::brakeMode::brake);
       m_intakeL.setBrakeMode(AbstractMotor::brakeMode::brake);
      std::cout << "intake" <<std::endl;
        std::cout << sensorVal << std:: endl;
        if(sensorVal > cubeSensValue){ //While the ball is not in the sensor
          m_intakeL.moveVoltage(12000);
          m_intakeR.moveVoltage(12000);
        }
        else{
          m_intakeL.moveVoltage(0);
          m_intakeR.moveVoltage(0);
        }
      }


    }
    pros::delay(20);
  }
}
