/*
Drive motor class implementation

This program implements a drive motor class for use in a robot controller

Authored by Xavier Nicholas, 2026
*/

//---Includes-------------------------------------------------
#include "driveMotor.h"

#include <iostream>
#include <string>
#include <cmath>

//---Implementation-------------------------------------------
//---Constructor----------------------------------------------
CDriveMotor::CDriveMotor( const std::string aLabel, int aVelocity )
    :   CSubsystem( aLabel ),
        mBraking( false )
{
    if ( aVelocity > MAX_VEL)
    {
        mVelocity = MAX_VEL;
    }
    else if ( aVelocity < MIN_VEL )
    {
        mVelocity = MIN_VEL;
    }
    else
    {
        mVelocity = aVelocity;
    }
}

//---Report current velocity----------------------------------
void CDriveMotor::Report()
{
    // Get a string for the direction
    std::string drivingDirection = (mVelocity < 0)?  "backwards" : "forwards";

    // Report the speed and direction
    std::cout << "DriveMotor " << GetLabel() << " is driving at " 
        << std::to_string(std::abs(mVelocity)) << "km/h " << drivingDirection
        << "." << std::endl;
}

//---Run the drive motor (example functionality)--------------
void CDriveMotor::Run()
{
    // Main functionality
    // Accelerate to max velocity then decelerate to min velocity
    // Switches at each limit

    if ( mVelocity >= MAX_VEL )
    {   // Switch acceleration direction
        mVelocity = MAX_VEL - ACCEL_AMT;
        mBraking = true;
    }
    else if ( mVelocity <= MIN_VEL )
    {   // Switch acceleration direction
        mVelocity = MIN_VEL + ACCEL_AMT;
        mBraking = false;
    }
    else
    {   // Add or subtract acceleration amount according to mBraking
        mVelocity = (mBraking) ? (mVelocity - ACCEL_AMT) : (mVelocity + ACCEL_AMT);
    }

    //  Keep velocity within limits
    if (mVelocity >= MAX_VEL)
    {
        mVelocity = MAX_VEL;
    }
    if (mVelocity <= MIN_VEL)
    {
        mVelocity = MIN_VEL;
    }
    
}