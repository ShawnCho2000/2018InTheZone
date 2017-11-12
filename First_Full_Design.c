#pragma config(Sensor, in1,    ExternalBatteryValue, sensorAnalog)
#pragma config(Sensor, in2,    Accel_x,        sensorAccelerometer)
#pragma config(Sensor, in3,    liftPosition,   sensorPotentiometer)
#pragma config(Sensor, in4,    colorValue,     sensorReflection)
#pragma config(Sensor, in5,    clawLiftPosition, sensorPotentiometer)
#pragma config(Sensor, in7,    mobileLiftPosition, sensorPotentiometer)
#pragma config(Sensor, in8,    GyroPosition,   sensorGyro)
#pragma config(Sensor, dgtl1,  coneHeight,     sensorSONAR_cm)
#pragma config(Motor,  port1,           clawMotor,     tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           wheelLeft,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           wheelRight,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           clawLiftL,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           clawLiftR,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           armLiftLeftB,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           armLiftLeftT,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           armLiftRightB, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           armLiftRightT, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          mobileLift,    tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

const int MAX_CLAWLIFT = 3100;
const int MIN_CLAWLIFT = 2100;
const int MAX_MOBILELIFT = 2100;
// const int MAX_LIFT = 1600;
const int MAX_LIFT = 2000;
const int MIN_LIFT = 280;

const int FEED_LIFT = 1400;
const int FEED_CLAWLIFT = 2200;
const int GLOBAL_WAITER = 100;


int autonomousMode = 1;

const int POWER_CLAW_OPEN = 60;

// ---------------------------------------
// TASKS
task move();
task lift();
task claw();
// END TASKS


// ---------------------------------------
// FUNCTIONS
// LIFT
void moveLift(int power);
void moveLiftUp(int power);
void moveLiftDown(int power);

int getClawLiftPosition();
void moveLiftUpToConeHeightAndHold(int power);
void moveLiftUpToConeHeightAndStop(int power);
void moveLiftDownToConeHeightAndStop(int power);
void moveLiftUpAndStop(int distance, int power);
void moveLiftUpAndStopAuton(int distance, int power);
void moveLiftDownAndStop(int distance, int power);

// CLAW LIFT
void moveClawLift(int power);
void moveClawLiftUp(int power);
void moveClawLiftDown(int power);
void moveClawLiftUpAndStop(int distance, int power);
void moveClawLiftDownAndStop(int distance, int power);

// CLAW
void moveClaw(int power);
void openClaw(int power);
void closeClaw(int power);

// MOBILE LIFT
void moveMobileLift(int power);
void moveMobileLiftUp(int power);
void moveMobileLiftDown(int power);
void moveMobileLiftUpAndStop();
void moveMobileLiftUpAndStopAuton();
void moveMobileLiftDownAndStop();

// MOVE
void MoveAccel(int distance, int power);
void MoveAccelAuton(int distance, int power);
void MoveHelper(int power);
void TurnGyro(int distance, int power);
void TurnHelper(int power);

// MACRO
void moveMobileLiftUpToStack(int powerLift, int distanceClawLift, int powerClawLift);
void moveMobileLiftUpToStackAuton(int powerLift, int distanceClawLift, int powerClawLift);
void moveMobileLiftDownToRelease(int powerLift, int distanceClawLift, int powerClawLift);
void moveMobileLiftDownToReleaseAuton(int powerLift, int distanceClawLift, int powerClawLift);
void moveLiftUpToConeHeightAndRelease(int powerLift, int distanceClawLift, int powerClawLift);
void moveLiftDownAndPickUp(int distanceLift,int powerliftUp, int powerliftDown, int distanceClawLift, int powerClawLift);

void moveLiftDownAndPkcUpForFeed(int distanceLift, int powerliftUp, int powerliftDown, int distanceClawLift, int powerClawLift);
void moveLiftToMax(int distanceLift, int powerLift, int distanceClawLift, int powerClawLift);

// BATTERY
int AdjustPowerUsingBatteryLevel(int originalPower);
int AdjustPowerUsingExternalBatteryLevel(int originalPower);

