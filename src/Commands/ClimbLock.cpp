/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimbLock.h"
#include "../Robot.h"

ClimbLock::ClimbLock() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::climbSystem);
}

// Called just before this Command runs the first time
void ClimbLock::Initialize() {
	Robot::climbSystem->ClimbLock();
}

// Called repeatedly when this Command is scheduled to run
void ClimbLock::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ClimbLock::IsFinished() {
	return Robot::climbSystem->climbState;
}

// Called once after isFinished returns true
void ClimbLock::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbLock::Interrupted() {
	End();
}
