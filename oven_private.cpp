// An oven temperature model (encapsulated version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is private, and main() works through meaningful
// functions rather than touching the temperatures directly.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>


//---COven---------------------------------------------------------------------
// COven holds an oven's name and current temperature. The temperature is
// private: callers change and inspect it only through the functions below.
class COven
{
  public:
    // Creates an oven with the given name, at room temperature.
    COven( const std::string& aName );

    // WarmUp raises the oven's temperature by one step.
    void WarmUp();

    // IsOverheating reports whether the oven has passed its safe limit.
    bool IsOverheating();

    // Report prints the oven's name and current temperature.
    void Report();

  private:
    std::string mName;       // the oven's label, e.g. "Reflow oven"
    int mTemperatureC10;     // CHANGED: current temperature in tenths of a degree Celsius (renamed)
};

//---main----------------------------------------------------------------------
// Sets up two ovens, warms each in steps, checks each for overheating, and
// reports both.
int main()
{
  COven ReflowOven( "Reflow oven" );
  COven CuringOven( "Curing oven" );

  for( int i = 0; i < 5; ++i )
    ReflowOven.WarmUp();

  for( int i = 0; i < 8; ++i )
    CuringOven.WarmUp();

  if( ReflowOven.IsOverheating() )
    std::cout << "Warning: oven is overheating!" << std::endl;

  if( CuringOven.IsOverheating() )
    std::cout << "Warning: oven is overheating!" << std::endl;

  ReflowOven.Report();
  CuringOven.Report();

  return 0;
}

//---COven Implementation------------------------------------------------------
COven::COven( const std::string& aName )
  : mName( aName ),
    mTemperatureC10( 200 )                // CHANGED: start at room temperature in tenths of a degree
{
}
//---
void COven::WarmUp()
{
  mTemperatureC10 += 10;                  // CHANGED: warm up by 1 degree (10 tenths)
}
//---
bool COven::IsOverheating()
{
  return mTemperatureC10 >= 2500;         // CHANGED: overheating limit is 250 C (2500 tenths)
}
//---
void COven::Report()
{
  int temp = mTemperatureC10 / 10;                                // ADDED: convert to degrees C
  std::cout << mName << " is at " << temp << "C" << std::endl;    // CHANGED: display temp in deg C
}



/* SUMMARY OF CHANGES
  - Renamed mTemperatureC to mTemperatureC10 for clarity
  - Room temperature, incrementation value, and overheating threshold required altering to reflect the new units
  - Report function required conversion to Celsius before displaying
*/