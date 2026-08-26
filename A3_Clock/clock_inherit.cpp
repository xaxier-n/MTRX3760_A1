// A clock model
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. main() creates one plain clock and steps it
// forward by a minute.
//
// Edit this file directly to build the version asked for in the handout.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---CClock--------------------------------------------------------------------
// A CClock keeps a time, measured in whole minutes, and can advance it one
// minute at a time, report it, and reset it to where it started.
class CClock
{
  public:
    // Creates a clock with the given name and starting time, in minutes
    // since midnight.
    CClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
};

//---CAlarmClock---------------------------------------------------------------
// A CAlarmClock keeps a time like an ordinary clock AND holds an alarm time.
class CAlarmClock : public CClock
{
  public:

    CAlarmClock( const std::string& aName, int aStartMinutes );

    void SetAlarm( int aAlarmMinutes );

    bool IsRinging();

    void Report();
  
  private:
    int mAlarmMinutes;          // the time the alarm is set to go off
    bool mAlarmSet;             // true if the alarm is set, false otherwise
};

//---main----------------------------------------------------------------------
// Creates one plain clock, starts it at 06:59, advances it one minute, and
// reports it.
int main()
{
  CClock clock( "Kitchen", 419 );    // 419 minutes = 06:59
  clock.Tick();
  clock.Report();

  CAlarmClock alarm( "Bedroom", 419 );
  alarm.SetAlarm( 430 );  // set alarm for 07:10

  while ( !alarm.IsRinging() )
  {
    alarm.Tick();
  }
    alarm.Report();
  

  return 0;
}

//---CClock Implementation-----------------------------------------------------
CClock::CClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes )
{
}
//---
void CClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}

//---CAlarmClock Implementation------------------------------------------------
CAlarmClock::CAlarmClock( const std::string& aName, int aStartMinutes )
  : CClock( aName, aStartMinutes ),
    mAlarmMinutes( 0 ),
    mAlarmSet( false )
{
}

void CAlarmClock::SetAlarm( int aAlarmMinutes )
{
  mAlarmMinutes = aAlarmMinutes;
  mAlarmSet = true;
}

bool CAlarmClock::IsRinging()
{
  return mAlarmSet && ( GetTime() >= mAlarmMinutes );
}

void CAlarmClock::Report()
{
  CClock::Report();               // reuse the base's name + time (ends the line)
  if( IsRinging() )
  {
    std::cout << "ALARM!" << std::endl;
  }
}
