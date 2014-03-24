#ifndef DRIVE_H
#define DRIVE_H
#include "WPILib.h"
#include "Macros.h"
#include "OperatorInterface.h"

class Drive
{
public:
	Drive(OperatorInterface *opInt = NULL);
	~Drive();
	
	bool shift(UINT8 highButton, UINT8 lowButton);
	
	void drive();
	
	void setLinVelocity(double linVal);
	double getLinVelocity();
	
	void setTurnSpeed(double turn, bool turboButton);		
	double getTurnSpeed();	
	
	double reduceTurn(double reduceBy);
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);
	
	double getRPM();
	
private:
	OperatorInterface *oi;
	
	Talon *frontLeftMotor;
	Talon *rearLeftMotor;
	Talon *frontRightMotor;
	Talon *rearRightMotor;
	DoubleSolenoid *shifter;	
	double linearVelocity; 
	double turnSpeed; 
	double leftCmd;
	double rightCmd;
	
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	double rpm;
	bool init;
	Timer *timer;
};
#endif
