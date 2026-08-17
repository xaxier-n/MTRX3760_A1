// A line-following robot (object-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a class, and a CRobot holds those parts and puts
// them to work.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added
const double ReducedSpeed = 0.25;     // forward speed once the battery is low
const int FullCharge = 100;           // charge the battery starts at
const int DrainPerCycle = 10;         // charge lost each cycle
const int LowChargeThreshold = 80;    // below this, the robot slows down

//---CLineSensor---------------------------------------------------------------
// A CLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
class CLineSensor
{
  public:
    // Creates a sensor at the beginning of the track.
    CLineSensor();

    // Read returns how far the robot is off the line this cycle. Positive
    // means the line is off to one side, negative the other.
    int Read();

  private:
    int mCycle;             // how many readings have been taken so far
};

//---CController---------------------------------------------------------------
// A CController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
class CController
{
  public:
    // Creates a controller with no previous reading.
    CController();

    // ComputeSteering works out how hard to steer, from how far off the line
    // the robot is and how quickly that is changing.
    double ComputeSteering( int aError );

  private:
    double mLastError;      // the reading from the previous cycle
};

//---CMotor--------------------------------------------------------------------
// A CMotor is a single drive motor with a label and a current speed.
class CMotor
{
  public:
    // Creates a motor with the given label, stopped.
    CMotor( const std::string& aName );

    // SetSpeed sets the motor's speed.
    void SetSpeed( double aSpeed );

    // Report prints the motor's label and current speed.
    void Report();

  private:
    std::string mName;      // the motor's label, e.g. "Left"
    double mSpeed;          // current speed, -1.0 to 1.0
};

//---CBattery------------------------------------------------------------------
// A CBattery holds the robot's remaining charge. It drops a little each cycle,
// and reports when it is low so the robot can slow down to conserve power.
class CBattery
{
  public:
    // Creates a battery fully charged.
    CBattery();
    // Drain uses up a little charge, once per cycle.
    void Drain();
    // IsLow reports whether the charge has dropped below the point where the
    // robot needs to slow down.
    bool IsLow();

  private:
    int mCharge;            // how much charge is left, 0 to FullCharge
};

//---CRobot--------------------------------------------------------------------
// A CRobot has a line sensor, a controller, and two drive motors. It offers
// operations described in terms of the whole robot rather than its parts.
class CRobot
{
  public:
    // Creates a robot with all of its parts ready to run.
    CRobot();

    // Update runs one cycle of the robot.
    void Update();

    // Report prints the state of the robot.
    void Report();

  private:
    CLineSensor mSensor;
    CController mController;
    CBattery mBattery;
    CMotor mLeftMotor;
    CMotor mRightMotor;
};

//---main----------------------------------------------------------------------
// Creates a robot, then runs it for a number of cycles, reporting it after
// each one.
int main()
{
  CRobot robot;

  for( int i = 0; i < NumCycles; ++i )
  {
    robot.Update();
    robot.Report();
  }

  return 0;
}

//---CLineSensor Implementation------------------------------------------------
CLineSensor::CLineSensor()
  : mCycle( 0 )
{
}
//---
int CLineSensor::Read()
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ mCycle ];
  ++mCycle;

  return reading;
}

//---CController Implementation------------------------------------------------
CController::CController()
  : mLastError( 0.0 )
{
}
//---
double CController::ComputeSteering( int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - mLastError );
  mLastError = aError;

  return steering;
}

//---CMotor Implementation-----------------------------------------------------
CMotor::CMotor( const std::string& aName )
  : mName( aName ),
    mSpeed( 0.0 )
{
}
//---
void CMotor::SetSpeed( double aSpeed )
{
  mSpeed = aSpeed;
}
//---
void CMotor::Report()
{
  std::cout << mName << " motor " << mSpeed;
}

//---CBattery Implementation---------------------------------------------------
CBattery::CBattery()
  : mCharge( FullCharge )
{
}
void CBattery::Drain()
{
  mCharge -= DrainPerCycle;
}
bool CBattery::IsLow()
{
  return mCharge < LowChargeThreshold;
}

//---CRobot Implementation-----------------------------------------------------
CRobot::CRobot()
  : mLeftMotor( "Left" ),
    mRightMotor( "Right" )
{
}
//---
void CRobot::Update()
{
  int error = mSensor.Read();
  double steering = mController.ComputeSteering( error );

  mBattery.Drain();
  double forwardSpeed = BaseSpeed;
  if( mBattery.IsLow() )
  {
    forwardSpeed = ReducedSpeed;
  }

  mLeftMotor.SetSpeed( forwardSpeed + steering );
  mRightMotor.SetSpeed( forwardSpeed - steering );
}
//---
void CRobot::Report()
{
  mLeftMotor.Report();
  std::cout << ", ";
  mRightMotor.Report();
  std::cout << std::endl;
}
