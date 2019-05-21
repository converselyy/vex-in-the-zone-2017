void autonomousControl() {
	if (modeChanged) { // Reset autonomous
		autoCount = 0;
		autoIsDone = false;
	}

	// Right autonomae are universal between sides, and vice versa (for now, will change when we start lifting)

	if (autoSelection == 0) { // R5Stars
		switch (autoCount) {
			//			   	LeftRight	Strafe	Target	Claw	launcher	PID			Reset 	Duration	Sensor
			case 0: autoState(0,	0,		0,		GRND,	CLOS,	false,		true,		true, 	dly,		TIME ); break; // Break
			default : autoIsDone = true;
		}
	}
}
