/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveAccDistance.h"
#include "Robot.h"

DriveAccDistance::DriveAccDistance(float feet, float inches, double acceleration) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveSystem);
	setFeet = feet;
	setInches = inches;
	setAcceleration = acceleration;
}

// Called just before this Command runs the first time
void DriveAccDistance::Initialize() {
	Robot::driveSystem->timer->Start();
	Robot::driveSystem->ResetDriveFlag();
}

// Called repeatedly when this Command is scheduled to run
void DriveAccDistance::Execute() {
	Robot::driveSystem->DriveAccDistance(setFeet, setInches, setAcceleration);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveAccDistance::IsFinished() {
	return Robot::driveSystem->isFinished;
}

// Called once after isFinished returns true
void DriveAccDistance::End() {
	Robot::driveSystem->DriveVelDistance(0, 0, 0, 0);
	Robot::driveSystem->timer->Stop();
	Robot::driveSystem->timer->Reset();
	Robot::driveSystem->ResetDriveFlag();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveAccDistance::Interrupted() {
	End();
}
