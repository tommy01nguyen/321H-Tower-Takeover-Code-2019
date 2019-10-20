#include "main.h"
using namespace okapi;

//Ports
//Dead: 1,3,10
#define port_driveRF 12
#define port_driveRB 11
#define port_driveLF 2
#define port_driveLB 7

#define port_intake 1
#define port_angler 19
#define port_liftL 9
#define port_liftR 20

//Chassis Constants
double trackWheelDiam = 2.75;
double chassisLen = 4.5;

//Controllers
Controller j_master = ControllerId::master;
Controller j_partner = ControllerId::partner;

//Motors | Port, Backward(true)/Forward , Gear Ratio, Encoder units
Motor m_driveRF(port_driveRF, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveRB(port_driveRB, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveLF(port_driveLF, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_driveLB(port_driveLB, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);

Motor m_intake(port_intake, true, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_angler(port_angler, true, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_liftL(port_liftL, true, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);
Motor m_liftR(port_liftR, false, AbstractMotor::gearset::green , AbstractMotor::encoderUnits::degrees);

//Motor Group | allows for moving all these motors at once
MotorGroup mg_driveR({-port_driveRB,port_driveRF});
MotorGroup mg_driveL({port_driveLB,-port_driveLF});
MotorGroup mg_lift({-port_liftL, port_liftR});

//Sensors
okapi::ADIEncoder encM('A', 'B', false); //currently doesnt exist on robot
okapi::ADIEncoder encR('E', 'F', true);
okapi::ADIEncoder encL('G', 'H', false);



//Okapi Chassis Controllers
auto encChassis = ChassisControllerFactory::create( //PID Controller
	{mg_driveL},{mg_driveR},
	encR,encL,
	IterativePosPIDController::Gains{.0011, 0, 0.0000008},
  IterativePosPIDController::Gains{0, 0, 0}, //Angle PID (Stay Straight PID)
  IterativePosPIDController::Gains{0, 0, 0},
  AbstractMotor::gearset::green,
  {2.75_in, 10_in}
);

auto pidChassis = ChassisControllerFactory::create( //PID Controller
	{mg_driveL},{mg_driveR},
	IterativePosPIDController::Gains{.0011, 0, 0.0000008},//straight
  IterativePosPIDController::Gains{0, 0, 0}, //Angle PID (Stay Straight PID)
  IterativePosPIDController::Gains{.001, 0, 0.0000008}, //turns
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
	encL.reset();
	encR.reset();
	encM.reset();
}
