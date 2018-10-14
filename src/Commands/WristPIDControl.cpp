/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/WristPIDControl.h>
#include "../Robot.h"

WristPIDControl::WristPIDControl() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::wristSystem);
}

// Called just before this Command runs the first time
void WristPIDControl::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void WristPIDControl::Execute() {
	Robot::wristSystem->UpdatePotVal();
	Robot::wristSystem->GetAvgPotVal();
	//Robot::wristSystem->HoldWristPosition();
	Robot::wristSystem->TestWristPID();
}

// Make this return true when this Command no longer needs to run execute()
bool WristPIDControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void WristPIDControl::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WristPIDControl::Interrupted() {

}
