/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutonomousCommand.h"
#include "DriverStation.h"

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
//	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
//	gameData[0] = 'R';
//
//	if(gameData.length() > 0)
//	{
//		if(position == 1)
//		{
//			if(gameData[0] == 'L')
//			{
//				printf("game data received");
//				AddSequential(new WristSetPosition(32.5));
//				AddSequential(new DriveDistance(0, 152, 1500, .5));
//				AddSequential(new DriveGyroTurn(-90));
//				AddSequential(new LiftPositionControl(7500));
//				AddSequential(new IntakeOutput(1));
//				AddParallel(new LiftPositionControl(0));
//				AddSequential(new WristSetPosition(65));
//			}
//			else
//			{
//				AddSequential(new DriveDistance(0, 152, 1500, .5));
//			}
//		}
//		if(position == 2)
//		{
//			if(gameData[0] == 'L')
//			{
//				AddSequential(new DriveDistance(0, 152, 1500, .5));
//			}
//			else
//			{
//				AddSequential(new DriveDistance(0, 152, 1500, .5));
//			}
//		}
//		if(position == 3)
//		{
//			if(gameData[0] == 'R')
//			{
//				AddSequential(new WristSetPosition(32.5));
//				AddSequential(new DriveDistance(0, 152, 1500, .5));
//				AddSequential(new DriveGyroTurn(90));
//				AddSequential(new LiftPositionControl(7500));
//				AddSequential(new IntakeOutput(1));
//				AddParallel(new LiftPositionControl(0));
//				AddSequential(new WristSetPosition(65));
//			}
//			else
//			{
//				AddSequential(new DriveDistance(0, 152, 1500, .5));
//			}
//		}
//	}
	if(position == 3)
	{
//		AddSequential(new WristSetPosition(32.5));
		AddSequential(new DriveDistance(20, 0, 1500, 0.5));
//		AddSequential(new DriveGyroTurn(90));
//		AddSequential(new LiftPositionControl(28000));
//		AddSequential(new IntakeOutput(1));
//		AddSequential(new IntakeTimed(-.2, 0.1));
//		AddSequential(new LiftPositionControl(0));
//		AddSequential(new WristSetPosition(65));
	}
	if(position == 1)
	{
		AddSequential(new WristSetPosition(32.5));
		AddSequential(new DriveDistance(0, 152, 1500, .5));
		AddSequential(new DriveGyroTurn(-90));
		AddSequential(new LiftPositionControl(7500));
		AddSequential(new IntakeOutput(1));
		AddParallel(new LiftPositionControl(0));
		AddSequential(new WristSetPosition(65));
	}
}
