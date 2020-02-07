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

extern pros::ADILineSensor s_backIntakeSensor;
extern pros::ADILineSensor s_frontIntakeSensor;
extern pros::Imu s_imu;

//Motor Groups;
extern MotorGroup mg_driveR;
extern MotorGroup mg_driveL;
extern MotorGroup mg_intake;

//Okapi Controllers
extern std::shared_ptr<okapi::AsyncMotionProfileController> chassisProfile;
extern std::shared_ptr<okapi::AsyncMotionProfileController> chassisProfileSlow;
extern std::shared_ptr<okapi::ChassisController> pidChassis;


//Initialize Commands
void initializeSensors();
