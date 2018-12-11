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
	target = position;
	virtualJoystick = 0;
	accPosition = 2000;
	startingPosition = Robot::liftSystem->GetEncoder();
}

// Called just before this Command runs the first time
void LiftPositionControl::Initialize() {
	Robot::liftSystem->ResetLiftFlag();
}

// Called repeatedly when this Command is scheduled to run
void LiftPositionControl::Execute() {
	Robot::liftSystem->GetEncoder();
	if(Robot::liftSystem->GetEncoder() < (target+startingPosition)/2 && target > startingPosition)
	{
		virtualJoystick = (Robot::liftSystem->GetEncoder() - startingPosition + 400)/accPosition;
	}
	else if(Robot::liftSystem->GetEncoder() < target)
	{
		virtualJoystick = (target - Robot::liftSystem->GetEncoder())/accPosition;
	}
	if(Robot::liftSystem->GetEncoder() > (target+startingPosition)/2 && target < startingPosition)
	{
		virtualJoystick = (Robot::liftSystem->GetEncoder() - startingPosition - 400)/accPosition;
	}
	else if(Robot::liftSystem->GetEncoder() > target)
	{
		virtualJoystick = (Robot::liftSystem->GetEncoder() - target)/accPosition;
	}
	if(virtualJoystick > 1){virtualJoystick = 1;}
	if(virtualJoystick < -0.5){virtualJoystick = -0.5;}
//	if(target > Robot::liftSystem->GetEncoder())
//	{
//		virtualJoystick = 1;
//	}
//	if(target < Robot::liftSystem->GetEncoder())
//	{
//		virtualJoystick = -0.5;
//	}
	Robot::liftSystem->LiftJoystickPID(virtualJoystick);
	if(target - Robot::liftSystem->GetEncoder() > -350 && target - Robot::liftSystem->GetEncoder() < 350)
	{
		Robot::liftSystem->SetLiftFlag();
	}
	frc::SmartDashboard::PutNumber("Vitual Joystick", virtualJoystick);
	frc::SmartDashboard::PutNumber("Lift Position", Robot::liftSystem->GetEncoder());
	frc::SmartDashboard::PutNumber("Error", target-Robot::liftSystem->GetEncoder());
}

// Make this return true when this Command no longer needs to run execute()
bool LiftPositionControl::IsFinished() {
	return /*Robot::liftSystem->GetUpperLimitSwitch() || */Robot::liftSystem->GetLowerLimitSwitch() || Robot::liftSystem->GetLiftFlag();
}

// Called once after isFinished returns true
void LiftPositionControl::End() {
	Robot::liftSystem->setTargetValue(Robot::liftSystem->GetEncoder());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftPositionControl::Interrupted() {

}
