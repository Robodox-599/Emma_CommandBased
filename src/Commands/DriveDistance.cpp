/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveDistance.h"
#include "../Robot.h"

DriveDistance::DriveDistance(float feet, float inches, double maxVel, double time) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveSystem);
	setFeet = feet;
	setInches = inches;
	setVelocity = maxVel;
	setTime = time;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	Robot::driveSystem->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	Robot::driveSystem->DriveVelDistance(setFeet, setInches, setVelocity, setTime);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	return Robot::driveSystem->isFinished;
}

// Called once after isFinished returns true
void DriveDistance::End() {
	Robot::driveSystem->DriveVelDistance(0, 0, 0, 0);
	Robot::driveSystem->timer->Stop();
	Robot::driveSystem->timer->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() {
	End();
}
