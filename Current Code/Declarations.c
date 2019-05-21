#define FWD 127
#define BWD -127
#define FSL	70
#define BSL	-70
#define LFT -127
#define RGT 127
#define IN 127
#define OUT -127
#define UP 127
#define DOWN 127
#define STOP 0
#define SLOW_MO_DRIVE 2.5
#define GFLIP -1800

#define AUTONUMBERLIFTWORK 2
#define AUTONUMBERLIFTNO 3
#define AUTONUMBER 1

// States of robot / control
#define DISABLED 0
#define DRIVER 1
#define AUTONOMOUS 2

// Slew controller definitions
#define MOTORRAMPSETTING
#define MOTORRAMPVALUE 8	// Drive ramp value
#define MOTORLIFTVALUE 1	// Lift ramp value

#define MANUALLIFT

// Defined lift levels - potentiometer
#define PGRND 3850
#define PHOLD 2700
#define PDHLD 3300
#define PBLOC 1980
#define PLNCH 1060
#define PRELE 1900
#define PBBLC 900

// Define claw state
#define OPEN false
#define CLOS true

//bool turning = true;	// If turning

bool oManual;			// If the lift operation is manual
bool oLevel = true;		// Or PID operated

// LCD button variables
bool LCDLeftLast;
bool LCDMidLast;
bool LCDRightLast;
bool LCDLeft = false;
bool LCDMid = false;
bool LCDRight = false;
bool cleared = false;

bool autoIsDone = false;	// If the autonomous is done

bool wasDisabled;			// Was the robot disabled?

bool exePID;				// Execute PID

typedef enum TERMINATION {
	TIME,	// Time
	RUSS,	// Right ultrasonic
	LUSS,	// Left ultrasonic
	FUSS,	// Front ultrasonic
	BUSS,	// Back ultra sonic - not used
	GYRO,	// Gyroscope
	ENCO,	// Encoders
	LHIG,	// Lift pot
	LINE,	// Line follower
	WUSS	// Wall ultrasonic
};

typedef struct { // iState
	// Joystick
	int ljoysticky;
	int ljoystickx;
	int rjoysticky;
	int rjoystickx;

	// Secondary joystick
	int sRjoystickx;
	int sRjoysticky;
	int sLjoystickx;
	int sLjoysticky;

	int rightE;	// Right encoder
	int leftE;	// Left encoder
	int driveEncoders;

	int liftEncoderS;		// Name impies itself, will eventually be used for autonomous, probably driver control

	int autonPot;			// Autonomous selector potentiometer

	int gyroS;				// Gyroscope reading
	int lastGyro;			// Last gyro reading

	//int gyro2;
	//int lastGyro2;

	bool clawState;

	bool shiftButton;		// Shift button 					7U
	bool stopButton;		// Stop the lift button
	bool liftUpButton;		// Lifting up button
	bool liftDownButton;	// Lift down button
	bool killSwitch;		// Kill swtich
	bool manualButton;		// Button to switch to manual lift
	bool levelButton;		// BUtton to switch to PID lift
	bool blockButton;		// Keeps the lift at a certain level to block
	bool grndButton;		// Ground button
	bool holdButton;		// Hold claw above fence
	bool dholdButton;		// Hold claw off the ground
	bool releaseButton;		// Bungie release button for secondary controller
	bool autoAlignButton;
	bool launchOnlyButton;

	// Subroutine buttons
	bool subRout1But;
	bool subRout2But;

	// Wheelie Bar
	bool wheelieBar;
	bool wheelieOpen;
	bool wheelieClose;

	//Claw
	bool clawOpen;			// Claw open button
	bool clawClose;			// Claw close button
	bool clawOpenS;
	bool clawCloseS;

	bool bRelease;

	bool toggleLast;

	int lineLSensor;		// Line sensor
	int lineRSensor;
	int liftPot;			// Lift potentiometer

	int rUltraS;			// Right ultrasonic sensor
	int lUltraS;			// Left ultrasonic sensor
	int fUltraS;
	int bUltraS;

	int liftTarget;			// Lift target
	int liftInte;			// Actual lift height
	int liftState;
	int liftPotTest;
} InputState;
InputState iState;

typedef struct MotorState { // mState
	// Drive train values with strafe
	int driveBRVal;
	int driveBLVal;
	int driveFRVal;
	int driveFLVal;

	// Drive train values without strafe
	int driveLVal;
	int driveRVal;

	// Lift values
	int liftL;
	int liftR;

	int liftPower;
} MotorState;
MotorState mState;

typedef struct PID {
	int target;				// The target speed from the encoders
	float error;			// The difference between the target and the current speed
	float integral;
	float derivative;
	float lastError;		// The last error input
	int result;				// Output

	int power;				// The current power of the launcher motors

	bool stable;
	float range;

	float kp;				// Proportional constant
	float ki;				// Integral constant
	float kd;				// Derivative constant
	float gain;
} PID;

bool modeChanged = false;
int lastMode = -1;	// Purposefully invalid
int currMode = DISABLED;

int autoCount = 0;
int autoSelection = 0;	// Autonomous selection number

int subCount = 0;
bool subDone = false;
bool subLast;

bool launchLast;

bool subRLED = false;

int dly; // Autonomous starting time
bool delaySet;
