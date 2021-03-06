/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RungDeploy.h"
#include "../Robot.h"

RungDeploy::RungDeploy() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::rungSystem);
	Requires(Robot::climbSystem);
}

// Called just before this Command runs the first time
void RungDeploy::Initialize() {
	if(Robot::climbSystem->climbState && Robot::rungSystem->ropeState)
	{
		Robot::rungSystem->RungDeploy();
	}
}

// Called repeatedly when this Command is scheduled to run
void RungDeploy::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RungDeploy::IsFinished() {
	return Robot::rungSystem->rungState;
}

// Called once after isFinished returns true
void RungDeploy::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RungDeploy::Interrupted() {
	End();
}
