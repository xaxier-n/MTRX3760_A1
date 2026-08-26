#ifndef TESTING_H
#define TESTING_H

/*
A testing functions header

This program defines testing functions for a robot controller's subsystems

Authored by Xavier Nicholas, 2026
*/

//---Includes----------------------------------------------------
#include <iostream>
#include <string>
#include <cmath>

//---Definitions-------------------------------------------------

void TestCDriveMotor( int aLoops, int aStartingVel );
/*
Tests the CDriveMotor class. Creates a CDriveMotor and reports the initial
state, then executes the Run() function the specified number of times,
reporting the state after each.

Arguments
    - aLoops: how many times to run and report
    - aStartingVel: the starting velocity in km/h (limited to -30 to 50)
*/

void TestCObjectSensor( int aLoops );
/*
Tests the CObjectSensor class. Creates a CObjectSensor and reports the initial
state, then executes the Run() function the specified number of times,
reporting the state after each.

Arguments
    - aLoops: how many times to run and report
*/

void TestAll( int aLoops, int aStartingVel );
/*
Tests both classes using the above functions.

Arguments
    - aLoops: how many times to run and report
    - aStartingVel: the drive motor's starting velocity in km/h 
        (limited to -30 to 50)
*/
void TestController( int aCycles, int aStartingVel );
/*
Tests the CController class. Creates a CController and registers a
CDriveMotor and a CObjectSensor with it (two different kinds of subsystem,
each with its own internal state), then runs the specified number of
cycles. Each cycle the controller runs and reports every registered
subsystem polymorphically, without knowing their concrete types.
 
Arguments
    - aCycles: how many cycles to run (at least 3 to see changing state)
    - aStartingVel: the drive motor's starting velocity in km/h
        (limited to -30 to 50)
*/

#endif