// CController.cpp -------------------------------------------------------------
//
// Implementation of the robot controller. The controller holds a set of
// subsystems as base-class pointers and, each cycle, runs and reports every
// one of them without knowing which concrete kind each subsystem is.
//
//--Includes-------------------------------------------------------------------
#include "CController.h"
#include <iostream>
#include <string>

// CController -------------------------------------------------------------------
// Creates an empty controller with no subsystems.
CController ::CController()
{
    mCount = 0;
    mCycle = 0;
}

// Registers a subsystem with the controller to run
void CController::AddSubsystem( CSubsystem* apSubsystem )
{
    if ( mCount < MAXSubsystems )
    {
        mSubsystems[mCount] = apSubsystem;
        ++mCount;
    }
}

// Runs a single cycle of all registered subsystems
// Each subsystem is run and then reports itself. The controller does not know
// what kind of subsystem it is running, only that it has a Run() and Report()
void CController::RunCycle()
{
    std::cout << "Controller cycle " << mCycle << std::endl;
    for ( int i = 0; i < mCount; ++i )
    {
        mSubsystems[i]->Run();
        mSubsystems[i]->Report();
    }
    ++mCycle;
}