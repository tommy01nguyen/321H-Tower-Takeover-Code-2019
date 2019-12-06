#include "main.h"
using namespace okapi;

//Ports
#define port_driveRF 1
#define port_driveRB 2
#define port_driveLF 8
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
Motor m_stacker(port_stacker, false, AbstractMotor::gearset::red , AbstractMotor::encoderUnits::degrees);
Motor m_lift(port_lift, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);


//Motor Group | allows for moving all these motors at once
MotorGroup mg_driveR({-port_driveRB,-port_driveRF});
MotorGroup mg_driveL({port_driveLB,port_driveLF});
MotorGroup mg_intake({port_intakeL, -port_intakeR});

//Okapi Chassis Controllers
ChassisControllerPID pidChassis = ChassisControllerFactory::create( //PID Controller
	{mg_driveL},{mg_driveR},
	IterativePosPIDController::Gains{.0011, 0, 0.0000008},//straight
  IterativePosPIDController::Gains{0, 0, 0}, //Angle PID (Stay Straight PID)
  IterativePosPIDController::Gains{.001, 0, 0.0000008}, //turns
  AbstractMotor::gearset::green,
  {1.71_in, 13_in}
);

AsyncMotionProfileController chassisProfile = AsyncControllerFactory::motionProfile( //Async 2D Motion Profile Controller
	3.0, 5.0, 30.0, pidChassis); //Max Velocity (m/s), Acceleration, and Jerk

//Test out adaptive tuning
const double testkP = 1.0;
const double testkI = .001;
const double testkD = .1;

AsyncPosPIDController pidLift = AsyncControllerFactory::posPID(port_lift, 0.001, 0.0, 0.0001);
AsyncPosPIDController pidStacker = AsyncControllerFactory::posPID(port_stacker, 0.001, 0.0, 0.0001);
AsyncPosPIDController pidDriveL = AsyncControllerFactory::posPID({mg_driveL}, .0011, 0, 0.0000008);
AsyncPosPIDController pidDriveR = AsyncControllerFactory::posPID({mg_driveR}, .0011, 0, 0.0000008);

void initializeRobot(){ //Initialize Robot Devices
	//Initialize Sensors
}
