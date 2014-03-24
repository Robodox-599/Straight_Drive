#include "Drive.h"

Drive::Drive(OperatorInterface *opInt)
{
	if(opInt) oi = opInt;
	
	linearVelocity = 0;
	turnSpeed = 0;
	
	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B);   
	shifter->Set(DoubleSolenoid::kReverse);
	
	frontLeftMotor = new Talon(1, DRIVE_FRONT_LEFT_MOTOR_CHANNEL);   
	rearLeftMotor = new Talon(1, DRIVE_REAR_LEFT_MOTOR_CHANNEL);   
	frontRightMotor = new Talon(1, DRIVE_FRONT_RIGHT_MOTOR_CHANNEL); 
	rearRightMotor = new Talon(1, DRIVE_REAR_RIGHT_MOTOR_CHANNEL);
	
	leftDriveEncoder = new Encoder(LEFT_DRIVE_ENCODER_CHANNEL_A, LEFT_DRIVE_ENCODER_CHANNEL_B);
	rightDriveEncoder = new Encoder(RIGHT_DRIVE_ENCODER_CHANNEL_A, RIGHT_DRIVE_ENCODER_CHANNEL_B);
	rpm = 0;
	init = true;
	timer = new Timer();
	timer->Start();
}

Drive::~Drive()
{
	delete shifter;
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
	delete leftDriveEncoder;
	delete rightDriveEncoder;
	delete timer;
	
	shifter = NULL;
	frontLeftMotor = NULL;
	rearLeftMotor = NULL;
	frontRightMotor = NULL;
	rearRightMotor = NULL;
	leftDriveEncoder = NULL;
	rightDriveEncoder = NULL;
	timer = NULL;
}

bool Drive::shift(UINT8 highButton, UINT8 lowButton)
{
	//static?
	bool lastGearWasHi = true;
	
	if(lowButton)
	{
		shifter->Set(DoubleSolenoid::kForward);
		lastGearWasHi = false;
	}
	else if(highButton)
	{
		shifter->Set(DoubleSolenoid::kReverse);
		lastGearWasHi = true;
	}
	
	return lastGearWasHi;	
}

void Drive::setLinVelocity(double linVal)
{
	if(linVal > DEADZONE)
	{
		linearVelocity = linVal;
	}
	else if(linVal < -DEADZONE)
	{
		linearVelocity = linVal;
	}
	else 
	{
		linearVelocity = 0; //NEUTRAL
	}	
}

double Drive::getLinVelocity()
{
	return linearVelocity;
}

void Drive::setTurnSpeed(double turn, bool turboButton)
{
	if((turn > DEADZONE && !turboButton) || (turn < -DEADZONE && !turboButton)) 
	{
		turnSpeed = turn * REDUCTION;
	}
	if(turn < DEADZONE && turn > -DEADZONE) 
	{
		turnSpeed = 0; //NEUTRAL
	}
	if((turn > DEADZONE && turboButton) || (turn < -DEADZONE && turboButton)) 
	{
		turnSpeed = turn;
	}
}

double Drive::getTurnSpeed()
{
	return turnSpeed;
}

double Drive::reduceTurn(double reduceBy)
{
	return turnSpeed * reduceBy;
}

void Drive::setLeftMotors(double velocity)
{
	frontLeftMotor->Set(-velocity, SYNC_STATE_OFF);
	rearLeftMotor->Set(-velocity, SYNC_STATE_OFF);
}

void Drive::setRightMotors(double velocity)
{
	frontRightMotor->Set(-velocity, SYNC_STATE_OFF);
	rearRightMotor->Set(-velocity, SYNC_STATE_OFF);
}

void Drive::drive()
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}

double Drive::getRPM()
{
	double initTime = 0;
	double deltaTime = 0;
	double initTicks = 0;
	double deltaTicks = 0;
	double ticksPerMinute = 0;
	
	if(init)
	{
		initTime = timer->Get();
		initTicks = leftDriveEncoder->Get();
		init = false;
	}
	
	deltaTime = timer->Get() - initTime;
	deltaTicks = leftDriveEncoder->Get() - initTicks;
	
	if(deltaTime == TIME_COMPARISON)
	{
		ticksPerMinute = deltaTicks * TIME_COMPARISON * MINUTE_CONVERSION;
		rpm = ticksPerMinute / TICKS_PER_ROTATION;
		init = true;
	}
	return rpm;
}


