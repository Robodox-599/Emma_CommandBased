/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/DriveShift.h>
#include "../Robot.h"

DriveShift::DriveShift() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveSystem);
}

// Called just before this Command runs the first time
void DriveShift::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveShift::Execute() {
	if(Robot::driveSystem->GetShift())
	{
		Robot::driveSystem->ShiftDown();
	}
	else
	{
		Robot::driveSystem->ShiftUp();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveShift::IsFinished() {
	if(Robot::driveSystem->GetShift())
	{
		return Robot::driveSystem->GetShift();
	}
	else
	{
		return !Robot::driveSystem->GetShift();
	}
}

// Called once after isFinished returns true
void DriveShift::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveShift::Interrupted() {
	End();
}
