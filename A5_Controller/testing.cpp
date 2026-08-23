/*
Testing functions implementation

This program implements testing functions for a robot controller's subsystems

Authored by Xavier Nicholas, 2026
*/

//---Includes-------------------------------------------------
#include "testing.h"
#include "driveMotor.h"
#include "objectSensor.h"

#include <iostream>
#include <string>

//---Implementation--------------------------------------------------------
// Test the CDriveMotor class
void TestCDriveMotor( int aLoops, int aStartingVel = 0 )
{
    std::cout << "Start TestCDriveMotor" << std::endl;

    // Initialise a CDriveMotor
    CDriveMotor motor("Motor1", aStartingVel);
    motor.Report();
    
    // Loop running the motor and reporting the velocity
    for (int i = 0; i < aLoops; i++) 
    {
        motor.Run();
        motor.Report();
    }
}

// Test the CObjectSensor class
void TestCObjectSensor( int aLoops )
{
    std::cout << "Start TestCObjectSensor" << std::endl;

    // Initialise a CObjectSensor
    CObjectSensor sensor("Sensor1");
    sensor.Report();
    
    // Loop running the sensor and reporting the state
    for (int i = 0; i < aLoops; i++) 
    {
        sensor.Run();
        sensor.Report();
    }
}

// Run all tests
void TestAll( int aLoops, int aStartingVel )
{
    TestCDriveMotor(aLoops, aStartingVel);
    TestCObjectSensor(aLoops);
}