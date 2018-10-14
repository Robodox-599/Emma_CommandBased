/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutonomousCommand.h"
#include "DriverStation.h"
#include <SmartDashboard/SmartDashboard.h>

AutonomousCommand::AutonomousCommand(int position) {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	//gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	while(gameData.length() <= 0)
	{
//		printf("Data Not Received");
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		frc::SmartDashboard::PutString("gameData", gameData);
	}

	if(gameData.length() > 0)
	{
		if(position == 1)
		{
			if(gameData[0] == 'L' && gameData[1] != 'L')
			{
				AddSequential(new WristSetPosition(65));
				AddSequential(new DriveDistance(14, -19.5, 3000, 1));
				AddSequential(new DriveGyroTurn(-90));
				AddSequential(new LiftPositionControl(5000));
				AddSequential(new WristSetPosition(32.5));
				AddSequential(new IntakeOutput(1));
				AddSequential(new IntakeTimed(-.2, 0.1));
				AddSequential(new LiftPositionControl(0));
				AddSequential(new WristSetPosition(65));
			}
			else if(gameData[1] == 'L')
			{
				AddSequential(new WristSetPosition(32.5));
				AddSequential(new DriveDistance(22, -9.5, 3000, 1));
				AddSequential(new DriveGyroTurn(-45));
				AddSequential(new LiftPositionControl(28000));
				AddSequential(new IntakeOutput(0.8));
				AddSequential(new IntakeTimed(-.2, 0.1));
				AddSequential(new LiftPositionControl(0));
				AddSequential(new WristSetPosition(65));
			}
			else
			{
				AddSequential(new WristSetPosition(65));
				AddSequential(new DriveDistance(14, -19.5, 3000, 1));
			}
		}
		if(position == 2)
		{
			if(gameData[0] == 'L')
			{
				AddSequential(new WristSetPosition(65));
				AddSequential(new DriveDistance(5, -14.5, 3000, 1));
				AddSequential(new DriveGyroTurn(70));
				AddSequential(new DriveDistance(6, 4.95, 3000, 1));
				AddSequential(new DriveGyroTurn(-110));
				AddSequential(new DriveDistance(4, -19, 3000, 1));
				AddSequential(new LiftPositionControl(5000));
				AddSequential(new WristSetPosition(32.5));
				AddSequential(new IntakeOutput(1));
				AddSequential(new IntakeTimed(-.2, 0.1));
				AddSequential(new LiftPositionControl(0));
				AddSequential(new WristSetPosition(65));
			}
			else
			{
				AddSequential(new WristSetPosition(65));
				AddSequential(new DriveDistance(5, -14.5, 3000, 1));
				AddSequential(new DriveGyroTurn(-45));
				AddSequential(new DriveDistance(4, 3.5, 3000, 1));
				AddSequential(new DriveGyroTurn(135));
				AddSequential(new DriveDistance(3, -17.5, 3000, 1));
				AddSequential(new LiftPositionControl(5000));
				AddSequential(new WristSetPosition(32.5));
				AddSequential(new IntakeOutput(1));
				AddSequential(new IntakeTimed(-.2, 0.1));
				AddSequential(new LiftPositionControl(0));
				AddSequential(new WristSetPosition(65));
			}
		}
		if(position == 3)
		{
			if(gameData[0] == 'R' && gameData[1] != 'R')
			{
				AddSequential(new WristSetPosition(65));
				AddSequential(new DriveDistance(14, -19.5, 3000, 1));
				AddSequential(new DriveGyroTurn(90));
				AddSequential(new LiftPositionControl(5000));
				AddSequential(new WristSetPosition(32.5));
				AddSequential(new IntakeOutput(1));
				AddSequential(new IntakeTimed(-.2, 0.1));
				AddSequential(new LiftPositionControl(0));
				AddSequential(new WristSetPosition(65));
			}
			else if(gameData[1] == 'R')
			{
				AddSequential(new WristSetPosition(32.5));
				AddSequential(new DriveDistance(22, -9.5, 3000, 1));
				AddSequential(new DriveGyroTurn(45));
				AddSequential(new LiftPositionControl(28000));
				AddSequential(new IntakeOutput(0.8));
				AddSequential(new IntakeTimed(-.2, 0.1));
				AddSequential(new LiftPositionControl(0));
				AddSequential(new WristSetPosition(65));
			}
			else
			{
				AddSequential(new WristSetPosition(65));
				AddSequential(new DriveDistance(14, -19.5, 3000, 1));
			}
		}
	}
}
