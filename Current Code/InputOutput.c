void getInput() {
	// Gyroscope related stuffs
	//iState.gyroS = SensorValue(gyroscope)/* + 1800 */;
//	if (iState.lastGyro > 2700 && iState.gyroS < 900) {
//		iState.gyroS += 3600;
//	} else if (iState.lastGyro < 900 && iState.gyroS > 2700) {
//		iState.gyroS -= 3600;
//	}
	iState.lastGyro = iState.gyroS;
	//iState.lastGyro2 = iState.gyro2;
	//turning = abs(iState.ljoysticky - iState.rjoysticky) > 25;

	// Claw
	SensorValue(clawR) = iState.clawState;
	SensorValue(clawL) = iState.clawState;
	iState.clawOpen = (bool) vexRT [Btn5U];
	iState.clawClose = (bool) vexRT [Btn5D];
	iState.clawOpenS = (bool) vexRT [Btn5UXmtr2];
	iState.clawCloseS = (bool) vexRT [Btn5DXmtr2];

	// Line sensors
	//iState.lineLSensor = SensorValue(lineL);
	//iState.lineRSensor = SensorValue(lineR);

	// Ultra sonic sensors, there isn't one on the back currently
	//iState.rUltraS = SensorValue(rightUS);
	//iState.lUltraS = SensorValue(leftUS);
	//iState.fUltraS = SensorValue(frontUS);
	//iState.bUltraS = SensorValue(rearUS);

	// Lift potentiometer
	//iState.liftInte = iState.liftPot;

	// Lift encoder
	//iState.liftEncoderS = SensorValue(liftEncoder);

	// Drivetrain encoders
	iState.rightE = SensorValue(rightDE);
	iState.leftE = SensorValue(leftDE);
	iState.driveEncoders = ((iState.rightE + iState.leftE) / 2);

	// Potentiometer on the lift
	iState.liftPot = SensorValue(liftPotent);
	//iState.liftPot = (int)(filterOutL + alpha * (float)(liftPotRaw - filterOutL));
	//filterOutL = iState.liftPot;

	SensorValue(subRoutLED) = subRLED;

	SensorValue(bungieRelease) = iState.bRelease;

	// Autonomous selection potentiometer
	autoSelection = iState.autonPot;
	iState.autonPot = SensorValue(autonSelector) / (4095 / AUTONUMBER);

	// Figuring the current robot mode
	lastMode = currMode;
	if (bIfiRobotDisabled) currMode = DISABLED;
	else if (bIfiAutonomousMode) currMode = AUTONOMOUS;
	else currMode = DRIVER;
	modeChanged = (lastMode != currMode);
	if (currMode == DISABLED) wasDisabled = true;

	// If it isn't autonomous mode, it resets the autonomous steps so it starts over every time
	if (!bIfiAutonomousMode) {
		autoCount = 0;
		autoIsDone = false;
	}

	if (subDone) {
		subCount = 0;
		subLast = false;
		subRLED = true;
	} else {
		subRLED = false;
	}

	if (LCDMid) {
		delaySet = true;
	} else {
		delaySet = false;
	}

	// Wheelie Bar
	SensorValue(wheelie) = iState.wheelieBar;
	iState.wheelieOpen = (bool) vexRT [Btn7R] || (bool) vexRT [Btn7RXmtr2];
	iState.wheelieClose = (bool) vexRT [Btn7L] || (bool) vexRT [Btn7LXmtr2];

	// Launcher
	SensorValue(launcher) = iState.liftLauncher;
	iState.launcherTrue = (bool) vexRT [Btn7D] || (bool) vexRT [Btn7DXmtr2];
	iState.launcherIn = (bool) vexRT [Btn6UXmtr2];
	iState.launcherOut = (bool) vexRT [Btn6DXmtr2];

	// Primary joysticks
	iState.ljoystickx = vexRT [Ch4];
	iState.ljoysticky = vexRT [Ch3];
	iState.rjoysticky = vexRT [Ch2];
	iState.rjoystickx = vexRT [Ch1];
	// Secondary joysticks
	iState.sLjoystickx = vexRT [Ch4Xmtr2];
	iState.sLjoysticky = vexRT [Ch3Xmtr2];
	iState.sRjoysticky = vexRT [Ch2Xmtr2];
	iState.sRjoystickx = vexRT [Ch1Xmtr2];

	iState.shiftButton = (bool) vexRT [Btn7U] || (bool)vexRT [Btn7UXmtr2]; // Shift button

	if (!iState.shiftButton && oLevel && !oManual) { // Regular controls
		iState.launchButton = (bool) vexRT [Btn6U];
		iState.grndButton = (bool) vexRT [Btn6D];
		iState.blockButton = (bool) vexRT [Btn8U];
		iState.dholdButton = (bool) vexRT [Btn8R];
		iState.holdButton = (bool) vexRT [Btn8L];
		iState.stopButton = (bool) vexRT [Btn8R];
		iState.launchOut = (bool) vexRT [Btn6UXmtr2];
		iState.launchIn = (bool) vexRT [Btn6DXmtr2];
		iState.launchOnlyButton = (bool) vexRT [Btn8D];
	} else if (!iState.shiftButton && oManual && !oLevel) {
		iState.liftUpButton = (bool) vexRT [Btn6U];
		iState.liftDownButton = (bool) vexRT [Btn6D];
		iState.clawOpen = (bool) vexRT [Btn5U];
		iState.clawClose = (bool) vexRT [Btn5D];
	} else { // Shift controls
		iState.clawOpen = (bool) vexRT [Btn5U];
		iState.clawClose = (bool) vexRT [Btn5D];
		iState.NateBut = (bool) vexRT [Btn8D];
		iState.CalebBut = (bool) vexRT [Btn8U];
		iState.manualButton = (bool) vexRT [Btn8R] || (bool) vexRT [Btn8RXmtr2];
		iState.killSwitch = (bool) vexRT [Btn7L] || (bool) vexRT [Btn7LXmtr2];
		iState.levelButton = (bool) vexRT [Btn8L] || (bool) vexRT [Btn8LXmtr2];
		iState.releaseButton = (bool) vexRT [Btn5DXmtr2];

		iState.subRout1But = (bool) vexRT [Btn7R];
		iState.subRout2But = (bool) vexRT [Btn7D];

	//	iState.disperseBarButton = (bool) vexRT [Btn6D];
	}

	LCDLeftLast = LCDLeft;
	LCDMidLast = LCDMid;
	LCDRightLast = LCDRight;

	// LCD buttons
	LCDLeft = (bool)(nLCDButtons & 1);
	LCDMid = (bool)(nLCDButtons & 2);
	LCDRight = (bool)(nLCDButtons & 4);
}

