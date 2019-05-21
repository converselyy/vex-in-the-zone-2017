void lcd() { // Overall LCD code
	if (LCDMid) {
		// This lets us set the delay before each autonomous from the LCD
		clearLCD(true, true, true);
		displayLCDString(1,0,"Delay: ");
		displayLCDString(1,8,"        ");
		displayLCDNumber(1,7,dly);
		if (!LCDRightLast && LCDRight) {
			dly += 100;
			LCDRightLast = true;
		} else if (!LCDLeftLast && LCDLeft) {
			dly -= 100;
			LCDLeftLast = true;
		} else {
			LCDLeftLast = false;
			LCDRightLast = false;
		}
	} else {
		// LCD button selection
		if (!LCDLeftLast && LCDLeft) {
			autoSelection--;
			clearLCD(false, true, true);
			bLCDBacklight = true;
			LCDLeftLast = true;
		} else if (!LCDRightLast && LCDRight) {
			autoSelection++;
			clearLCD(false, true, true);
			bLCDBacklight = true;
			LCDRightLast = true;
		} else {
			bLCDBacklight = false;
		}

		// Autonomous selection
		if (autoSelection == 0) {
			clearLCD(true, true, true);
			displayLCDCenteredString(1,"R5Stars");
			bLCDBacklight = true;
		}
	}

	// This makes the autonomous routine labels on LCD go in a loop
	if (autoSelection < 0) { autoSelection = AUTONUMBER; }
	if (autoSelection > AUTONUMBER) { autoSelection = 0; }
}

void lcdDisabled() { // LCD display while robot is disabled
	bLCDBacklight = true;
	string mainBattery;

	displayLCDString(0, 0, "Disabled ");
	sprintf(mainBattery,"%1.2f%c",nImmediateBatteryLevel/1000.0,'V'); // This builds the cortex battery value
	displayNextLCDString(mainBattery); // This displays the cortex battery level
}

void lcdAutonomous() { // LCD display for autonomous mode
	string mainBattery;

	displayLCDString(0,0,"Autonomous ");
	sprintf(mainBattery,"%1.2f%c",nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	// This displays what autonomous step the robot is in while running a routine
	displayLCDNumber(1,14,autoCount);
}

void lcdDriver() { // LCD display for driver control
	bLCDBacklight = true;
	string mainBattery;

	displayLCDString(0,0,"Driver ");
	sprintf(mainBattery,"%1.2f%c",nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);
}