// LCD
void AutonomousSelector(int btnLCD);
void DisplayAutonomousMode(int autonomousModeValue);
void displayBatteryLevelOnLCD(int autonomousModeValue);


// void moveLiftUpAndRelease(int distanceLift, int powerLift, int distanceClawLift, int powerClawLift);

// HELPERS
void dropCone();
void startAuton();
void stopAll();
void stopLift();
void stopClawLift();
void stopClaw();

// END FUNCTIONS

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	startAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task move()
{
	while (true)
	{
		wait1Msec(50);

		int ch1 = vexRT[Ch1];
		int ch3 = vexRT[Ch3];

		motor[wheelLeft] = ch3 + ch1;
		motor[wheelRight] = -(ch3 - ch1);

		if (abs(motor[wheelRight]) < 17 || abs(motor[wheelLeft]) < 17)
		{
			motor[wheelLeft] = 0;
			motor[wheelRight] = 0;
		}
	}
}


task lift()
{
	const int powerliftUp = 100;
	const int powerliftDown = 40;
	const int powerClawLiftUp = 80;
	const int powerClawLiftDown = 60;
	const int powerMobileLift = 120;

	while (true)
	{
		wait1Msec(50);

		if (vexRT[Btn8R] == 1) {
			if (vexRT[Btn7U] == 1) { //Move Lift up with btn 7U
				moveLiftUp(powerliftUp); //80
				// if (vexRT[Btn7U] == 0) {
				// 	moveLiftUp(5); //holding power
				// }
			}
			else if (vexRT[Btn7D] == 1){ //Move Lift down with btn 7D
				moveLiftDown(powerliftDown); //-40
				// if (vexRT[Btn7D] == 0) {
				// 	moveLiftDown(15); //holding power
				// }
			}
			else if (vexRT[Btn5U] == 1){
				moveClawLiftUp(powerClawLiftUp);
				// moveClawLiftUpAndStop(MAX_CLAWLIFT, powerClawLiftUp);
			}
			else if (vexRT[Btn5D] == 1){
				moveClawLiftDown(powerClawLiftDown);
				// moveClawLiftDownAndStop(MIN_CLAWLIFT, powerClawLiftDown);
			}

			if (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0){
				stopClawLift();
			}

			if (vexRT[Btn7U] == 0 && vexRT[Btn7D] == 0){
				stopLift();
			}
		}
		else if (vexRT[Btn8R] == 0) {
			if (vexRT[Btn7U] == 1) {
				moveLiftUpToConeHeightAndRelease(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
			}
			else if (vexRT[Btn7D] == 1) {
				moveLiftDownAndPickUp(MIN_LIFT, powerliftUp, powerliftDown, MIN_CLAWLIFT, powerClawLiftDown);
				// moveLiftDownAndStop(230, powerliftDown);
			}
			else if (vexRT[Btn5U] == 1){
				moveClawLiftUp(powerClawLiftUp / 2);
			}
			else if (vexRT[Btn5D] == 1){
				moveClawLiftDown(powerClawLiftDown / 2);
			}
			// else if (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0){
			// 	stopClawLift();
			// }
			else if (vexRT[Btn7R] == 1){
				moveMobileLiftDownToRelease(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
				// moveMobileLiftDownAndStop(750, 80);
				// moveMobileLiftDown(30);
			}
			else if (vexRT[Btn7L] == 1){
				moveMobileLiftUpToStack(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
				// moveMobileLiftUp(30);
			}
			else if (vexRT[Btn8U] == 1){
				long startTime = nPgmTime;

				//moveLiftToMax(MAX_LIFT, powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
				moveMobileLiftDownToReleaseAuton(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
				wait1Msec(GLOBAL_WAITER);
				MoveAccel(75, 50);
				wait1Msec(GLOBAL_WAITER);
				moveMobileLiftUpToStackAuton(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);	
				moveLiftDownAndStop(280, 50);
				wait1Msec(GLOBAL_WAITER);				
				//moveLiftDownAndPickUp(MIN_LIFT, powerliftUp, powerliftDown, MIN_CLAWLIFT, powerClawLiftDown);
				openClaw(POWER_CLAW_OPEN); //for one cone only!
				wait1Msec(400); //for one cone only!
				stopClaw(); //for one cone only!
				/*MoveAccel(60, 60);
				wait1Msec(GLOBAL_WAITER);
				moveClawLiftDown(35);
				wait1Msec(GLOBAL_WAITER);
				moveClawLiftDown(0);
				closeClaw(50);
				wait1Msec(700);
				closeClaw(0);
				moveLiftUpToConeHeightAndRelease(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
				wait1Msec(GLOBAL_WAITER);
				openClaw(50);
				wait1Msec(225);
				stopClaw();*/
				moveLiftUpAndStop(1600, powerliftUp);
				MoveAccel(800, -100);
				wait1Msec(GLOBAL_WAITER);
				TurnGyro(500, -50);
				wait1Msec(GLOBAL_WAITER);
				MoveAccel(250, -100);
				wait1Msec(GLOBAL_WAITER);
				TurnGyro(750, -50);
				wait1Msec(GLOBAL_WAITER);
				MoveAccel(300, 70);
				wait1Msec(GLOBAL_WAITER);
				MoveAccel(80, 30);
				MoveHelper(20);
				moveMobileLiftDownAndStop();
				wait1Msec(GLOBAL_WAITER);
				/*moveMobileLiftUp(120);
				wait1Msec(300);
				moveMobileLiftDownAndStop();*/
				MoveAccel(300, -80);

				writeDebugStreamLine("autonomous) Time: %d", nPgmTime - startTime);

			}
			else if (vexRT[Btn8D] == 1){
				moveLiftDownAndPkcUpForFeed(FEED_LIFT, powerliftUp, powerliftDown / 2, FEED_CLAWLIFT, powerClawLiftDown);
				// moveMobileLiftDownToReleaseAuton(powerliftUp, MAX_CLAWLIFT, powerClawLiftUp);
			}

			if (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0 && vexRT[Btn6U] == 0){
				stopClawLift();
			}
		}

	}
}

task claw()
{
	while (true)
	{
		wait1Msec(50);

		if (vexRT[Btn6U] == 1){
			moveClawLiftDown(25);
			closeClaw(50);
		}
		else if (vexRT[Btn6D] == 1){
			openClaw(POWER_CLAW_OPEN);
			wait1Msec(250);
			stopClaw();
		}
	}
}


task usercontrol()
{
	//startTask(move);
	startTask(lift);
	startTask(claw);
	// User control code here, inside the loop
	//int on = 0;
	while (true)
	{
		wait1Msec(50);


		int btnLCD = nLCDButtons;
		if (btnLCD > 0)
		{
			AutonomousSelector(btnLCD);
			// startTask(displayBatteryLevelOnLCD);
		}

		/*if(vexRT[Btn7L] == 1){ //toggle auto stay
		if (on == 0){
		on = 1;
		}
		else if (on != 0){
		on = 0;
		}
		}
		if (on == 0){
		moveLift(30);
		}
		else if (on != 0){
		moveLift(0);
		}*/
		while(vexRT[Btn8L] == 1){
			stopAll();
		}
		while (vexRT[Btn8R] == 1) {
			dropCone();
		}


	}
}

// -------------------------------------
// SENSORS
int getConeDistance()
{
	return SensorValue(coneHeight);
}
int getLiftPosition()
{
	return SensorValue(liftPosition);
}

int getClawLiftPosition()
{
	return SensorValue(clawLiftPosition);
}

int getMobileLiftPosition()
{
	return SensorValue(mobileLiftPosition);
}

// END SENSORS


// -------------------------------------
// STOPS
void stopAll(){
	motor[armLiftLeftB] = 0;
	motor[armLiftLeftT] = 0;
	motor[armLiftRightB] = 0;
	motor[armLiftRightT] = 0;
	motor[clawMotor] = 0;
	motor[clawLiftL] = 0;
	motor[clawLiftR] = 0;
	motor[mobileLift] = 0;
	motor[wheelLeft] = 0;
	motor[wheelRight] = 0;
}
// END STOPS

// -------------------------------------
// LIFT
void holdLift(){
	moveLift(10);
}


void stopLift(){
	moveLift(0);
}

void moveLiftUp(int power) {

	if (getLiftPosition() >= MAX_LIFT)
	{
		return;
	}
	moveLift(power);
}

void moveLiftDown(int power) {

	if (getLiftPosition() <= MIN_LIFT)
	{
		return;
	}
	moveLift(-power);
}

void moveLift(int power){
	int newPower = AdjustPowerUsingBatteryLevel(power);
	motor[armLiftLeftB] = -newPower;
	motor[armLiftLeftT] = newPower;
	motor[armLiftRightB] =  newPower;
	motor[armLiftRightT] = -newPower;
}

// HELPER
void moveLiftUpToConeHeightAndRelease(int powerLift, int distanceClawLift, int powerClawLift) {
	stopClaw();
	moveClawLiftUpAndStop(MIN_CLAWLIFT - 300, powerClawLift);
	moveLiftUpToConeHeightAndHold(powerLift);
	wait1Msec(200);
	moveClawLiftUpAndStop(distanceClawLift, powerClawLift);
	wait1Msec(200);
	wait1Msec(200);
	moveLiftDownToConeHeightAndStop(30);
	wait1Msec(200);
	// openClaw(50);
	// wait1Msec(225);
	// stopClaw();
}

void moveLiftUpToConeHeightAndHold(int power) {
	// writeDebugStreamLine("moveLiftUpToConeHeightAndHold) maxHeight: %d", maxHeight);

	moveLiftUp(power);
	wait1Msec(100);

	int distaince = getConeDistance();
	int height = getLiftPosition();
	// while (distaince > 0 && distaince < 20){
	int count = 0;
	int tPower = power;
	while (true){
		if (distaince > 20)
		{
			writeDebugStreamLine("moveLiftUpToConeHeightAndHold #1) Cone Distaince: %d, Lift Height: %d", distaince, height);
			count++;
			tPower = 0;

			wait1Msec(50);
		}
		else if (distaince < 21 && count > 0)
		{
			writeDebugStreamLine("moveLiftUpToConeHeightAndHold #2) Cone Distaince: %d, Lift Height: %d", distaince, height);

			count  = 0;
			tPower = power;
		}

		if (height >= MAX_LIFT)
		{
			writeDebugStreamLine("moveLiftUpToConeHeightAndHold #3) Cone Distaince: %d, Lift Height: %d", distaince, height);
			break;
		}

		if (count > 3)
		{
			break;
		}

		moveLiftUp(tPower);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}

		distaince = getConeDistance();
		height = getLiftPosition();
	}


	holdLift();

	// wait1Msec(100);
	// stopLift();
}

void moveLiftUpToConeHeightAndStop(int power) {

	moveLiftUp(power);
	wait1Msec(100);


	int distaince = getConeDistance();
	while (distaince > 0 && distaince < 25){
		moveLiftUp(power);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}

		distaince = getConeDistance();
	}

	// wait1Msec(100);
	stopLift();
}

void moveLiftDownToConeHeightAndStop(int power) {

	moveLiftDown(power);
	wait1Msec(100);

	int distaince = getConeDistance();
	// while (distaince > 20){
	while (true){

		if (0 < distaince && distaince < 20)
		{
			break;
		}

		moveLiftDown(power);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}

		distaince = getConeDistance();
	}

	writeDebugStreamLine("moveLiftDownToConeHeightAndStop) Cone Distaince: %d", distaince);

	// wait1Msec(100);
	stopLift();
}

void moveLiftUpAndStop(int distance, int power) {

	while (getLiftPosition() < distance){
		moveLiftUp(power);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}
	stopLift();
}

void moveLiftUpAndStopAuton(int distance, int power) {

	moveClawLiftUp(80);
	while (getLiftPosition() < distance){
		moveLiftUp(power);
		if (getClawLiftPosition() > MAX_CLAWLIFT){
			stopClawLift();
		}
	}
	stopLift();
}

void moveLiftToMax(int distanceLift, int powerLift, int distanceClawLift, int powerClawLift) {
	moveLiftUpAndStop(distanceLift, powerLift);
	moveClawLiftUpAndStop(distanceClawLift, powerClawLift);
}

void moveLiftDownAndPickUp(int distanceLift, int powerliftUp, int powerliftDown, int distanceClawLift, int powerClawLift) {
	openClaw(POWER_CLAW_OPEN);
	wait1Msec(500);//CHANGED FROM 200
	moveLiftUpToConeHeightAndHold((powerliftUp / 3) * 2/*powerliftUp*/);
	stopClaw();
	wait1Msec(200);
	moveClawLiftDownAndStop(distanceClawLift, powerClawLift);
	wait1Msec(200);
	moveLiftDownAndStop(distanceLift, powerliftDown);
	wait1Msec(200);
}

void moveLiftDownAndPkcUpForFeed(int distanceLift, int powerliftUp, int powerliftDown, int distanceClawLift, int powerClawLift) {
	openClaw(POWER_CLAW_OPEN);
	wait1Msec(500);//CHANGED FROM 200
	moveLiftUpToConeHeightAndHold(powerliftUp);
	stopClaw();
	wait1Msec(200);
	moveClawLiftDownAndStop(distanceClawLift, powerClawLift);
	wait1Msec(200);
	moveLiftDownAndStop(distanceLift, powerliftDown);
	wait1Msec(200);
	// moveLiftUpToConeHeightAndHold(powerLift);
	// wait1Msec(200);
	// moveClawLiftDownAndStop(distanceClawLift + 200, powerClawLift);
	// wait1Msec(200);
	// moveLiftDownAndStop(distanceLift, powerLift / 2);
	// wait1Msec(200);
	// moveLiftUpAndStop(distanceLift, powerLift);
	// wait1Msec(200);
	// moveClawLiftDownAndStop(distanceClawLift - 230, powerClawLift);
}

void moveLiftDownAndStop(int distance, int power) {

	while (getLiftPosition() > distance){
		moveLiftDown(power);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}
	wait1Msec(200);
	stopLift();
}
// END MOVES

// -------------------------------------
// CLAW LIFT
void stopClawLift(){
	moveClawLift(0);
}

void moveClawLiftUp(int power){
	moveClawLift(power);
}

void moveClawLiftDown(int power){
	moveClawLift(-power);
}

void moveClawLift(int power){
	int newPower = AdjustPowerUsingExternalBatteryLevel(power);

	motor[clawLiftL] = newPower;
	motor[clawLiftR] = -newPower;
}

void moveClawLiftUpAndStop(int distance, int power) {

	while (getClawLiftPosition() < distance){
		moveClawLiftUp(power);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}
	stopClawLift();
}

void moveClawLiftDownAndStop(int distance, int power) {

	while (getClawLiftPosition() > distance){
		moveClawLiftDown(power);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}
	stopClawLift();
}
// END CLAW LIFT


// -------------------------------------
// CLAW
void stopClaw(){
	moveClaw(0);
}

void openClaw(int power){
	moveClaw(power);
}

void closeClaw(int power){
	moveClaw(-power);
}

void moveClaw(int power){
	motor[clawMotor] = power;
}

void dropCone() {
}
// END CLAW


// -------------------------------------
// MOBILE LIFT
void stopMobileLift(){
	moveMobileLift(0);
}

void moveMobileLiftUp(int power){
	moveMobileLift(power);
}

void moveMobileLiftDown(int power){
	moveMobileLift(-power);
}

void moveMobileLift(int power){
	motor[mobileLift] = power;
}

void moveMobileLiftUpToStack(int powerLift, int distanceClawLift, int powerClawLift) {
	moveLiftUpAndStop(450, powerLift);
	wait1Msec(200);
	moveClawLiftUpAndStop(distanceClawLift, powerClawLift);
	wait1Msec(200);
	moveMobileLiftUpAndStop();
}

void moveMobileLiftUpToStackAuton(int powerLift, int distanceClawLift, int powerClawLift) {
	moveLiftUpAndStop(450, powerLift);
	wait1Msec(200);
	moveMobileLiftUpAndStop();
}


void moveMobileLiftDownToReleaseAuton(int powerLift, int distanceClawLift, int powerClawLift) {
	moveLiftUpToConeHeightAndHold(powerLift / 2);
	wait1Msec(200);
	moveLiftUpAndStopAuton(1600, powerLift);
	wait1Msec(200);
	//moveClawLiftUpAndStop(distanceClawLift, powerClawLift);
	moveMobileLiftDownAndStop();
	MoveAccelAuton(800, 100);
}

void moveMobileLiftUpAndStop() {

	while (getMobileLiftPosition() < MAX_MOBILELIFT){
		moveMobileLiftUp(120);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}

	stopMobileLift();
}

void moveMobileLiftUpAndStopAuton() {

	while (getMobileLiftPosition() < MAX_MOBILELIFT){
		moveLiftDownAndStop(280, 50);

		while (getLiftPosition() > 280){
			moveLiftDown(50);
		}
		wait1Msec(200);
		stopLift();
		moveMobileLiftUp(120);
	}

	stopMobileLift();
}


void moveMobileLiftDownToRelease(int powerLift, int distanceClawLift, int powerClawLift) {
	openClaw(POWER_CLAW_OPEN);
	wait1Msec(200);
	moveLiftUpToConeHeightAndHold(powerLift / 2);
	stopClaw();

	wait1Msec(200);
	moveLiftUpAndStop(450, powerLift);
	wait1Msec(200);

	moveClawLiftUpAndStop(distanceClawLift, powerClawLift);
	wait1Msec(200);
	moveMobileLiftDownAndStop();
}

void moveMobileLiftDownAndStop() {

	while (getMobileLiftPosition() > MAX_MOBILELIFT){
		moveMobileLiftDown(120);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}

	while (getMobileLiftPosition() > 750){
		moveMobileLiftDown(60);
		if (vexRT[Btn8L] == 1)
		{
			break;
		}
	}

	stopMobileLift();
}
// END MOBILE LIFT

// -------------------------------------
// MOVE
void MoveAccel(int distance, int power) {
	// ClearEncoder();

	//writeDebugStreamLine("MoveValue_Accel) Started ===");
	int velocity = 0;
	int position = 0;
	int value = 0;
	clearTimer(T3);
	int newPower = AdjustPowerUsingExternalBatteryLevel(power);
	while (abs(position) < abs(distance)){
		value = SensorValue[Accel_x];
		velocity += value;
		//velocity = (value == 0)? velocity : velocity + value;
		position += velocity;

		// writeDebugStreamLine("MoveValue_Accel) pos: %d, vel: %d ", position, velocity);
		if (time1[T3] >= 2000)
		{
			break;
		}
		MoveHelper(newPower);
		wait1Msec(100);
	}
	MoveHelper(0);
}

void MoveAccelAuton(int distance, int power) {
	// ClearEncoder();

	//writeDebugStreamLine("MoveValue_Accel) Started ===");
	int velocity = 0;
	int position = 0;
	int value = 0;
	clearTimer(T3);
	int newPower = AdjustPowerUsingExternalBatteryLevel(power);
	while (abs(position) < abs(distance)){
		value = SensorValue[Accel_x];
		velocity += value;
		//velocity = (value == 0)? velocity : velocity + value;
		position += velocity;

		// writeDebugStreamLine("MoveValue_Accel) pos: %d, vel: %d ", position, velocity);
		if (time1[T3] >= 2000)
		{
			break;
		}
		MoveHelper(newPower);
		wait1Msec(100);
	}
	MoveHelper(0);
}

void MoveHelper(int power)
{
	motor[wheelLeft] = power;
	motor[wheelRight] = -power;
}

void TurnGyro(int distance, int power) {
	// wait1Msec(time);
	SensorValue[GyroPosition] = 0;
	int newPower = AdjustPowerUsingExternalBatteryLevel(power);
	while (abs(SensorValue[GyroPosition])<abs(distance)){
		TurnHelper(newPower);
	}
	TurnHelper(0);
}

void TurnHelper(int power)
{
	motor[wheelLeft] = power;
	motor[wheelRight] = power;
}

// void TurnRight(int power)
// {
// 	motor[wheelLeft] = -power;
// 	motor[wheelRight] = -power;
// }
// END MOVE

// -------------------------------------
// ADJUST BATTERY
int AdjustPowerUsingBatteryLevel(int originalPower)
{
	float batteryLevel = nImmediateBatteryLevel;
	float batteryOffset =	7500 / batteryLevel;
	int adjustedPower = originalPower * batteryOffset;
	//  writeDebugStreamLine("(AjustBattery) BatterLevel: %d - OriginalPower: %d - WantedPower: %d", AdjustBatteryLevel, OriginalPower, WantedPower);
	return adjustedPower;
}

int AdjustPowerUsingExternalBatteryLevel(int originalPower)
{
	float batteryLevel = SensorValue[ExternalBatteryValue] * 3.57;

	float batteryOffset =	7500 / batteryLevel;
	int adjustedPower = originalPower * batteryOffset;
	//  writeDebugStreamLine("(AjustBattery) BatterLevel: %d - OriginalPower: %d - WantedPower: %d", AdjustBatteryLevel, OriginalPower, WantedPower);
	return adjustedPower;
}

// END ADJUST BATTERY


// -------------------------------------
// LCD
void AutonomousSelector(int btnLCD)
{
	writeDebugStreamLine("AutonomousSelector) button: %d", btnLCD);

	bLCDBacklight=true;

	displayBatteryLevelOnLCD(autonomousMode);
	int autonomousModeValue = autonomousMode;

	int button = 0;
	while(true)
	{
		button = nLCDButtons;

		if (button == 2 || vexRT[Btn8L] == 1)
		{
			displayBatteryLevelOnLCD(autonomousModeValue);

			bLCDBacklight=false;
			break;
		}
		else if (button == 1 || vexRT[Btn6U] == 1)
		{
			if (autonomousModeValue > 1)
			{
				autonomousModeValue--;
			}

			DisplayAutonomousMode(autonomousModeValue);
		}
		else if (button == 4 || vexRT[Btn6D] == 1)
		{
			if (autonomousModeValue < 3)
			{
				autonomousModeValue++;
			}

			DisplayAutonomousMode(autonomousModeValue);
		}
	}

	bLCDBacklight=false;
}

void DisplayAutonomousMode(int autonomousModeValue)
{
	writeDebugStreamLine("DisplayAutonomousMode) autonomousModeValue: %d", autonomousModeValue);

	clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
	clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

	string text;
	//}
	switch(autonomousModeValue)
	{
	case 1:
		{
			text = "Autonomous";
			break;
		}
	case 2:
		{
			//text = "ProgrammingSkill";
			text = "None";
			break;
		}
	case 3:
		{
			text = "ProgSkill";
			break;
		}
	}

	//Display the Primary Robot battery voltage
	// displayLCDString(0, 0, "Autonomous: ");
	displayLCDString(0, 0, text);

	wait1Msec(500);
}

void displayBatteryLevelOnLCD(int autonomousModeValue)
{
	writeDebugStreamLine("displayBatteryLevelOnLCD) autonomousModeValue: %d", autonomousModeValue);

	clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
	clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

	autonomousMode = autonomousModeValue;

	string text;
	sprintf(text, "Selected: %d", autonomousMode); //Build the value to be displayed

	//Display the Primary Robot battery voltage
	// displayLCDString(0, 0, "Autonomous: ");
	displayLCDString(0, 0, text);

	wait1Msec(800);

	//while(true)                                                        // An infinite loop to keep the program running until you terminate it
	//{
	clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
	clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

	string mainBattery, externalBattery;

	//Display the Primary Robot battery voltage
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	//float externalBatteryLevel = SensorValue[ExternalBatteryValue];
	//Display the Backup battery voltage
	displayLCDString(1, 0, "External: ");
	sprintf(externalBattery, "%1.2f%c", (SensorValue[ExternalBatteryValue] * 3.57)/1000.0, 'V');    //Build the value to be displayed
	displayNextLCDString(externalBattery);

	//Short delay for the LCD refresh rate
	wait1Msec(500);
}

void startAuton() {
	closeClaw(50);
	wait1Msec(400);
	closeClaw(0);
}

// END LCD
