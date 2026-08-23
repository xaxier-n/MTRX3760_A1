#ifndef OBJECTSENSOR_H
#define OBJECTSENSOR_H

/*
An object sensor class header

This program defines an object sensor for use in a robot controller

Authored by Xavier Nicholas, 2026
*/

//---Includes----------------------------------------------------
#include "subsystem.h"

#include <iostream>
#include <string>

//---CObjectSensor-----------------------------------------------
/*
A CObjectSensor is a CSubsystem that detects an object and its distance away.
It will set a stop flag when the object is reached. It functions through Run() 
and can report its current state.
*/
class CObjectSensor : public CSubsystem
{
    public:
        CObjectSensor( const std::string aLabel );
        void Run();                 // run the system
        void Report();              // report current state
    private:
        int mObjDist;               // distance from object in metres
        bool mDetected;             // whether an object is detected
        bool mStop;                 // detected object has been reached
};

#endif