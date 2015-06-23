#pragma config(Sensor, dgtl1,  TouchSwitch,    sensorTouch)
#pragma config(Motor,  port2,           LauncherLeft,  tmotorVex393, openLoop)
#pragma config(Motor,  port3,           LauncherRight, tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

task startmotor();
task stopmotor();

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task startmotor()
{
	motor[LauncherLeft] = 127;
	motor[LauncherRight] = 127;
}


task stopmotor()
{
	motor[LauncherLeft] = 0;
	motor[LauncherRight] = 0;
}

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
		{
			int btn8d = vexRT[Btn8D]; // lift down
		  int btn8u = vexRT[Btn8U]; // lift up
	
	
		  if (btn8d == 1)
		  {
		  			StartTask(startmotor);
			}
	
			
		  if (btn8u == 1)
		  {
		  			StartTask(stopmotor);
			}
	}	
}
