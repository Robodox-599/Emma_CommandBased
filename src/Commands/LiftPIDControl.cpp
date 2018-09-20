/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LiftPIDControl.h"
#include "../Robot.h"

LiftPIDControl::LiftPIDControl() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::liftSystem);
}

// Called just before this Command runs the first time
void LiftPIDControl::Initialize() {
	Robot::liftSystem->ResetEncoder();
}

// Called repeatedly when this Command is scheduled to run
void LiftPIDControl::Execute() {
	//Robot::liftSystem->JoystickLift(Robot::oi->atk3->GetRawAxis(1));
	Robot::liftSystem->GetEncoder();
	//Robot::liftSystem->SetLiftMotors(0.17);
	if(Robot::oi->atk3->GetRawAxis(1) > 0 && Robot::liftSystem->GetUpperLimitSwitch())
	{
		//Robot::liftSystem->JoystickLift(0);
		Robot::liftSystem->LiftPositionPID(0);
		Robot::liftSystem->maxEncVal = Robot::liftSystem->GetEncoder();
	}
	else if(Robot::oi->atk3->GetRawAxis(1) < 0 && Robot::liftSystem->GetLowerLimitSwitch())
	{
		//Robot::liftSystem->JoystickLift(0);
		Robot::liftSystem->LiftPositionPID(0);
	}
	else
	{
		Robot::liftSystem->LiftPositionPID(Robot::oi->atk3->GetRawAxis(1));
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LiftPIDControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LiftPIDControl::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftPIDControl::Interrupted() {

}
