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
	float ki = 0;

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

	isFinished = false;

	pGyon = new PigeonIMU(frontRightMotor);
	pGyon->SetYaw(0, 0);
	currentHeading = 0;
	gyroTarget = 0;
	turn = false;
	teleopFlag = false;
	autoFlag = false;
	targetHeading = 0;

	velocity = 0;
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
	double leftOutput;
	double rightOutput;
	double increment = 600;

	teleopFlag = true;
	autoFlag = false;

	if(y > 0.2)
	{
		y = (y-0.2)*(1/.8)*3000/**max velocity*/;
	}
	else if(y < -0.2)
	{
		y = (y+0.2)*1/.8*3000/**max velocity*/;
	}
	else
	{
		y = 0;
	}

	if(x > 0.2)
	{
		x = (x-0.2)*1/.8*1500/**max velocity/2*/;
	}
	else if(x < -0.2)
	{
		x = (x+0.2)*1/.8*1500/**max velocity/2*/;
	}
	else
	{
		x = 0;
	}

	l = -y+x;
	r = -y-x;

	if(l > rearLeftMotor->GetSelectedSensorVelocity(0) + increment)
	{
		leftOutput = rearLeftMotor->GetSelectedSensorVelocity(0) + increment;
	}
	else if(l < rearLeftMotor->GetSelectedSensorVelocity(0) - increment)
	{
		leftOutput = rearLeftMotor->GetSelectedSensorVelocity(0) - increment;
	}
	else
	{
		leftOutput = l;
	}

	if(r > rearRightMotor->GetSelectedSensorVelocity(0) + increment)
	{
		rightOutput = rearRightMotor->GetSelectedSensorVelocity(0) + increment;
	}
	else if(r < rearRightMotor->GetSelectedSensorVelocity(0) - increment)
	{
		rightOutput = rearRightMotor->GetSelectedSensorVelocity(0) - increment;
	}
	else
	{
		rightOutput = r;
	}

	frontLeftMotor->Set(ControlMode::Follower, 1);
	rearLeftMotor->Set(ControlMode::Velocity, leftOutput);
	frontRightMotor->Set(ControlMode::Follower, 3);
	rearRightMotor->Set(ControlMode::Velocity, rightOutput);

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
}

