/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeJoystick.h"
#include "../Robot.h"

IntakeJoystick::IntakeJoystick() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intakeSystem);
}

// Called just before this Command runs the first time
void IntakeJoystick::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void IntakeJoystick::Execute() {
	Robot::intakeSystem->IntakeRoll(.5 * (Robot::oi->atk3->GetRawAxis(2) - 1));
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void IntakeJoystick::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeJoystick::Interrupted() {
	End();
}
