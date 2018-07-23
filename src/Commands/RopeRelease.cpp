/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RopeRelease.h"
#include "../Robot.h"

RopeRelease::RopeRelease() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::rungSystem);
}

// Called just before this Command runs the first time
void RopeRelease::Initialize() {
	Robot::rungSystem->RopeRelease();
}

// Called repeatedly when this Command is scheduled to run
void RopeRelease::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RopeRelease::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RopeRelease::End() {
	Robot::rungSystem->RopeNeutral();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RopeRelease::Interrupted() {
	End();
}
