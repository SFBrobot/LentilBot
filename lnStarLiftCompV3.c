#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  frontFlipLeds,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  backFlipLeds,   sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  tankLeds,       sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  lDriveEnc,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rDriveEnc,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  liftEnc,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  clawEnc,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           lClaw,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rDrive,        tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port3,           brLift,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mrLift,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           trLift,        tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port6,           tlLift,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           mlLift,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           blLift,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           lDrive,        tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          rClaw,         tmotorVex393_HBridge, openLoop, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!





//#define DEBUG






#define RX 0
#define RY 1
#define LY 2
#define LX 3

#define LIFT_UP_BTN (vexRT[Btn5U])
#define LIFT_DWN_BTN (vexRT[Btn5D])

#define CLAW_OPEN_BTN (vexRT[Btn6U])
#define CLAW_CLOSE_BTN (vexRT[Btn6D])


#ifdef DEBUG
#define SAVE_LIFT_ENC (vexRT[Btn7U])
#define SAVE_LDRIVE_ENC (vexRT[Btn7L])
#define SAVE_RDRIVE_ENC (vexRT[Btn7R])
#endif

#define setRDrive(pwr) motor[rDrive] = pwr
#define setLDrive(pwr) motor[lDrive] = pwr

#define setClaw(pwr) motor[lClaw] = \
	motor[rClaw] = \
	pwr

#define setLift(pwr) \
	motor[blLift] = \
		motor[mlLift] = \
		motor[tlLift] = \
		motor[trLift] = \
		motor[mrLift] = \
		motor[brLift] = \
		pwr

int* arcade(int* arr, int move, int rot) {
	arr[0] = move + rot;
	arr[1] = move - rot;
	return arr;
}

void setDrive(int* pwrs) {
	setLDrive(pwrs[0]);
	setRDrive(pwrs[1]);

}


typedef struct {
	bool out;
	word valLast;

} Toggle;

bool upToggle(Toggle* toggle, word in) {
	if(in != toggle->valLast)
		toggle->out = true;
	else
		toggle->out = false;
	toggle->valLast = in;
	return toggle->out;
}

bool pressToggle(Toggle* toggle, word in) {
	if(toggle->out && in)
		return true;
	else
		return false;
}

typedef struct {
	int targ,
		val,
		error,
		errLast;
	float prop,
		integ,
		deriv,
		kP,
		kI,
		kD;
	tSensors sensorPort;
	signed char out;
} Pid;

void initPid(Pid* pid, float kP,	float kI, float kD, tSensors sensorPort) {
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
	pid->sensorPort = sensorPort;
	pid->error =
		pid->targ =
		SensorValue[pid->sensorPort] =
		pid->integ = 0;
}

void setPid(Pid* pid, int target) {
	pid->targ = target;
	pid->errLast =
		pid->integ = 0;
}

int upPid(Pid* pid) {
	pid->val = SensorValue[pid->sensorPort];
	pid->errLast = pid->error;
	pid->error = pid->targ - pid->val;
	pid->prop = pid->error * pid->kP;
	pid->integ += pid->error * pid->kI;
	if(abs(pid->integ) > 127)
		pid->integ = 127 * sgn(pid->integ);
	pid->deriv = (pid->error - pid->errLast) * pid->kD;
	return round(pid->prop + pid->integ + pid->deriv);
}

Toggle liftUpToggle,
	liftDwnToggle;
#ifdef DEBUG
Toggle liftEncSave,
	rDriveEncSave,
	lDriveEncSave;
#endif

Pid lDrivePid,
	rDrivePid,
	liftPid;


const int liftSetPts[3] = {0, 824, 1098};





#ifdef DEBUG
int liftEncVals[10],
	lDriveEncVals[10],
	rDriveEncVals[10];
#endif

signed char liftTargCt = 0,
	liftTargCtLast;




task pidCtls() {
	while(true) {
		upPid(&liftPid);
		if(bIfiAutonomousMode) {
			upPid(&rDrivePid);
			upPid(&lDrivePid);
		}
		wait1Msec(20);
	}
}

