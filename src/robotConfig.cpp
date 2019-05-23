#include "main.h"
using namespace okapi;

//Ports
#define port_driveRF 5
#define port_driveRB 7
#define port_driveLF 15
#define port_driveLB 2

//Chassis Constants
const int wheelDiam = 4;
const int chassisLen = 12;

//Controllers
Controller j_master = ControllerId::master;
Controller j_partner = ControllerId::partner;

//Motors | Port, Backward(true)/Forward , Gear Ratio, Encoder units

Motor m_driveRF(port_driveRF, false, AbstractMotor::gearset::blue , AbstractMotor::encoderUnits::degrees);
Motor m_driveRB(port_driveRB, true, AbstractMotor::gearset::blue , AbstractMotor::encoderUnits::degrees);
Motor m_driveLF(port_driveLF, true, AbstractMotor::gearset::blue , AbstractMotor::encoderUnits::degrees);
Motor m_driveLB(port_driveLB, false, AbstractMotor::gearset::blue , AbstractMotor::encoderUnits::degrees);

//Motor Group | allows for moving all these motors at once
MotorGroup mg_driveR({-port_driveRB,-port_driveRF});
MotorGroup mg_driveL({port_driveLB,port_driveLF});

//Sensors
pros::ADIEncoder encL('A', 'B', false);
pros::ADIEncoder encR('C', 'D', false);

//Okapi Chassis Controllers
auto pidChassis = ChassisControllerFactory::create( //PID Controller
	{mg_driveL},{mg_driveR},
	IterativePosPIDController::Gains{.0011, 0, 0.0000008},
  IterativePosPIDController::Gains{0, 0, 0}, //Angle PID (Stay Straight PID)
  IterativePosPIDController::Gains{.001, 0, 0.0000008},
  AbstractMotor::gearset::blue,
  {1.71_in, 13_in}
);

auto slowPidChassis = ChassisControllerFactory::create(
	{mg_driveL},{mg_driveR},
  IterativePosPIDController::Gains{.0008, 0, 0.00000008},
  IterativePosPIDController::Gains{0, 0, 0},
  IterativePosPIDController::Gains{.0007, 0, 0.0000008}, //Slower Turn PID
  AbstractMotor::gearset::blue,
  {1.71_in, 13_in}
);


auto chassisProfile = AsyncControllerFactory::motionProfile( //Async 2D Motion Profile Controller
	2.0, 4.0, 23.0, pidChassis); //Max Velocity (m/s), Acceleration, and Jerk

auto fastChassisProfile = AsyncControllerFactory::motionProfile( //Faster
	3.0, 5.0, 30.0, pidChassis);


void initializeRobot(){ //Initialize Robot Devices
}
