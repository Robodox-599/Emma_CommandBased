/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <Commands/IntakeIn.h>

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

	Button1->WhileHeld(new IntakeIn(.7));
}