void DriveSystem::DriveVelDistance(float feet, float inches, double maxVel, double timeOfAcceleration)
{
	double position = FeetToTicks(feet) + InchesToTicks(inches);
	double velocityFactor;
	double nativeTime = timeOfAcceleration*10;
	double t2 = ((position-(maxVel * nativeTime))/maxVel)/10 + timeOfAcceleration;
	autoFlag = true;
	teleopFlag = false;
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

void DriveSystem::DriveAccDistance(float feet, float inches, double acceleration)
{
	double position = FeetToTicks(feet) + InchesToTicks(inches);
	double cruiseTime;
	double accTime;
	double accDistance;
	double cruiseDistance;
	double maxVel = 3000;
	autoFlag = true;
	teleopFlag = false;
	accTime = (maxVel/acceleration);
	accDistance = 0.5*(acceleration)*(accTime)*(accTime);//(at^2)/2... *10 to convert to native units.
	cruiseDistance = position - accDistance*2;
	cruiseTime = (cruiseDistance/maxVel)/10;
	if(timer->Get() < accTime)
	{
		velocity += acceleration/(accTime);
	}
	else if(timer->Get() > accTime && timer->Get() < (cruiseTime + accTime))
	{
		velocity = maxVel;
	}
	else
	{
		velocity -= acceleration/(accTime);
	}
	if(velocity <= 0){isFinished = true;}
	frc::SmartDashboard::PutNumber("velocity", velocity);
	frc::SmartDashboard::PutNumber("time", timer->Get());
	frc::SmartDashboard::PutNumber("cruise distance", position - accDistance*2);
	frc::SmartDashboard::PutNumber("Cruise Time", cruiseTime);
	frc::SmartDashboard::PutNumber("Acceleration Time", accTime);
	frc::SmartDashboard::PutNumber("Acceleration Distance", accDistance);
//	frontLeftMotor->Set(ControlMode::Follower, 1);
//	rearLeftMotor->Set(ControlMode::Velocity, velocity);
//	frontRightMotor->Set(ControlMode::Follower, 3);
//	rearRightMotor->Set(ControlMode::Velocity, velocity);
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

void DriveSystem::GetYaw()
{
	currentHeading = ypr[0];
}

void DriveSystem::SetGyroTarget(double target)
{
	GetYaw();
	targetHeading = target;
	gyroTarget = currentHeading + target;
}

double DriveSystem::ReturnGyroTarget()
{
	return gyroTarget;
}

void DriveSystem::ResetGyroFlag()
{
	turn = false;
}

bool DriveSystem::GetGyroFlag()
{
	return turn;
}

void DriveSystem::GyroTurn(double angle)
{
	double accAngle = 45;
	double velocity = 1000;
	double error;
	double velocityFactor;
	error = angle - currentHeading;
	if(error > targetHeading/2 && angle > 0){velocityFactor = (targetHeading-error+10)/accAngle;}
	else if(error > 0){velocityFactor = (error+3)/accAngle;}
	if(error < targetHeading/2 && angle < 0){velocityFactor = (targetHeading-error-10)/accAngle;}
	else if(error < 0){velocityFactor = (error-3)/accAngle;}

	if(velocityFactor > 1){velocityFactor = 1;}
	if(velocityFactor < -1){velocityFactor = -1;}
//	if(error > -1 && error < 1){velocityFactor = 0; turn = true;}
	if(error == 0){velocityFactor = 0; turn = true;}

	frontLeftMotor->Set(ControlMode::Follower, 1);
	rearLeftMotor->Set(ControlMode::Velocity, -velocity*velocityFactor);
	frontRightMotor->Set(ControlMode::Follower, 3);
	rearRightMotor->Set(ControlMode::Velocity, velocity*velocityFactor);

	frc::SmartDashboard::PutNumber("First Acceleration", targetHeading-error);
	frc::SmartDashboard::PutNumber("error", error);
	frc::SmartDashboard::PutNumber("Current Heading", currentHeading);
	frc::SmartDashboard::PutNumber("Velocity", velocityFactor);
	frc::SmartDashboard::PutNumber("target", angle);
	frc::SmartDashboard::PutBoolean("Gyro Flag", turn);
	frc::SmartDashboard::PutNumber("gyro value", ypr[0]);
}

void DriveSystem::GetGyroValues()
{
	pGyon->GetYawPitchRoll(ypr);
}

void DriveSystem::ResetDriveFlag()
{
	isFinished = false;
}

void DriveSystem::SetAutoFlag()
{
	autoFlag = true;
	teleopFlag = false;
}

void DriveSystem::SetTeleopFlag()
{
	teleopFlag = true;
	autoFlag = false;
}

void DriveSystem::SetPID()
{
	float kp = 0.8;
	float ki;
	if(teleopFlag == true)
	{
		ki = 0;
	}
	if(autoFlag == true)
	{
		ki = 0.004;
	}
	rearLeftMotor->Config_kF(0, 0.45, 0);
	rearLeftMotor->Config_kP(0, kp, 0);
	rearLeftMotor->Config_kI(0, ki, 0);

	rearRightMotor->Config_kF(0, 0.45, 0);
	rearRightMotor->Config_kP(0, kp, 0);
	rearRightMotor->Config_kI(0, ki, 0);

	frontLeftMotor->Config_kF(0, 0.45, 0);
	frontLeftMotor->Config_kP(0, kp, 0);
	frontLeftMotor->Config_kI(0, ki, 0);

	frontRightMotor->Config_kF(0, 0.45, 0);
	frontRightMotor->Config_kP(0, kp, 0);
	frontRightMotor->Config_kI(0, ki, 0);
}

void DriveSystem::ResetGyro()
{
	pGyon->SetYaw(0, 0);
}
