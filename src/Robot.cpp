/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>

#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

DriveSystem* Robot::driveSystem = new DriveSystem();
ClimbSystem* Robot::climbSystem = new ClimbSystem();
IntakeSystem* Robot::intakeSystem = new IntakeSystem();
LiftSystem* Robot::liftSystem = new LiftSystem();
RungSystem* Robot::rungSystem = new RungSystem();
WristSystem* Robot::wristSystem = new WristSystem();
OI* Robot::oi = new OI();
Compressor *comp599 = new Compressor();


void Robot::RobotInit() {
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
//	m_chooser.AddDefault("Nothing", nullptr);
	//m_chooser.AddDefault("Drive Distance", new DriveDistance(10, 0, 2250, 0.5));
	m_chooser.AddDefault("Gyro Turn", new DriveGyroTurn(90));
	m_chooser.AddObject("Test Auto", new TestAuto1());
	comp599->SetClosedLoopControl(true);

}

/**
 * This function is called once each time the robot enters Disabled
 * mode.
 * You can use it to reset any subsystem information you want to clear
 * when
 * the robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to
 * select
 * between different autonomous modes using the dashboard. The sendable
 * chooser code works with the Java SmartDashboard. If you prefer the
 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
 * GetString code to get the auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to
 * the
 * chooser code above (like the commented example) or additional
 * comparisons
 * to the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
	m_autoCommand.reset(m_chooser.GetSelected());
	if (m_autoCommand.get() != nullptr)
	{
			m_autoCommand->Start();
	}
//	autonomousCommand->Start();
	// m_autoSelected = SmartDashboard::GetString(
	// 		"Auto Selector", kAutoNameDefault);
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	m_autoCommand->Cancel();
	Robot::wristSystem->TestWristPID(-15);
//	autonomousCommand->Cancel();
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run();
frc::SmartDashboard::PutNumber("Average Potentiometer Value", Robot::wristSystem->GetPotVal());
frc::SmartDashboard::PutNumber("Z axis Value", Robot::oi->atk3->GetRawAxis(2));}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
