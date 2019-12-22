#include "main.h"
using namespace okapi;

//Ports
#define port_driveRF 1
#define port_driveRB 2
#define port_driveLF 7
#define port_driveLB 10

#define port_intakeL 20
#define port_intakeR 19
#define port_stacker 11
#define port_lift 5

//Controllers
Controller j_master = ControllerId::master;
Controller j_partner = ControllerId::partner;

//Motors | Port, Backward(true)/Forward , Gear Ratio, Encoder units
Motor m_driveRF(port_driveRF, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveRB(port_driveRB, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveLF(port_driveLF, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveLB(port_driveLB, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);

Motor m_intakeL(port_intakeL, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_intakeR(port_intakeR, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_stacker(port_stacker, true, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_lift(port_lift, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);


//Motor Group | allows for moving all these motors at once
MotorGroup mg_driveR({-port_driveRB,-port_driveRF});
MotorGroup mg_driveL({port_driveLB,port_driveLF});
MotorGroup mg_intake({port_intakeL, -port_intakeR});

//Okapi Chassis Controllers
ChassisControllerPID pidChassis = ChassisControllerFactory::create( //PID Controller
	{mg_driveL},{mg_driveR},
	IterativePosPIDController::Gains{.0025, 0, 0.0000008},//straight
  IterativePosPIDController::Gains{0, 0, 0}, //Angle PID (Stay Straight PID)
  IterativePosPIDController::Gains{.0021, 0, 0.0000008}, //turns
  AbstractMotor::gearset::green,
  {4.125_in, 13_in}
);

AsyncMotionProfileController chassisProfile = AsyncControllerFactory::motionProfile( //Async 2D Motion Profile Controller
	3.0, 5.0, 30.0, pidChassis); //Max Velocity (m/s), Acceleration, and Jerk

AsyncMotionProfileController chassisProfileSlow = AsyncControllerFactory::motionProfile( //Async 2D Motion Profile Controller
	1.0, 2.0, 10.0, pidChassis); //Max Velocity (m/s), Acceleration, and Jerk


void initializeRobot(){ //Initialize Robot Devices
	//Initialize Sensors
	resetEncoders();
}
