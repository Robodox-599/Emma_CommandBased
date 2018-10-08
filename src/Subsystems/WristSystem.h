/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"
#include "WPILib.h"
#include "../RobotMap.h"

class WristSystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	AnalogPotentiometer* pot;
	TalonSRX* wristMotor;
	double avgPotVal;
	double potVals[10];
	PIDVar wrist;
	bool wristSet;
	double wristTarget;
public:
	WristSystem();
	void InitDefaultCommand() override;
	double GetPotVal();
	void UpdatePotVal();
	void GetAvgPotVal();
	void HoldWristPosition();
	void TestWristPID();
	bool WristFlag();
	void ResetWristFlag();
	void SetWristTarget(double angle);
};

