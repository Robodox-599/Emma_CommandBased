/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimbUnlock.h"
#include "../Robot.h"

ClimbUnlock::ClimbUnlock() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::climbSystem);
}

// Called just before this Command runs the first time
void ClimbUnlock::Initialize() {
	Robot::climbSystem->ClimbUnlock();
}

// Called repeatedly when this Command is scheduled to run
void ClimbUnlock::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ClimbUnlock::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimbUnlock::End() {
	Robot::climbSystem->ClimbNeutral();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbUnlock::Interrupted() {
	End();
}
