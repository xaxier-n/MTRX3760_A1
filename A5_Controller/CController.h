// CController.h -------------------------------------------------------------
#ifndef CCONTROLLER_H
#define CCONTROLLER_H
/*
A controller class header
 
This program defines a controller for running a robot's subsystems
 
Authored by 530318347, 2026
*/
#include "subsystem.h" 

//---CController-----------------------------------------------
/*
A CController runs a set of CSubsystem objects. It stores each one as a
base class pointer, so it does not need to know their concrete type. Each
cycle it runs and reports every registered subsystem.
*/
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
    //The maximum number of subsystems the controller can hold
    static const int MAXSubsystems = 10;
    //The subsystems as base pointers
    CSubsystem* mSubsystems[MAXSubsystems];
    int mCount;
    int mCycle;

};

#endif



