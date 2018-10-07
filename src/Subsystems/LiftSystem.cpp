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

//max lift = -30000

LiftSystem::LiftSystem() : Subsystem("LiftSystem") {
	frontRightLift = new TalonSRX(9);
	frontLeftLift = new TalonSRX(7);
	backRightLift = new TalonSRX(10);
	backLeftLift = new TalonSRX(6);

	lowerLimit = new DigitalInput(1);
	upperLimit  = new DigitalInput(0);
	maxEncVal = 0;

	lift.kf = 0.17;
	lift.kp = 0.0004;
	lift.ki = 0.00001;
	lift.kd = 0;
	lift.integrator = 0;
	targetValue = 0;

	backLeftLift->SetInverted(false);
	frontLeftLift->SetInverted(false);
	backRightLift->SetInverted(true);
	frontRightLift->SetInverted(true);

	frontLeftLift->SetSensorPhase(true);

	frontLeftLift->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 0);
	frontLeftLift->SetSelectedSensorPosition(0, 0, 0);
	frontLeftLift->Config_kF(0, 0.17, 10);

	liftSet = false;
	newTargetValue = 0;
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

void LiftSystem::LiftTalonPositionPID(double target)
{
	frontLeftLift->Set(ControlMode::PercentOutput, target);
	backLeftLift->Set(ControlMode::Follower, 7);
	frontRightLift->Set(ControlMode::Follower, 7);
	backRightLift->Set(ControlMode::Follower, 7);
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
	frontRightLift->Set(ControlMode::PercentOutput, power);
	backRightLift->Set(ControlMode::PercentOutput, power);
}

void LiftSystem::LiftJoystickPID(double joyValue)
{
	if(joyValue > 0.2)
	{
		joyValue = (joyValue - 0.2)*1/.8;
	}
	else if(joyValue < -0.2)
	{
		joyValue = (joyValue + 0.2)*1/.8;
	}
	else
	{
		joyValue = 0;
	}
	newTargetValue += joyValue * 200;
	LiftPositionPID(newTargetValue);
//	targetValue += target * 200;
//	lift.error = targetValue - GetEncoder();
//	lift.integrator += lift.error;
//	lift.motorPower = lift.kf + (lift.error * lift.kp) + lift.kd * (lift.error - lift.prevError) + (lift.ki * lift.integrator);
//	SetLiftMotors(lift.motorPower);
//	lift.prevError = lift.error;

	frc::SmartDashboard::PutNumber("Front Left Motor", frontLeftLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Front Right Motor", frontRightLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Rear Left Motor", backLeftLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Rear Right Motor", backRightLift->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("y axis", joyValue);
	frc::SmartDashboard::PutNumber("new target value", newTargetValue);
}

void LiftSystem::LiftPositionPID(double targetTicks)
{
	if(targetTicks > GetEncoder())
	{
		targetValue += 2;
		if (targetValue > targetTicks) { targetValue = targetTicks; }
	}
	if(targetTicks < GetEncoder())
	{
		targetValue -= 2;
		if (targetValue < targetTicks) { targetValue = targetTicks; }
	}
	if(targetTicks == GetEncoder())
	{
		targetValue += 0;
	}
	lift.error = targetValue - GetEncoder();
	lift.integrator += lift.error;
	lift.motorPower = lift.kf + (lift.error * lift.kp) + lift.kd * (lift.error - lift.prevError) + (lift.ki * lift.integrator);
	//SetLiftMotors(lift.motorPower);
	lift.prevError = lift.error;
	if(lift.error > -100 && lift.error < 100){liftSet = true;}
	frc::SmartDashboard::PutNumber("lift encoder value", GetEncoder());
	frc::SmartDashboard::PutNumber("desired lift value", targetTicks);
	frc::SmartDashboard::PutNumber("Increasing target value", targetValue);
	frc::SmartDashboard::PutNumber("motor output", lift.motorPower);
}

bool LiftSystem::GetLiftFlag()
{
	return liftSet;
}

void LiftSystem::ResetLiftFlag()
{
	liftSet = false;
}

double LiftSystem::GetTargetValue()
{
	return targetValue;
}