void doOutput() {
	//Filter low values
	if((abs(iState.ljoystickx) < 20 && abs(iState.ljoysticky) < 20 && abs(iState.rjoystickx) < 20 && abs(iState.rjoysticky) < 20) && autoIsDone) {
		motor [driveFL] = 0;
		motor [driveFR] = 0;
		motor [driveBL] = 0;
		motor [driveBR] = 0;
	} else {
	#ifdef MOTORRAMPSETTING	// This gradually increases the motor power so it doesn't burn the motors out.
		if (motor [driveFL] < mState.driveFLVal)
			motor [driveFL] += MOTORRAMPVALUE;
		else if (motor [driveFL] > mState.driveFLVal)
			motor [driveFL] -= MOTORRAMPVALUE;

		if (motor [driveFR] < mState.driveFRVal)
			motor [driveFR] += MOTORRAMPVALUE;
		else if (motor [driveFR] > mState.driveFRVal)
			motor [driveFR] -= MOTORRAMPVALUE;

		if (motor [driveBL] < mState.driveBLVal)
			motor [driveBL] += MOTORRAMPVALUE;
		else if (motor [driveBL] > mState.driveBLVal)
			motor [driveBL] -= MOTORRAMPVALUE;

		if (motor [driveBR] < mState.driveBRVal)
			motor [driveBR] += MOTORRAMPVALUE;
		else if (motor [driveBR] > mState.driveBRVal)
			motor [driveBR] -= MOTORRAMPVALUE;

		if (motor [liftBR] < mState.liftR)
			motor [liftBR] += MOTORLIFTVALUE;
		else if (motor [liftBR] > mState.liftR)
			motor [liftBR] -= MOTORLIFTVALUE;

		if (motor [liftFR] < mState.liftR)
			motor [liftFR] += MOTORLIFTVALUE;
		else if (motor [liftFR] > mState.liftR)
			motor [liftFR] -= MOTORLIFTVALUE;

		if (motor [liftMR] < mState.liftR)
			motor [liftMR] += MOTORLIFTVALUE;
		else if (motor [liftMR] > mState.liftR)
			motor [liftMR] -= MOTORLIFTVALUE;

		if (motor [liftBL] < mState.liftL)
			motor [liftBL] += MOTORLIFTVALUE;
		else if (motor [liftBL] > mState.liftL)
			motor [liftBL] -= MOTORLIFTVALUE;

		if (motor [liftFL] < mState.liftL)
			motor [liftFL] += MOTORLIFTVALUE;
		else if (motor [liftFL] > mState.liftL)
			motor [liftFL] -= MOTORLIFTVALUE;

		if (motor [liftML] < mState.liftL)
			motor [liftML] += MOTORLIFTVALUE;
		else if (motor [liftML] > mState.liftL)
			motor [liftML] -= MOTORLIFTVALUE;
	#else
		// Drive, without strafe
		motor [driveFL] = mState.driveFLVal;
		motor [driveFR] = mState.driveFRVal;
		motor [driveBL] = mState.driveBLVal;
		motor [driveBR] = mState.driveBRVal;
	#endif

		// Right side lift
		motor [liftFR] = mState.liftR;
		motor [liftMR] = mState.liftR;
		motor [liftBR] = mState.liftR;

		//// Left side lift
		motor [liftFL] = mState.liftL;
		motor [liftML] = mState.liftL;
		motor [liftBL] = mState.liftL;
	}
}
