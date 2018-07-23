/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "WristSystem.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "Commands/PotentiometerValue.h"

WristSystem::WristSystem() : Subsystem("WristSystem") {
	wristMotor = new TalonSRX(11);
	pot = new AnalogPotentiometer(3, 200, -38);
}

void WristSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new PotentiometerValue());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
double WristSystem::GetPotVal()
{
	return pot->Get();
}
