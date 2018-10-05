/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveSystem.h"
#include "Commands/DriveByJoystick.h"
#include "Commands/DriveVelocity.h"

//6 inch wheels, 3000u/100ms low gear, 6800u/100ms high gear, 7650ticks/revolution

DriveSystem::DriveSystem() : Subsystem("DriveSystem") {
	timer = new Timer;

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

	float seconds = 0.15;

	rearLeftMotor->ConfigClosedloopRamp(seconds, 0);
	rearRightMotor->ConfigClosedloopRamp(seconds, 0);
	frontLeftMotor->ConfigClosedloopRamp(seconds, 0);
	frontRightMotor->ConfigClosedloopRamp(seconds, 0);

	float kp = 0.8;
	float ki = 0.004;

	rearLeftMotor->Config_kF(0, 0.45, 0);
	rearLeftMotor->Config_kP(0, kp, 0);
	rearLeftMotor->Config_kI(0, ki, 0);
	rearLeftMotor->Config_kD(0, 0, 0);

	rearRightMotor->Config_kF(0, 0.45, 0);
	rearRightMotor->Config_kP(0, kp, 0);
	rearRightMotor->Config_kI(0, ki, 0);
	rearRightMotor->Config_kD(0, 0, 0);

	frontLeftMotor->Config_kF(0, 0.45, 0);
	frontLeftMotor->Config_kP(0, kp, 0);
	frontLeftMotor->Config_kI(0, ki, 0);
	frontLeftMotor->Config_kD(0, 0, 0);

	frontRightMotor->Config_kF(0, 0.45, 0);
	frontRightMotor->Config_kP(0, kp, 0);
	frontRightMotor->Config_kI(0, ki, 0);
	frontRightMotor->Config_kD(0, 0, 0);

	shifter = new DoubleSolenoid(4, 5);
	shifter->Set(DoubleSolenoid::kForward);
	shift = false;//false shift = low gear(Shifted Down)

	setTime = false;

	decelerate = 0;

	distanceError = 400;

	isFinished = false;

	pGyon = new PigeonIMU(frontLeftMotor);
	pGyon->SetYaw(0, 0);

	gyro.kf = 0;
	gyro.kp = 0;
	gyro.ki = 0;
	gyro.kd = 0;
	gyro.integrator = 0;
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

bool DriveSystem::GetShift()
{
	return shift;
}

void DriveSystem::JoystickVelocityDrive(double x, double y)
{
	double l;
	double r;

	if(y > 0.2)
	{
		y = (y-0.2)*(1/.8)*1500/**max velocity*/;
	}
	else if(y < -0.2)
	{
		y = (y+0.2)*1/.8*1500/**max velocity*/;
	}
	else
	{
		y = 0;
	}

	if(x > 0.2)
	{
		x = (x-0.2)*1/.8*1500/**max velocity*/;
	}
	else if(x < -0.2)
	{
		x = (x+0.2)*1/.8*1500/**max velocity*/;
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
	frc::SmartDashboard::PutNumber("Closed Loop Error Left", rearLeftMotor->GetClosedLoopError(0));
	frc::SmartDashboard::PutNumber("Closed Loop Error Right", rearRightMotor->GetClosedLoopError(0));
	frc::SmartDashboard::PutNumber("Rear Left Velocity", rearLeftMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Rear Right Velocity", rearRightMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Velocity Error", rearLeftMotor->GetSelectedSensorVelocity(0) - rearRightMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Encoder Error", rearLeftMotor->GetSelectedSensorPosition(QuadEncoder) - rearRightMotor->GetSelectedSensorPosition(QuadEncoder));
}

void DriveSystem::DriveDistance(float feet, float inches)
{
	double position = FeetToTicks(feet) + InchesToTicks(inches);
	double setRightPosition = position + RightEncoderValue();
	double setLeftPosition = position + LeftEncoderValue();

	frontLeftMotor->Set(ControlMode::Follower, 1);
	rearLeftMotor->Set(ControlMode::Position, setLeftPosition);
	frontRightMotor->Set(ControlMode::Follower, 3);
	rearRightMotor->Set(ControlMode::Position, setRightPosition);
	frc::SmartDashboard::PutNumber("closed loop error auton", rearLeftMotor->GetClosedLoopError(0));
	frc::SmartDashboard::PutNumber("left encoder value", LeftEncoderValue());
	frc::SmartDashboard::PutNumber("right encoder value", RightEncoderValue());
	frc::SmartDashboard::PutBoolean("acceptable error", DistanceError());
}

void DriveSystem::DriveVelDistance(float feet, float inches, double maxVel, double timeOfAcceleration)
{
	double position = FeetToTicks(feet) + InchesToTicks(inches);
	double velocityFactor;
	double nativeTime = timeOfAcceleration*10;
	double t2 = ((position-(maxVel * nativeTime))/maxVel)/10 + timeOfAcceleration;
	if(timer->Get() < t2)
	{
		velocityFactor = timer->Get()/timeOfAcceleration;
	}
	else if(!setTime && timer->Get() > t2)
	{
		decelerate = timer->Get();
		setTime = true;
	}
	else
	{
		velocityFactor = (timeOfAcceleration - (timer->Get()-decelerate))/timeOfAcceleration;
	}
	if(velocityFactor > 1){velocityFactor = 1;}
	if(velocityFactor < 0){velocityFactor = 0; isFinished = true;}
	frontLeftMotor->Set(ControlMode::Follower, 1);
	rearLeftMotor->Set(ControlMode::Velocity, maxVel*velocityFactor);
	frontRightMotor->Set(ControlMode::Follower, 3);
	rearRightMotor->Set(ControlMode::Velocity, maxVel*velocityFactor);

	frc::SmartDashboard::PutNumber("velocity factor", velocityFactor);
	frc::SmartDashboard::PutNumber("Rear Left Velocity", rearLeftMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("Rear Right Velocity", rearRightMotor->GetSelectedSensorVelocity(0));
	frc::SmartDashboard::PutNumber("time", timer->Get());
	frc::SmartDashboard::PutNumber("t2", t2);
	frc::SmartDashboard::PutBoolean("Decelerate Time Set", decelerate);
	frc::SmartDashboard::PutBoolean("Finished", isFinished);
	frc::SmartDashboard::PutNumber("Distance", position);
	frc::SmartDashboard::PutNumber("left encoder value", LeftEncoderValue());
	frc::SmartDashboard::PutNumber("right encoder value", RightEncoderValue());
}

double DriveSystem::FeetToTicks(float feet)
{
	return feet*7650/1.66158333;
}

double DriveSystem::InchesToTicks(float inches)
{
	return inches*7650/19.939;
}

double DriveSystem::LeftEncoderValue()
{
	return rearLeftMotor->GetSelectedSensorPosition(0);
}

double DriveSystem::RightEncoderValue()
{
	return rearRightMotor->GetSelectedSensorPosition(0);
}

bool DriveSystem::DistanceError()
{
	double position = FeetToTicks(6) + InchesToTicks(0);
	if(position - rearLeftMotor->GetSelectedSensorPosition(0) < abs(distanceError) && position - rearRightMotor->GetSelectedSensorPosition(0) < abs(distanceError))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GyroTurn(double angle)
{
	double currentHeading;
	double target = angle;

}
