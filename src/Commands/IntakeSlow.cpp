/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeSlow.h"
#include "../Robot.h"

IntakeSlow::IntakeSlow() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intakeSystem);

}

// Called just before this Command runs the first time
void IntakeSlow::Initialize() {
	Robot::intakeSystem->IntakeRoll(0.2);
}

// Called repeatedly when this Command is scheduled to run
void IntakeSlow::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeSlow::IsFinished() {
	return Robot::rungSystem->ropeState;
}

// Called once after isFinished returns true
void IntakeSlow::End() {
	Robot::intakeSystem->IntakeRoll(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeSlow::Interrupted() {
	End();
}
