/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveSystem.h"
#include "../RobotMap.h"
#include "Commands/DriveByJoystick.h"
#include "Commands/DriveVelocity.h"

DriveSystem::DriveSystem() : Subsystem("DriveSystem") {
	frontLeftMotor = new TalonSRX(2);
	rearLeftMotor = new TalonSRX(1);
	frontRightMotor = new TalonSRX(4);
	rearRightMotor = new TalonSRX(3);

	frontLeftMotor->SetInverted(true);
	rearLeftMotor->SetInverted(true);
	frontRightMotor->SetInverted(false);
	rearRightMotor->SetInverted(false);

	rearLeftMotor->SetSensorPhase(true);
	rearRightMotor->SetSensorPhase(false);

	rearLeftMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 0);
	rearRightMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 0);

	rearLeftMotor->SetSelectedSensorPosition(0, 0, 0);
	rearRightMotor->SetSelectedSensorPosition(0, 0, 0);

	rearLeftMotor->ConfigClosedloopRamp(0, 0);
	rearRightMotor->ConfigClosedloopRamp(0, 0);

	frontLeftMotor->ConfigClosedloopRamp(0, 0);
	frontRightMotor->ConfigClosedloopRamp(0, 0);

	rearLeftMotor->Config_kF(0, 0.33, 0);
	rearLeftMotor->Config_kP(0, 0.63, 0);
	rearLeftMotor->Config_kI(0, 0, 0);
	rearLeftMotor->Config_kD(0, 0, 0);

	rearRightMotor->Config_kF(0, 0.33, 0);
	rearRightMotor->Config_kP(0, 0.63, 0);
	rearRightMotor->Config_kI(0, 0, 0);
	rearRightMotor->Config_kD(0, 0, 0);

	frontLeftMotor->Config_kF(0, 0.33, 0);
	frontLeftMotor->Config_kP(0, 0.63, 0);
	frontLeftMotor->Config_kI(0, 0, 0);
	frontLeftMotor->Config_kD(0, 0, 0);

	frontRightMotor->Config_kF(0, 0.33, 0);
	frontRightMotor->Config_kP(0, 0.63, 0);
	frontRightMotor->Config_kI(0, 0, 0);
	frontRightMotor->Config_kD(0, 0, 0);

	shifter = new DoubleSolenoid(4, 5);
	shifter->Set(DoubleSolenoid::kForward);
	shift = false;//false shift = low gear(Shifted Down)
}

void DriveSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new DriveByJoystick());
	SetDefaultCommand(new DriveVelocity());
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

	l = y-x;
	r = y+x;

	frontLeftMotor->Set(ControlMode::PercentOutput, l);
	rearLeftMotor->Set(ControlMode::PercentOutput, l);
	frontRightMotor->Set(ControlMode::PercentOutput, r);
	rearRightMotor->Set(ControlMode::PercentOutput, r);

	frc::SmartDashboard::PutNumber("Rear Left Drive Encoder", rearLeftMotor->GetSelectedSensorPosition(QuadEncoder));
	frc::SmartDashboard::PutNumber("Rear Right Drive Encoder", rearRightMotor->GetSelectedSensorPosition(QuadEncoder));
}

void DriveSystem::ShiftUp()
{
	shifter->Set(DoubleSolenoid::kReverse);
	shift = true;
}

void DriveSystem::ShiftDown()
{
	shifter->Set(DoubleSolenoid::kForward);
	shift = false;
}

void DriveSystem::JoystickVelocityDrive(double x, double y)
{
	double l;
	double r;

	if(y > 0.2)
	{
		y = (y-0.2)*(1/.8)*3100/**max velocity*/;
	}
	else if(y < -0.2)
	{
		y = (y+0.2)*1/.8*3100/**max velocity*/;
	}
	else
	{
		y = 0;
	}

	if(x > 0.2)
	{
		x = (x-0.2)*1/.8*3100/**max velocity*/;
	}
	else if(x < -0.2)
	{
		x = (x+0.2)*1/.8*3100/**max velocity*/;
	}
	else
	{
		x = 0;
	}

	l = -y+x;
	r = -y-x;

	frontLeftMotor->Set(ControlMode::Follower, 1);
	rearLeftMotor->Set(ControlMode::Velocity, l);
	frontRightMotor->Set(ControlMode::Follower, 3);
	rearRightMotor->Set(ControlMode::Velocity, r);

	frc::SmartDashboard::PutNumber("Power input left", l);
	frc::SmartDashboard::PutNumber("Power input right", r);
	frc::SmartDashboard::PutNumber("Rear Left Drive Encoder", rearLeftMotor->GetSelectedSensorPosition(QuadEncoder));
	frc::SmartDashboard::PutNumber("Rear Right Drive Encoder", rearRightMotor->GetSelectedSensorPosition(QuadEncoder));
	frc::SmartDashboard::PutNumber("Closed Loop Error", rearLeftMotor->GetClosedLoopError(0));
	frc::SmartDashboard::PutNumber("Rear Left Velocity", rearLeftMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Rear Right Velocity", rearRightMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Velocity Error", rearLeftMotor->GetSelectedSensorVelocity(0) - rearRightMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Encoder Error", rearLeftMotor->GetSelectedSensorPosition(QuadEncoder) - rearRightMotor->GetSelectedSensorPosition(QuadEncoder));
}
