#pragma once
#include "main.h"
#include "okapi/api.hpp"


using namespace okapi;

//Controllers
extern Controller j_master;
extern Controller j_partner;

//Motors
extern Motor m_angler;
extern Motor m_lift;
extern Motor m_intakeR;
extern Motor m_intakeL;

extern Motor m_driveRF;
extern Motor m_driveRB;
extern Motor m_driveLF;
extern Motor m_driveLB;

//Chassis Constants
extern double trackWheelDiam;
extern double chassisL;

//Motor Groups;
extern MotorGroup mg_driveR;
extern MotorGroup mg_driveL;


//Okapi Controllers
extern AsyncMotionProfileController chassisProfile;
extern AsyncMotionProfileController fastChassisProfile;
extern ChassisControllerPID encChassis;
extern ChassisControllerPID pidChassis;
extern ChassisControllerPID slowPidChassis;


//Sensors
extern okapi::ADIEncoder encL;
extern okapi::ADIEncoder encR;
extern okapi::ADIEncoder encM;

//Filter
//extern okapi::EmaFilter f_intakeFilter;

//Initialize Commands
void initializeRobot();