void pre_auton() {
	bStopTasksBetweenModes = false;
	initPid(&liftPid, .1, 0, 0, liftEnc);
	initPid(&rDrivePid, .1, 0, 0, rDriveEnc);
	initPid(&lDrivePid, .1, 0, 0, lDriveEnc);

	if(nAvgBatteryLevel < 7600)
		playSound(soundDownwardTones);

	else if(nAvgBatteryLevel < 8000)
		playSound(soundUpwardTones);
}

task autonomous() {
	int clawEncLast,
		liftEncLast;

	startTask(pidCtls);

  setLift(127);
  wait1Msec(750);
  setLift(0);
  do {
  	clawEncLast = SensorValue[clawEnc];
  	setClaw(127);
  	wait1Msec(50);
	} while(SensorValue[clawEnc] != clawEncLast);
	setClaw(SensorValue[clawEnc] = 0);
	do {
		liftEncLast = SensorValue[liftEnc];
		setLift(-127);
		wait1Msec(50);
	} while(SensorValue[liftEnc] != liftEncLast);
	setLift(SensorValue[liftEnc] = 0);
	while(SensorValue[clawEnc] > -500) {
		setClaw(-127);
		wait1Msec(20);
	}
	setClaw(127);
	wait1Msec(20);
	setClaw(0);
}



task usercontrol() {
	int stick[4],
		drivePwrs[2],
		liftPwr;
#ifdef DEBUG
	char encValCt[3] = { 0, 0, 0 };
#endif
	const signed char stickThresh = 7;

	while (true) {
	  for(int i = 0; i < 4; i++)
			stick[i] =
				(fabs(vexRT[i]) >= stickThresh)
				? vexRT[i]
				: 0;

		upToggle(&liftUpToggle, LIFT_UP_BTN);
		upToggle(&liftDwnToggle, LIFT_DWN_BTN);
		liftTargCtLast = liftTargCt;

#ifdef DEBUG
		upToggle(&liftEncSave, SAVE_LIFT_ENC);
		upToggle(&rDriveEncSave, SAVE_RDRIVE_ENC);
		upToggle(&lDriveEncSave, SAVE_LDRIVE_ENC);

		if(pressToggle(&liftEncSave, SAVE_LIFT_ENC)) {
			liftEncVals[encValCt[0]] = SensorValue[liftEnc];
			encValCt[0]++;
		}
		if(pressToggle(&lDriveEncSave, SAVE_LDRIVE_ENC)) {
			lDriveEncVals[encValCt[1]] = SensorValue[lDriveEnc];
			encValCt[1]++;
		}
		if(pressToggle(&liftEncSave, SAVE_LIFT_ENC)) {
			rDriveEncVals[encValCt[2]] = SensorValue[rDriveEnc];
			encValCt[2]++;
		}
#endif

		liftTargCt += (pressToggle(&liftUpToggle, LIFT_UP_BTN) ^ pressToggle(&liftDwnToggle, LIFT_DWN_BTN))
			? (pressToggle(&liftUpToggle, LIFT_UP_BTN))
				? 1
				: -1
			: 0;

		if(liftTargCt > 2)
			liftTargCt = 0;
		else if(liftTargCt < 0)
			liftTargCt = 2;

		setDrive(arcade(drivePwrs, stick[LY], stick[RX]));

		if(liftTargCt != liftTargCtLast)
			setPid(&liftPid, liftSetPts[liftTargCt]);

		setClaw((CLAW_OPEN_BTN ^ CLAW_CLOSE_BTN)
			? (CLAW_OPEN_BTN)
				? 127
				: -127
			: 0);

		liftPwr = (LIFT_UP_BTN ^ LIFT_DWN_BTN)
			? (LIFT_UP_BTN)
				? 127
				: -127
			: 0;

		setLift(liftPwr);

		wait1Msec(20);
	}
}