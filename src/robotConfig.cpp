#include "main.h"
using namespace okapi;

//Ports Broken: 19,20,13,15
#define port_driveRF 16
#define port_driveRB 17
#define port_driveLF 12
#define port_driveLB 5

#define port_intakeL 11
#define port_intakeR 7
#define port_stacker 6
#define port_lift 10

#define port_imu 4

//Controllers
Controller j_master = ControllerId::master;
Controller j_partner = ControllerId::partner;

//Motors | Port, Backward(true)/Forward , Gear Ratio, Encoder units
Motor m_driveRF(port_driveRF, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveRB(port_driveRB, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveLF(port_driveLF, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveLB(port_driveLB, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);

Motor m_intakeL(port_intakeL, true, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_intakeR(port_intakeR, false, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_stacker(port_stacker, false, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_lift(port_lift, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);


pros::ADILineSensor s_backIntakeSensor('C');
pros::ADILineSensor s_frontIntakeSensor('D');
pros::Imu s_imu(port_imu);

//Motor Group | allows for moving all these motors at once
MotorGroup mg_driveR({-port_driveRB,-port_driveRF});
MotorGroup mg_driveL({port_driveLB,port_driveLF});
MotorGroup mg_intake({-port_intakeL, port_intakeR});

void initializeSensors(){
	resetEncoders();
	s_backIntakeSensor.calibrate();
	s_frontIntakeSensor.calibrate();


	s_imu.reset();
	int time = pros::millis();
	int iter = 0;
	while (s_imu.is_calibrating()) {
		// printf("IMU calibrating... %d\n", iter);
		// iter += 10;
		pros::delay(10);
	}
	//should print about 2000 ms
	// printf("IMU is done calibrating (took %d ms)\n", iter - time);
	// pros::delay(1000);
}
