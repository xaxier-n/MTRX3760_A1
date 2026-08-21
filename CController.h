// CController.h -------------------------------------------------------------
#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include "Subsystem.h" 

// The maximum number of subsystems that can be registered with the controller
const int MAXSubsystems = 10;

class CController
{
    public:
    //Creates an empty controller with no subsystems.
    CController();
    
    //Registers a subsystem with the controller to run
    void AddSubsystem( CSubsystem* apSubsystem );

    //Runs a single cycle of all registered subsystems
    void RunCycle();

    private:
    //The subsystems as base pointers
    CSubsystem* mSubsystems[MAXSubsystems];
    int mCount;
    int mCycle;

}

#endif



