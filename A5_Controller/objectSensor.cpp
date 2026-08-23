/*
Object sensor class implementation

This program implements an object sensor class for use in a robot controller

Authored by Xavier Nicholas, 2026
*/

//---Includes-------------------------------------------------
#include "objectSensor.h"

#include <iostream>
#include <string>

//---Implementation-------------------------------------------
//---Constructor----------------------------------------------
CObjectSensor::CObjectSensor( std::string aLabel )
    :   CSubsystem( aLabel ),
        mObjDist( 10 ),
        mDetected( false ),
        mStop( false )
{
}

// Run the object sensor (example functionality)
void CObjectSensor::Run()
{ // Detect an object and proceed to it, then manouevre around it

    if ( mStop )
    {
        if ( !mDetected ) { // stopped but no obstacle
            mStop = false;  // continue
            return;
        }
        else
        {
            return;
        }
    }

    if ( !mDetected )
    {
        // Detect a new object
        mDetected = true;
        mObjDist = 10;
    } 
    else
    {
        if ( mObjDist > 0 )
        {   // Decrement object distance
            mObjDist -= 1;
        }
        else
        {   // Stop at object
            mStop = true;
            mDetected = false;
        }
    }

    // Keep object distance positive
    if ( mObjDist < 0 ) mObjDist = 0;

}

// Report the current state of the sensor
void CObjectSensor::Report()
{
    if ( mStop )
    {
        std::cout << GetLabel() << ": Stopped at object. Attempting "
        << "to manouevre around..." << std::endl;
    }
    else if ( !mDetected )
    {
        std::cout << GetLabel() << ": No object detected." << std::endl;
    }
    else 
    {
        std::cout << GetLabel() << ": Object detected " << mObjDist << "m away."
            << std::endl;
    }
}