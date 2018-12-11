/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeSystem.h"
#include <CTRE/Phoenix.h>
#include <WPILib.h>
#include "../RobotMap.h"
#include <Commands/IntakeSlow.h>

IntakeSystem::IntakeSystem() : Subsystem("IntakeSystem") {
    leftIntakeMotor = new TalonSRX(5);
    rightIntakeMotor = new TalonSRX(8);
}

void IntakeSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new IntakeSlow());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void IntakeSystem::IntakeRoll(float speed)
{
	leftIntakeMotor->Set(ControlMode::PercentOutput, -speed);
	rightIntakeMotor->Set(ControlMode::PercentOutput, speed);
}
