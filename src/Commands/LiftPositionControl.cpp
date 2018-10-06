/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LiftPositionControl.h"
#include "../Robot.h"

LiftPositionControl::LiftPositionControl(double position) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::liftSystem);
	target = position;
}

// Called just before this Command runs the first time
void LiftPositionControl::Initialize() {
	Robot::liftSystem->ResetLiftFlag();
}

// Called repeatedly when this Command is scheduled to run
void LiftPositionControl::Execute() {
	Robot::liftSystem->GetEncoder();
	if(Robot::liftSystem->GetLowerLimitSwitch() && Robot::liftSystem->GetTargetValue() < 0)
	{
		Robot::liftSystem->SetLiftMotors(0.17);
	}
	else if(Robot::liftSystem->GetUpperLimitSwitch() && Robot::liftSystem->GetTargetValue() > 0)
	{
		Robot::liftSystem->SetLiftMotors(0.17);
	}
	else
	{
		Robot::liftSystem->LiftPositionPID(target);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LiftPositionControl::IsFinished() {
	return Robot::liftSystem->GetLiftFlag();
}

// Called once after isFinished returns true
void LiftPositionControl::End() {
	Robot::liftSystem->SetLiftMotors(0.17);
	Robot::liftSystem->ResetLiftFlag();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftPositionControl::Interrupted() {

}
