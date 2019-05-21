void constrain(int constrainedVar, int minVal, int maxVal) { // Constrain function
	if (constrainedVar < minVal){
		constrainedVar = minVal;
	}

	if (constrainedVar > maxVal){
		constrainedVar = maxVal;
	}
}

void executePID(PID *pid, int currentValue) { // PID function
	pid->error = pid->target - currentValue;
	//pid->integral *= 9;
	//pid->integral += pid->error;
	//pid->integral /= 10;
	pid->integral = pid->integral + pid->error;
	constrain(pid->integral, -1000, 1000);
	pid->derivative = pid->error - pid->lastError;
	pid->lastError = pid->error;

	pid->result = (int)(((float)pid->error * pid->kp + (float)pid->derivative * pid->kd))/* * liftPID.gain*/;

	pid->stable = (abs(pid->error) + abs(pid->derivative)) < pid->range;
}

void clearLCD(bool top, bool bottom, bool once) { // Function to clear LCD
	if (top && bottom && !cleared) {
		clearLCDLine(0);
		clearLCDLine(1);
	} else if (top && !cleared) { // True = top line
		clearLCDLine(0);
	} else if (bottom && !cleared) {
		clearLCDLine(1);
	}

	if (once) { // If LCD only needs cleared once, input true
		cleared = true;
	} else if (!once) {
		cleared = false;
	}
}
