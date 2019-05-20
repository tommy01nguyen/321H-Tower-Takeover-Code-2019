#pragma once
#include "main.h"
#include "okapi/api.hpp"


using namespace okapi;

//Controllers
extern Controller j_master;
extern Controller j_partner;

//Motors
extern Motor m_catapult;
extern Motor m_intake;
extern Motor m_driveRF;
extern Motor m_driveRM;
extern Motor m_driveRB;
extern Motor m_driveLF;
extern Motor m_driveLM;
extern Motor m_driveLB;

//Chassis Constants
extern const int wheelD;
extern const int chassisL;

//Motor Groups;
extern MotorGroup mg_driveR;
extern MotorGroup mg_driveL;

//Okapi Controllers
extern AsyncMotionProfileController chassisProfile;
extern AsyncMotionProfileController fastChassisProfile;
extern ChassisControllerPID pidChassis;
extern ChassisControllerPID slowPidChassis;


//Sensors
extern pros::ADIEncoder encL;
extern pros::ADIEncoder encR;

//Filter
//extern okapi::EmaFilter f_intakeFilter;

//Initialize Commands
void initializeRobot();
