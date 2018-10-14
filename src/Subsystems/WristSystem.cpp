/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/WristPIDControl.h>
#include "WristSystem.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"

WristSystem::WristSystem() : Subsystem("WristSystem") {
	wristMotor = new TalonSRX(11);
	pot = new AnalogPotentiometer(3, 200, -46);
	wristTarget = pot->Get();
	avgPotVal = 0;
	potVals[0] = 0;
	potVals[1] = 0;
	potVals[2] = 0;
	potVals[3] = 0;
	potVals[4] = 0;
	potVals[5] = 0;
	potVals[6] = 0;
	potVals[7] = 0;
	potVals[8] = 0;
	potVals[9] = 0;
	wrist.integrator = 0;
	wrist.kf = -0.40;
	wrist.kp = 0.025;
	wrist.ki = 0;
	wrist.kd = 0.25;
	wristMotor->ConfigOpenloopRamp(0.25, 0);
	wristSet = false;
}

void WristSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new WristPIDControl());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
double WristSystem::GetPotVal()
{
	return avgPotVal;
//	return pot->Get();
}

void WristSystem::UpdatePotVal()
{
	potVals[0] = potVals[1];
	potVals[1] = potVals[2];
	potVals[2] = potVals[3];
	potVals[3] = potVals[4];
	potVals[4] = potVals[5];
	potVals[5] = potVals[6];
	potVals[6] = potVals[7];
	potVals[7] = potVals[8];
	potVals[8] = potVals[9];
	potVals[9] = pot->Get();
}

void WristSystem::GetAvgPotVal()
{
	avgPotVal = (potVals[0] + potVals[1] + potVals[2] + potVals[3] + potVals[4] + potVals[5] + potVals[6] + potVals[7] + potVals[8] + potVals[9])/10;
}

void WristSystem::HoldWristPosition()
{
	double angle;
	angle = avgPotVal*(3.14/140)/*In parentheses - conversion from potentiometer value to radians*/;
	if(avgPotVal > -6)
	{
		wristMotor->Set(ControlMode::PercentOutput, -0.40*cos(angle));
	}
	else
	{
		wristMotor->Set(ControlMode::PercentOutput, 0);
	}
	frc::SmartDashboard::PutNumber("Wrist Motor Power Output", wristMotor->GetMotorOutputPercent());
}

void WristSystem::TestWristPID()
{
	double nkp = 0.0125;
	double angle = avgPotVal*(3.14/140);
	//double setTarget = -32.5*(target-1);
	wrist.error = avgPotVal - wristTarget;
	wrist.integrator += wrist.error;
	if(wrist.error < 0)
	{
		wrist.motorPower = (wrist.error * wrist.kp) + (wrist.kd * (wrist.error - wrist.prevError)) + (wrist.ki * wrist.integrator);
	}
	else
	{
		wrist.motorPower = (wrist.error * nkp) + (wrist.kd * (wrist.error - wrist.prevError)) + (wrist.ki * wrist.integrator);
	}
	if(avgPotVal < 0 && wristTarget < 0)
	{
		wristMotor->Set(ControlMode::PercentOutput, 0);
	}
	else
	{
		wristMotor->Set(ControlMode::PercentOutput, ((wrist.kf)*cos(angle))+wrist.motorPower);
	}
	if(wrist.error > -3 && wrist.error < 3){wristSet = true;}
	if(wristTarget < 0){wristSet = true;}
	wrist.prevError = wrist.error;
	frc::SmartDashboard::PutNumber("Wrist Motor Power Output", wristMotor->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Previous Error", wrist.prevError);
	frc::SmartDashboard::PutNumber("Target error", wrist.error);
	frc::SmartDashboard::PutNumber("wrist target", wristTarget);
}

bool WristSystem::WristFlag()
{
	return wristSet;
}

void WristSystem::ResetWristFlag()
{
	wristSet = false;
}

void WristSystem::SetWristTarget(double angle)
{
	wristTarget = angle;
}

bool WristSystem::WristTargetSet(double angle)
{
	if(wristTarget == angle)
	{
		return true;
	}
	else
	{
		return false;
	}
}
