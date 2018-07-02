/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LiftSystem.h"
#include "../RobotMap.h"
#include <CTRE/Phoenix.h>
#include <WPILib.h>

LiftSystem::LiftSystem() : Subsystem("LiftSystem") {
	frontRightLift = new TalonSRX(9);
	frontLeftLift = new TalonSRX(7);
	backRightLift = new TalonSRX(10);
	backLeftLift = new TalonSRX(6);

	lowerLimit = new DigitalInput(1);
	upperLimit  = new DigitalInput(0);
}

void LiftSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool LiftSystem::GetLowerLimitSwitch()
{
	return lowerLimit->Get();
}

bool LiftSystem::GetUpperLimitSwitch()
{
	return upperLimit->Get();
}

void LiftSystem::JoystickLift(double y)
{
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

	frontLeftLift->Set(ControlMode::PercentOutput, y);
	backLeftLift->Set(ControlMode::PercentOutput, y);
	frontRightLift->Set(ControlMode::PercentOutput, y);
	backRightLift->Set(ControlMode::PercentOutput, y);
}
