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
#include "Commands/LiftPIDControl.h"

LiftSystem::LiftSystem() : Subsystem("LiftSystem") {
	frontRightLift = new TalonSRX(9);
	frontLeftLift = new TalonSRX(7);
	backRightLift = new TalonSRX(10);
	backLeftLift = new TalonSRX(6);

	lowerLimit = new DigitalInput(1);
	upperLimit  = new DigitalInput(0);
	maxEncVal = 0;

	backLeftLift->SetInverted(false);
	frontLeftLift->SetInverted(false);
	backRightLift->SetInverted(true);
	frontRightLift->SetInverted(true);

	frontLeftLift->SetSensorPhase(true);
}

void LiftSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new LiftPIDControl());
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
		y = 0.17;
	}

	frontLeftLift->Set(ControlMode::PercentOutput, y);
	backLeftLift->Set(ControlMode::PercentOutput, y);
	frontRightLift->Set(ControlMode::PercentOutput, y);
	backRightLift->Set(ControlMode::PercentOutput, y);
	frc::SmartDashboard::PutNumber("Lift Encoder", frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));\
	frc::SmartDashboard::PutNumber("Front Left Motor", frontLeftLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Front Right Motor", frontRightLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Rear Left Motor", backLeftLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Rear Right Motor", backRightLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Max Encoder Value", maxEncVal);
	frc::SmartDashboard::PutNumber("y axis", y);
}

void LiftSystem::LiftPositionPID(double target)
{

}

void LiftSystem::ResetEncoder()
{
	frontLeftLift->SetSelectedSensorPosition(0,0,0);
}

double LiftSystem::GetEncoder()
{
	return frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

void LiftSystem::SetLiftMotors(double power)
{
	frontLeftLift->Set(ControlMode::PercentOutput, power);
	backLeftLift->Set(ControlMode::PercentOutput, power);
//	frontRightLift->Set(ControlMode::PercentOutput, power);
//	backRightLift->Set(ControlMode::PercentOutput, power);
}
