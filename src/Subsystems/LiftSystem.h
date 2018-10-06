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
#include "../RobotMap.h"

class LiftSystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	TalonSRX *frontRightLift;
	TalonSRX *frontLeftLift;
	TalonSRX *backRightLift;
	TalonSRX *backLeftLift;
	DigitalInput *upperLimit;
	DigitalInput *lowerLimit;
	PIDVar lift;
	double targetValue;
	bool liftSet;
public:
	LiftSystem();
	void InitDefaultCommand() override;
	bool GetUpperLimitSwitch();
	bool GetLowerLimitSwitch();
	void JoystickLift(double y);
	void LiftTalonPositionPID(double target);
	void ResetEncoder();
	double GetEncoder();
	void SetLiftMotors(double power);
	void LiftJoystickPID(double target);
	void LiftPositionPID(double target);
	bool GetLiftFlag();
	void ResetLiftFlag();
	double GetTargetValue();


	double maxEncVal;
};

