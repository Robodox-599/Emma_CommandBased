/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "WristSetPosition.h"
#include "../Robot.h"

WristSetPosition::WristSetPosition(float target) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::wristSystem);
	angle = target;
}

// Called just before this Command runs the first time
void WristSetPosition::Initialize() {
	Robot::wristSystem->ResetWristFlag();
}

// Called repeatedly when this Command is scheduled to run
void WristSetPosition::Execute() {
	Robot::wristSystem->UpdatePotVal();
	Robot::wristSystem->GetAvgPotVal();
	Robot::wristSystem->SetWristTarget(angle);
	Robot::wristSystem->TestWristPID();
}

// Make this return true when this Command no longer needs to run execute()
bool WristSetPosition::IsFinished() {
	return Robot::wristSystem->WristFlag();
	printf("Robot received wrist flag\n");
}

// Called once after isFinished returns true
void WristSetPosition::End() {
	printf("Wrist Code Ended\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WristSetPosition::Interrupted() {
	End();
}
