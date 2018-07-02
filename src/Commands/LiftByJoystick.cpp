/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LiftByJoystick.h"
#include "../Robot.h"

LiftByJoystick::LiftByJoystick() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::liftSystem);
}

// Called just before this Command runs the first time
void LiftByJoystick::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LiftByJoystick::Execute() {
	Robot::liftSystem->JoystickLift(Robot::oi->atk3->GetRawAxis(1));
}

// Make this return true when this Command no longer needs to run execute()
bool LiftByJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LiftByJoystick::End() {
	Robot::liftSystem->JoystickLift(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftByJoystick::Interrupted() {
	End();
}
