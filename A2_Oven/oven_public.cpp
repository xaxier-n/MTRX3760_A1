// An oven temperature model (public-data version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is stored in public member variables, and main()
// reads and changes the temperatures directly.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---COven---------------------------------------------------------------------
// COven holds an oven's name and current temperature. Both members are public,
// so any code can read or change them directly.
class COven
{
  public:
    std::string mName;       // the oven's label, e.g. "Reflow oven"
    int mTemperatureC10;     // CHANGED: current temperature, in tenths of a degree Celsius
};

//---main----------------------------------------------------------------------
// Sets up two ovens, warms each in one-degree steps, checks each for
// overheating, and reports both. Every step reaches into the ovens' data
// directly.
int main()
{
  COven ReflowOven;
  ReflowOven.mName = "Reflow oven";
  ReflowOven.mTemperatureC10 = 200;           // CHANGED: start at room temperature (tenths of a degree)

  COven CuringOven;
  CuringOven.mName = "Curing oven";
  CuringOven.mTemperatureC10 = 200;           // CHANGED: start at room temperature (tenths of a degree)

  for( int i = 0; i < 5; ++i )
    ReflowOven.mTemperatureC10 += 10;         // CHANGED: warm up by one degree (ten tenths)

  for( int i = 0; i < 8; ++i )
    CuringOven.mTemperatureC10 += 10;         // CHANGED: warm up by one degree (ten tenths)

  if( ReflowOven.mTemperatureC10 >= 2500 )    // CHANGED: overheating limit is 250 C (now in tenths)
    std::cout << "Warning: oven is overheating!" << std::endl;

  if( CuringOven.mTemperatureC10 >= 2500 )    // CHANGED: overheating limit is 250 C (now in tenths)
    std::cout << "Warning: oven is overheating!" << std::endl;

  int temp = ReflowOven.mTemperatureC10/10;             // ADDED: convert to deg. C
  std::cout << ReflowOven.mName << " is at "
            << temp << "C" << std::endl;                // CHANGED: display temp in deg C

  temp = CuringOven.mTemperatureC10/10;                 // ADDED: convert to deg. C
  std::cout << CuringOven.mName << " is at "
            << temp << "C" << std::endl;                // CHANGED: display temp in deg C

  return 0;
}


/* SUMMARY OF CHANGES
  - Renamed mTemperatureC to mTemperatureC10 for clarity
  - Room temperature, incrementation value, and overheating threshold required altering to reflect the new units - 
    these changes had to be made for each oven 
  - Report function required conversion to Celsius before displaying
*/ 
