/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveSystem.h"
#include "../RobotMap.h"

DriveSystem::DriveSystem() : Subsystem("DriveSystem") {
	frontLeftMotor = new TalonSRX(4);
	rearLeftMotor = new TalonSRX(3);
	frontRightMotor = new TalonSRX(2);
	rearRightMotor = new TalonSRX(1);

	frontLeftMotor->SetInverted(true);
	rearLeftMotor->SetInverted(true);
	frontRightMotor->SetInverted(false);
	rearRightMotor->SetInverted(false);
}

void DriveSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveSystem::JoystickDrive(double x, double y)
{
	double l;
	double r;

	if(y > 0.2)
	{
		y = (y-0.2)*1/.8;
	}
	else if(y < -0.2)
	{
		y = (y+0.2)*1/.8;
	}
	else
	{
		y = 0;
	}

	if(x > 0.2)
	{
		x = (x-0.2)*1/.8;
	}
	else if(x < -0.2)
	{
		x = (x+0.2)*1/.8;
	}
	else
	{
		x = 0;
	}

	l = -y+x;
	r = -y-x;

	frontLeftMotor->Set(ControlMode::PercentOutput, l);
	rearLeftMotor->Set(ControlMode::PercentOutput, l);
	frontRightMotor->Set(ControlMode::PercentOutput, r);
	rearRightMotor->Set(ControlMode::PercentOutput, r);
}