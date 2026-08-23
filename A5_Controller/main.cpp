#include <iostream>
#include <string>
#include <cmath>

//---Subsystem definition-----------------------------------
class CSubsystem
{
    public:
        CSubsystem( const std::string aLabel );
        virtual ~CSubsystem();
        virtual void Run() = 0;
        virtual void Report() = 0;
        std::string GetLabel();

    private:
        std::string mLabel;
};

//---DriveMotor definition----------------------------------
class CDriveMotor : public CSubsystem
{
    public:
        CDriveMotor( const std::string aLabel, int aVelocity = 0 );
        virtual ~CDriveMotor();
        void Run();
        void Report();
    private:
        int mVelocity;
        const int MAX_VEL = 50;
        const int MIN_VEL = -30;
        const int ACCEL_AMT = 10;
        bool mBraking;
};

//---ObjectSensor definition--------------------------------
class CObjectSensor : public CSubsystem
{
    public:
        CObjectSensor( const std::string aLabel );
        virtual ~CObjectSensor();
        void Run();
        void Report();
    private:
        int mObjDist;
        bool mDetected;
        bool mStop;
};

/*
If not detected, switch to detected
If detected, check distance
    If distance > 0, subtract 1
    If distance <= 0, set to 0 and set mStop
*/

//---Subsystem implementation-------------------------------
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

//---DriveMotor implementation------------------------------
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



CDriveMotor::~CDriveMotor()
{
}

void CDriveMotor::Report()
{
    std::string drivingDirection = (mVelocity < 0)?  "backwards" : "forwards";
    std::cout << "DriveMotor " << GetLabel() << " is driving at " 
        << std::to_string(std::abs(mVelocity)) << "km/h " << drivingDirection
        << "." << std::endl;
}

void CDriveMotor::Run()
{
    if ( mVelocity >= MAX_VEL )
    {
        mVelocity = MAX_VEL - ACCEL_AMT;
        mBraking = true;
    }
    else if ( mVelocity <= MIN_VEL )
    {
        mVelocity = MIN_VEL + ACCEL_AMT;
        mBraking = false;
    }
    else
    {
        mVelocity = (mBraking) ? (mVelocity - ACCEL_AMT) : (mVelocity + ACCEL_AMT);
    }

    if (mVelocity >= MAX_VEL)
    {
        mVelocity = MAX_VEL;
    }
    if (mVelocity <= MIN_VEL)
    {
        mVelocity = MIN_VEL;
    }
    
}

//---ObjectSensor definition
CObjectSensor::CObjectSensor( std::string aLabel )
    :   CSubsystem( aLabel ),
        mObjDist( 10 ),
        mDetected( false ),
        mStop( false )
{

}

CObjectSensor::~CObjectSensor()
{

}

void CObjectSensor::Run() 
{
/*
If stop
If not detected, switch to detected
If detected, check distance
    If distance > 0, subtract 1
    If distance <= 0, set to 0 and set mStop
*/

    if ( mStop )
    {
        if ( !mDetected ) {
            mStop = false;
            return;
        }
        else 
        {
            return;
        }
    }

    if ( !mDetected )
    {
        mDetected = true;
        mObjDist = 10;
    } 
    else
    {
        if ( mObjDist > 0 )
        {
            mObjDist -= 1;
        }
        else
        {
            mStop = true;
            mDetected = false;
        }
    }

    if ( mObjDist < 0 ) mObjDist = 0;

}

void CObjectSensor::Report()
{
    if ( mStop )
    {
        std::cout << GetLabel() << ": Stopped at object. Attempting "
        << "to manouevre around..." << std::endl;
    }
    else if ( !mDetected )
    {
        std::cout << GetLabel() << ": No object detected." << std::endl;
    }
    else 
    {
        std::cout << GetLabel() << ": Object detected " << mObjDist << "m away."
            << std::endl;
    }
}

//---Testing definitions-----------------------------------------------------------
void TestCDriveMotor(int aLoops, int aStartingVel );
void TestCObjectSensor(int aLoops);

//---Main--------------------------------------------------------------------------
int main()
{
    int testLoops = 15;
    // int startingVelocity = 55;
    // TestCDriveMotor(testLoops, startingVelocity);
    TestCObjectSensor(testLoops);
    
    return 0;
}

//---Testing implementation--------------------------------------------------------
void TestCDriveMotor(int aLoops, int aStartingVel = 0)
{
    std::cout << "Start TestCDriveMotor" << std::endl;

    CDriveMotor motor("Motor1", aStartingVel);
    motor.Report();
    
    for (int i = 0; i < aLoops; i++) 
    {
        motor.Run();
        motor.Report();
    }
}

void TestCObjectSensor(int aLoops)
{
    std::cout << "Start TestCObjectSensor" << std::endl;

    CObjectSensor sensor("Sensor1");
    sensor.Report();
    
    for (int i = 0; i < aLoops; i++) 
    {
        sensor.Run();
        sensor.Report();
    }
}