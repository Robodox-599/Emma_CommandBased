/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>
#include <Commands/CommandGroup.h>
#include <Commands/WristSetPosition.h>
#include <Commands/DriveGyroTurn.h>
#include <Commands/DriveDistance.h>
#include <Commands/LiftPositionControl.h>
#include <Commands/IntakeOutput.h>
#include <Commands/IntakeTimed.h>
#include <Commands/DriveAccDistance.h>

class AutonomousCommand : public frc::CommandGroup {
public:
	AutonomousCommand(int position);
private:
	std::string gameData;
};

