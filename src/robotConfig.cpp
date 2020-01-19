#include "main.h"
using namespace okapi;

//Ports Broken: 19,20
#define port_driveRF 16
#define port_driveRB 17
#define port_driveLF 13
#define port_driveLB 15

#define port_intakeL 11
#define port_intakeR 7
#define port_stacker 6
#define port_lift 10

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





//Motor Group | allows for moving all these motors at once
MotorGroup mg_driveR({-port_driveRB,-port_driveRF});
MotorGroup mg_driveL({port_driveLB,port_driveLF});
MotorGroup mg_intake({port_intakeL, -port_intakeR});

//Okapi Chassis Controllers
std::shared_ptr<okapi::ChassisController> pidChassis = ChassisControllerBuilder()
										.withMotors({mg_driveL},{mg_driveR})
										.withGains({.0025, 0, 0.0000008}, {.0021, 0, 0.0000008})
										.withDimensions(AbstractMotor::gearset::green, {{4.125_in, 11.5_in}, imev5GreenTPR})
										.build();

std::shared_ptr<okapi::AsyncMotionProfileController> chassisProfile = AsyncMotionProfileControllerBuilder() //Async 2D Motion Profile Controller
 											 	.withLimits({3.0, 5.0, 10.0})
												.withOutput(pidChassis)
												.buildMotionProfileController();

std::shared_ptr<okapi::AsyncMotionProfileController> chassisProfileSlow = AsyncMotionProfileControllerBuilder() //Async 2D Motion Profile Controller
 											 	.withLimits({1.0, 2.0, 10.0})
												.withOutput(pidChassis)
												.buildMotionProfileController();


void initializeRobot(){ //Initialize Robot Devices
	//Initialize Sensors
	resetEncoders();
}
