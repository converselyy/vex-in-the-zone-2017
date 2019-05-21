void endState() {
	clearTimer(T1);
	autoCount++;
	//rightEncoderLast = iState.rightE;
	//leftEncoderLast = iState.leftE;
	//SensorValue(Gyroscope) = 0;
	SensorValue(rightDE) = 0;
	SensorValue(leftDE) = 0;
	SensorValue(gyroscope) = 0;
}

void autoState(int left, int right, int strafe, int lift, bool claw, bool lLauncher, bool level, bool reset, int duration, TERMINATION sensor) {
	// Drive with strafe
	mState.driveFLVal = left + strafe;
	mState.driveFRVal = right - strafe;
	mState.driveBLVal = left - strafe;
	mState.driveBRVal = right + strafe;

	// True for closed, false for open
	iState.clawState = claw;

	// Drive without strafe
/*	if (left == right) {
		gyroPID.target = 0;
		gyroPID.kp = 0.1;
		gyroPID.ki = 0;
		gyroPID.kd = 0;
		executePID(gyroPID, iState.gyroS);
		mState.driveLVal = (right + left) / 2 - gyroPID.result;
		mState.driveRVal = (right + left) / 2 + gyroPID.result;
	} else {
		mState.driveLVal = left;
		mState.driveRVal = right;
	} */

	iState.wheelieBar = true;

	if (lLauncher) {
		iState.liftLauncher = true;
	} else if (!lLauncher) {
		iState.liftLauncher = false;
	}

	if (reset) {
		if (sensor == TIME) {		 // Time - miliseconds
			if (time1[T1] > duration){
				endState();
			}
		} else if (sensor == ENCO) { // Encoder - ticks
			if (abs(iState.leftE) > duration)/* || abs (iState.leftE) > duration)*/ {
				endState();
			}
		} else if (sensor == GYRO) {
			if (abs(iState.gyroS) > duration) {
				endState();
			}
		} else if (sensor == LHIG) {
			if (abs(iState.liftPot) < duration) {
				endState();
			}
		} else if (sensor == FUSS) { // Front ultrasonic - measure changeable in Sensors Setup
			if (abs(iState.fUltraS) < duration) {
				endState();
			}
		} else if (sensor == LUSS) {
			if (abs(iState.lUltraS) < duration) {
				endState();
			}
		} else if (sensor == RUSS) {
			if (abs(iState.rUltraS) < duration) {
				endState();
			}
		} else if (sensor == LINE) {
			if ((iState.lineLSensor + iState.lineRSensor) / 2 < duration) {
				endState();
			}
		}
	} else if (!reset) {
		if (sensor == TIME) {		 // Time - miliseconds
			if (time1[T1] > duration){
				autoCount++;
			}
		} else if (sensor == ENCO) { // Encoder - ticks
			if (abs(iState.leftE) > duration)/* || abs (iState.leftE) > duration)*/ {
				autoCount++;
			}
		} else if (sensor == GYRO) { // Gyroscope - Tenths of degrees
			if (abs(iState.gyroS) > duration) {
				autoCount++;
			}
		} else if (sensor == FUSS) { // Front ultrasonic - measure changeable in Sensors Setup
			if (abs(iState.rUltraS) < duration) {
				autoCount++;
			}
		} else if (sensor == LUSS) {
			if (abs(iState.lUltraS) < duration) {
				autoCount++;
			}
		} else if (sensor == RUSS) {
			if (abs(iState.fUltraS) < duration) {
				autoCount++;
			}
		} else if (sensor == LINE) {
			if ((iState.lineLSensor + iState.lineRSensor) / 2 < duration) {
				autoCount++;
			}
		}
	}
	return;
}

void autoTurnG (int angle, int lift, bool claw, bool level, int timeOut) {
	gyroPID.target = angle;
	gyroPID.kp = 1.0;
	gyroPID.ki = 0.0009;
	gyroPID.kd = 22.0;
	gyroPID.range = 1.17;
	executePID(gyroPID, iState.gyroS);
	mState.driveFLVal = -gyroPID.result;
	mState.driveBLVal = -gyroPID.result;
	mState.driveFRVal = +gyroPID.result;
	mState.driveBRVal = +gyroPID.result;

	if (gyroPID.stable) {
			endState();
	}
	return;
}

void autoDPID(int left, int right, int strafe, int lift, bool claw, bool lLauncher, bool level, bool reset, int duration, TERMINATION sensor) {
	drivPID.kp = 0.05;
	drivPID.ki = 0;
	drivPID.kd = 0;
	drivPID.target = duration;
	if (sensor == ENCO) { executePID(drivPID, iState.driveEncoders); }
	// Drive with strafe and PID, untested PID
	mState.driveFLVal = (left + strafe) * drivPID.result;
	mState.driveFRVal = (right - strafe) * drivPID.result;
	mState.driveBLVal = (right - strafe) * drivPID.result;
	mState.driveBRVal = (left + strafe) * drivPID.result;

	// True for closed, false for open
	iState.clawState = claw;

	iState.wheelieBar = true;

	if (lLauncher) {
		iState.liftLauncher = true;
	} else if (!lLauncher) {
		iState.liftLauncher = false;
	}

	if (reset) {
		if (sensor == TIME) {		 // Time - miliseconds
			if (time1[T1] > duration){
				endState();
			}
		} else if (sensor == ENCO) { // Encoder - ticks
			if (abs(iState.leftE) > duration)/* || abs (iState.leftE) > duration)*/ {
				endState();
			}
		} else if (sensor == GYRO) {
			if (abs(iState.gyroS) > duration) {
				endState();
			}
		} else if (sensor == LHIG) {
			if (abs(iState.liftPot) < duration) {
				endState();
			}
		} else if (sensor == FUSS) { // Front ultrasonic - measure changeable in Sensors Setup
			if (abs(iState.fUltraS) < duration) {
				endState();
			}
		} else if (sensor == LUSS) {
			if (abs(iState.lUltraS) < duration) {
				endState();
			}
		} else if (sensor == RUSS) {
			if (abs(iState.rUltraS) < duration) {
				endState();
			}
		} else if (sensor == LINE) {
			if ((iState.lineLSensor + iState.lineRSensor) / 2 < duration) {
				endState();
			}
		}
	} else if (!reset) {
		if (sensor == TIME) {		 // Time - miliseconds
			if (time1[T1] > duration){
				autoCount++;
			}
		} else if (sensor == ENCO) { // Encoder - ticks
			if (abs(iState.leftE) > duration)/* || abs (iState.leftE) > duration)*/ {
				autoCount++;
			}
		} else if (sensor == GYRO) { // Gyroscope - Tenths of degrees
			if (abs(iState.gyroS) > duration) {
				autoCount++;
			}
		} else if (sensor == FUSS) { // Front ultrasonic - measure changeable in Sensors Setup
			if (abs(iState.rUltraS) < duration) {
				autoCount++;
			}
		} else if (sensor == LUSS) {
			if (abs(iState.lUltraS) < duration) {
				autoCount++;
			}
		} else if (sensor == RUSS) {
			if (abs(iState.fUltraS) < duration) {
				autoCount++;
			}
		} else if (sensor == LINE) {
			if ((iState.lineLSensor + iState.lineRSensor) / 2 < duration) {
				autoCount++;
			}
		}
	}
	return;
}
