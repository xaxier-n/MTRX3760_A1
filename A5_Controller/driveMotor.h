#ifndef DRIVEMOTOR_H
#define DRIVEMOTOR_H

/*
A drive motor class header

This program defines a drive motor for use in a robot controller

Authored by Xavier Nicholas, 2026
*/

//---Includes--------------------------------------------------
#include "subsystem.h"

#include <iostream>
#include <string>

//---CDriveMotor-----------------------------------------------
/*
A CDriveMotor is a CSubsystem that has a velocity and is either braking or
accelerating. It functions through Run() and can report its current velocity.
*/
class CDriveMotor : public CSubsystem
{
    public:
        CDriveMotor( const std::string aLabel, int aVelocity = 0 );

        void Run();                     // run the system
        void Report();                  // report the current state
    private:
        int mVelocity;                  // velocity of the system in km/h
        const int MAX_VEL = 50;         // maximum velocity
        const int MIN_VEL = -30;        // minimum velocity
        const int ACCEL_AMT = 10;       // how much velocity changes by when run
        bool mBraking;                  // is the system braking
};

#endif