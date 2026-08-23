/*
Subsystem class implementation

This program implements a subsystem class for use in a robot controller

Authored by Xavier Nicholas, 2026
*/

//--Includes--------------------------------------------------
#include "subsystem.h"

#include <iostream>
#include <string>

//---Implementation---------------------------------
CSubsystem::CSubsystem ( const std::string aLabel )
    : mLabel( aLabel )
{
    std::cout << "Ctor " << mLabel << std::endl;
}

CSubsystem::~CSubsystem()
{
    std::cout << "Dtor " << mLabel << std::endl;
}

std::string CSubsystem::GetLabel()
{
    return mLabel;
}
