/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <Commands/IntakeTeleop.h>
#include <Commands/ClimbLock.h>
#include <Commands/RungDeploy.h>
#include <Commands/RungReset.h>
#include <Commands/ClimbUnlock.h>
#include <Commands/DriveShift.h>
#include <Commands/RopeRelease.h>
#include <Commands/RopeReset.h>
#include <Commands/WristSetPosition.h>
#include <Commands/IntakeJoystick.h>
#include <WPILib.h>

OI::OI() {
	// Process operator interface input here.
	xbox = new Joystick(0);
	JoystickButton* Buttonx1 = new JoystickButton(xbox, 1);
	JoystickButton* Buttonx2 = new JoystickButton(xbox, 2);
	JoystickButton* Buttonx3 = new JoystickButton(xbox, 3);
	JoystickButton* Buttonx4 = new JoystickButton(xbox, 4);
	JoystickButton* Buttonx6 = new JoystickButton(xbox, 6);
	JoystickButton* Buttonx7 = new JoystickButton(xbox, 7);

	atk3 = new Joystick(1);
	JoystickButton* Button1 = new JoystickButton(atk3, 1);
	JoystickButton* Button2 = new JoystickButton(atk3, 2);
	JoystickButton* Button3 = new JoystickButton(atk3, 3);
	JoystickButton* Button4 = new JoystickButton(atk3, 4);
	JoystickButton* Button5 = new JoystickButton(atk3, 5);
	JoystickButton* Button6 = new JoystickButton(atk3, 6);
	JoystickButton* Button7 = new JoystickButton(atk3, 7);
	JoystickButton* Button8 = new JoystickButton(atk3, 8);
	JoystickButton* Button9 = new JoystickButton(atk3, 9);
	JoystickButton* Button10 = new JoystickButton(atk3, 10);
	JoystickButton* Button11 = new JoystickButton(atk3, 11);

	Buttonx1->WhenPressed(new ClimbLock());
	Buttonx3->WhenPressed(new ClimbUnlock());

	Buttonx2->WhenPressed(new DriveShift());

	Button1->WhileHeld(new IntakeJoystick());
	Button4->WhileHeld(new IntakeTeleop(1));

	Button7->WhenPressed(new RungDeploy());
	Button6->WhenPressed(new RungReset());
	Button9->WhenPressed(new RopeRelease());
	Button8->WhenPressed(new RopeReset());

	Button3->WhenPressed(new WristSetPosition(65));
	Button5->WhenPressed(new WristSetPosition(32.5));
	Button2->WhenPressed(new WristSetPosition(-15));
}
