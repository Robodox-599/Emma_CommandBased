/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RungSystem.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

RungSystem::RungSystem() : Subsystem("RungSystem") {
	rungPiston = new DoubleSolenoid(6, 7);
	rungPiston->Set(DoubleSolenoid::kReverse);
}

void RungSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void RungSystem::RungDeploy()
{
	rungPiston->Set(DoubleSolenoid::kForward);
}

void RungSystem::RungReset()
{
	rungPiston->Set(DoubleSolenoid::kReverse);
}

void RungSystem::RungNeutral()
{
	rungPiston->Set(DoubleSolenoid::kOff);
}
