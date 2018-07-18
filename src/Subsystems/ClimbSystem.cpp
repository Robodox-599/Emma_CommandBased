/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimbSystem.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

ClimbSystem::ClimbSystem() : Subsystem("ClimbSystem") {
	climbPiston = new DoubleSolenoid(0, 1);
}

void ClimbSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ClimbSystem::ClimbLock()
{
	climbPiston->Set(DoubleSolenoid::kReverse);
}

void ClimbSystem::ClimbUnlock()
{
	climbPiston->Set(DoubleSolenoid::kForward);
}

void ClimbSystem::ClimbNeutral()
{
	climbPiston->Set(DoubleSolenoid::kOff);
}

int ClimbSystem::ClimbStatus()
{
	return climbPiston->Get();
}
