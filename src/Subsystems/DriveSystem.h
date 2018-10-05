/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <CTRE/Phoenix.h>
#include <WPILib.h>
#include "Timer.h"
#include "../RobotMap.h"

class DriveSystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	TalonSRX* frontLeftMotor;
	TalonSRX* rearLeftMotor;
	TalonSRX* frontRightMotor;
	TalonSRX* rearRightMotor;

	PigeonIMU * pGyon;
	double ypr[3];
	PIDVar gyro;

	DoubleSolenoid* shifter;
	bool shift;
public:
	DriveSystem();
	void InitDefaultCommand() override;
	void JoystickDrive(double x, double y);
	void ShiftUp();
	void ShiftDown();
	void JoystickVelocityDrive(double x, double y);
	void DriveDistance(float feet, float inches);
	void DriveVelDistance(float feet, float inches, double maxVel, double time);
	double FeetToTicks(float feet);
	double InchesToTicks(float inches);
	double LeftEncoderValue();
	double RightEncoderValue();
	bool DistanceError();
	bool GetShift();
	void GyroTurn(double angle);

	float distanceError;
	bool setTime;
	double decelerate;
	Timer* timer;
	bool isFinished;
};

