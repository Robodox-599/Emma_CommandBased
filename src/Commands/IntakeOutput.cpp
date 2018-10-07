/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeOutput.h"
#include "../Robot.h"

IntakeOutput::IntakeOutput(float timeout) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intakeSystem);
	seconds = timeout;
}

// Called just before this Command runs the first time
void IntakeOutput::Initialize() {
	SetTimeout(seconds);
	Robot::intakeSystem->IntakeRoll(-1);
}

// Called repeatedly when this Command is scheduled to run
void IntakeOutput::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeOutput::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void IntakeOutput::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeOutput::Interrupted() {
	End();
}
