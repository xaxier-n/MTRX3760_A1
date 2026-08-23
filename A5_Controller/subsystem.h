#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H
/*
A subsystem class header

This program defines a subsystem for use in a robot controller

Authored by Xavier Nicholas, 2026
*/

//--Includes--------------------------------------------------
#include <iostream>
#include <string>

//---CSubsystem-----------------------------------------------
/*
A CSubsystem is a system with a label that has functionality 
through Run() and can report its current state. GetLabel()
returns the subsystem's label.
*/
class CSubsystem
{
    public:
        CSubsystem( const std::string aLabel );
        virtual ~CSubsystem();

        virtual void Run() = 0;         // run the subsystem
        virtual void Report() = 0;      // report current state
        std::string GetLabel();         // return the label

    private:
        std::string mLabel;
};

#endif