/*
 * Robot.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Admin
 */
#pragma once

#include <Commands/Command.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>

#include "OI.h"


class Robot : public frc::TimedRobot {
public:
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
