// A line-following robot (function-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a struct, and free functions operate on those
// structs by taking them as arguments.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <stdio.h>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added
const double ReducedSpeed = 0.25;     // forward speed once the battery is low
const int FullCharge = 100;           // charge the battery starts at
const int DrainPerCycle = 10;         // charge lost each cycle
const int LowChargeThreshold = 80;    // below this, the robot slows down

//---SLineSensor---------------------------------------------------------------
// SLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
struct SLineSensor
{
  int cycle;              // how many readings have been taken so far
};

//---SController---------------------------------------------------------------
// SController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
struct SController
{
  double lastError;       // the reading from the previous cycle
};

//---SMotor--------------------------------------------------------------------
// SMotor holds one drive motor's label and its current speed.
struct SMotor
{
  const char* pName;      // the motor's label, e.g. "Left"
  double speed;           // current speed, -1.0 to 1.0
};

//---SBattery------------------------------------------------------------------
// SBattery holds the robot's remaining charge. It drops a little each cycle,
// and once it is low the robot drives more slowly to conserve power.
struct SBattery
{
  int charge;             // how much charge is left, 0 to FullCharge
};

//---Function declarations-----------------------------------------------------
void InitLineSensor( SLineSensor* apSensor );
void InitController( SController* apController );
void InitMotor( SMotor* apMotor, const char* aName );
void InitBattery( SBattery* apBattery );
void DrainBattery( SBattery* apBattery );
bool BatteryIsLow( SBattery* apBattery );

int ReadLineSensor( SLineSensor* apSensor );
double ComputeSteering( SController* apController, int aError );
void SetMotorSpeed( SMotor* apMotor, double aSpeed );

void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor, SBattery* apBattery );
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor );

//---main----------------------------------------------------------------------
// Sets up each part of the robot, then runs it for a number of cycles,
// reporting the motors after each one.
int main()
{
  SLineSensor sensor;
  SController controller;
  SMotor leftMotor;
  SMotor rightMotor;
  SBattery battery;

  InitLineSensor( &sensor );
  InitController( &controller );
  InitMotor( &leftMotor, "Left" );
  InitMotor( &rightMotor, "Right" );
  InitBattery( &battery );

  for( int i = 0; i < NumCycles; ++i )
  {
    UpdateRobot( &sensor, &controller, &leftMotor, &rightMotor, &battery );
    ReportRobot( &leftMotor, &rightMotor );
  }

  return 0;
}

//---InitLineSensor------------------------------------------------------------
// Starts the sensor at the beginning of the track.
void InitLineSensor( SLineSensor* apSensor )
{
  apSensor->cycle = 0;
}

//---InitController------------------------------------------------------------
// Starts the controller with no previous reading.
void InitController( SController* apController )
{
  apController->lastError = 0.0;
}

//---InitMotor-----------------------------------------------------------------
// Gives a motor its label and sets it stopped.
void InitMotor( SMotor* apMotor, const char* aName )
{
  apMotor->pName = aName;
  apMotor->speed = 0.0;
}

//---InitBattery---------------------------------------------------------------
// Starts the battery fully charged.
void InitBattery( SBattery* apBattery )
{
  apBattery->charge = FullCharge;
}

//---DrainBattery--------------------------------------------------------------
// Uses up a little charge, once per cycle.
void DrainBattery( SBattery* apBattery )
{
  apBattery->charge -= DrainPerCycle;
}

//---BatteryIsLow--------------------------------------------------------------
// Reports whether the charge has dropped below the point where the robot
// needs to slow down.
bool BatteryIsLow( SBattery* apBattery )
{
  return apBattery->charge < LowChargeThreshold;
}

//---ReadLineSensor------------------------------------------------------------
// Returns how far the robot is off the line this cycle. Positive means the
// line is off to one side, negative the other.
int ReadLineSensor( SLineSensor* apSensor )
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ apSensor->cycle ];
  ++apSensor->cycle;

  return reading;
}

//---ComputeSteering-----------------------------------------------------------
// Works out how hard to steer, from how far off the line the robot is and how
// quickly that is changing.
double ComputeSteering( SController* apController, int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - apController->lastError );
  apController->lastError = aError;

  return steering;
}

//---SetMotorSpeed-------------------------------------------------------------
// Sets one motor's speed.
void SetMotorSpeed( SMotor* apMotor, double aSpeed )
{
  apMotor->speed = aSpeed;
}

//---UpdateRobot---------------------------------------------------------------
// Runs one cycle: read the sensor, work out the steering, drain the battery,
// and set both motors using the resulting forward speed.
void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor, SBattery* apBattery )
{
  int error = ReadLineSensor( apSensor );
  double steering = ComputeSteering( apController, error );

  DrainBattery( apBattery );
  double forwardSpeed = BaseSpeed;
  if( BatteryIsLow( apBattery ) )
  {
    forwardSpeed = ReducedSpeed;
  }

  SetMotorSpeed( apLeftMotor, forwardSpeed + steering );
  SetMotorSpeed( apRightMotor, forwardSpeed - steering );
}

//---ReportRobot---------------------------------------------------------------
// Prints the state of both of the robot's motors.
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor )
{
  printf( "%s motor %g, %s motor %g\n",
          apLeftMotor->pName, apLeftMotor->speed,
          apRightMotor->pName, apRightMotor->speed );
}