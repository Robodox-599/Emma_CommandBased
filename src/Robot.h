/*
 * Robot.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Admin
 */
#pragma once

#include <Commands/Command.h>
#include <Commands/DriveDistance.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>

#include "OI.h"
#include "Subsystems/DriveSystem.h"
#include "Subsystems/ClimbSystem.h"
#include "Subsystems/IntakeSystem.h"
#include "Subsystems/LiftSystem.h"
#include "Subsystems/RungSystem.h"
#include "Subsystems/WristSystem.h"


class Robot : public frc::TimedRobot {
public:
	static DriveSystem* driveSystem;
	static ClimbSystem* climbSystem;
	static IntakeSystem* intakeSystem;
	static LiftSystem* liftSystem;
	static RungSystem* rungSystem;
	static WristSystem* wristSystem;
	static OI* oi;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	std::unique_ptr<frc::Command> m_autoCommand;
	frc::SendableChooser<frc::Command*> m_chooser;
};
