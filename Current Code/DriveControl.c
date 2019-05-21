void driverControl() {
	if (iState.killSwitch) { // Shift then 7D, kills all motors
		mState.driveFLVal = 0;
		mState.driveFRVal = 0;
		mState.driveBLVal = 0;
		mState.driveBRVal = 0;
		mState.liftR = 0;
		mState.liftL = 0;
	} else {
		// Arcade drive, with strafe
		//					FWD/BWD				Turn Left/Right		Strafe Left/Right
		mState.driveFLVal = iState.rjoysticky + iState.rjoystickx + iState.ljoystickx;
		mState.driveFRVal = iState.rjoysticky - iState.rjoystickx - iState.ljoystickx;
		mState.driveBLVal = iState.rjoysticky + iState.rjoystickx - iState.ljoystickx;
		mState.driveBRVal = iState.rjoysticky - iState.rjoystickx + iState.ljoystickx;

		// Tank drive, no strafe
		//mState.driveLVal = iState.ljoysticky;
		//mState.driveRVal = iState.rjoysticky;

		if (iState.manualButton && !oManual) {
			oManual = true;
			oLevel = false;
		} else if (iState.levelButton && !oLevel) {
			oLevel = true;
			oManual = false;
		}

		//liftPID.kp = 0.07
/*		liftPID.ki = 0;
		liftPID.kd = 0;
		liftPID.gain = 0.1;
		if (liftPID.target != 0 && exePID && oLevel) {
			executePID(liftPID, iState.liftPot);
			mState.liftPower = liftPID.result;
			mState.liftPower = (mState.liftPower - (mState.liftPower * 2));
			mState.liftR = mState.liftPower;
			mState.liftL = mState.liftPower;
		} */
	}
}
