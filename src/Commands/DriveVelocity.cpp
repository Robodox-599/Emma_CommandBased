/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveVelocity.h"
#include "../Robot.h"

DriveVelocity::DriveVelocity() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveSystem);
}

// Called just before this Command runs the first time
void DriveVelocity::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveVelocity::Execute() {
	Robot::driveSystem->JoystickVelocityDrive(Robot::oi->xbox->GetRawAxis(4), Robot::oi->xbox->GetRawAxis(1));
}

// Make this return true when this Command no longer needs to run execute()
bool DriveVelocity::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveVelocity::End() {
	Robot::driveSystem->JoystickVelocityDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveVelocity::Interrupted() {
	End();
}
