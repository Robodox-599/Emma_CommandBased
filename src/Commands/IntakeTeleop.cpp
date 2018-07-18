/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeTeleop.h"
#include "../Robot.h"

IntakeTeleop::IntakeTeleop(float speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intakeSystem);
	motorSpeed = speed;
}

// Called just before this Command runs the first time
void IntakeTeleop::Initialize() {
	Robot::intakeSystem->IntakeRoll(motorSpeed);
}

// Called repeatedly when this Command is scheduled to run
void IntakeTeleop::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeTeleop::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void IntakeTeleop::End() {
	Robot::intakeSystem->IntakeRoll(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeTeleop::Interrupted() {
	End();
}
