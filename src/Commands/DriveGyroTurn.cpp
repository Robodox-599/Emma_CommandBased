/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveGyroTurn.h"
#include "../Robot.h"

DriveGyroTurn::DriveGyroTurn(double angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveSystem);
	target = angle;
}

// Called just before this Command runs the first time
void DriveGyroTurn::Initialize() {
	Robot::driveSystem->SetGyroTarget(target);
	Robot::driveSystem->ResetGyroFlag();
}

// Called repeatedly when this Command is scheduled to run
void DriveGyroTurn::Execute() {
	Robot::driveSystem->GetYaw();
	Robot::driveSystem->GetGyroValues();
	Robot::driveSystem->GyroTurn(Robot::driveSystem->ReturnGyroTarget());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveGyroTurn::IsFinished() {
	return Robot::driveSystem->GetGyroFlag();
}

// Called once after isFinished returns true
void DriveGyroTurn::End() {
	Robot::driveSystem->ResetGyroFlag();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveGyroTurn::Interrupted() {
	End();
}
