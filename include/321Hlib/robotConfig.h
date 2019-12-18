#pragma once
#include "main.h"
using namespace okapi;

//Controllers
extern Controller j_master;
extern Controller j_partner;

//Motors
extern Motor m_stacker;
extern Motor m_lift;
extern Motor m_intakeR;
extern Motor m_intakeL;

extern Motor m_driveRF;
extern Motor m_driveRB;
extern Motor m_driveLF;
extern Motor m_driveLB;

//Motor Groups;
extern MotorGroup mg_driveR;
extern MotorGroup mg_driveL;

//Okapi Controllers
extern AsyncMotionProfileController chassisProfile;
extern ChassisControllerPID pidChassis;


//Initialize Commands
void initializeRobot();
