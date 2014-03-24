#include "WPILib.h"
#include "Drive.h"
#include "OperatorInterface.h"
#include "Macros.h"

class Main : public IterativeRobot
{
public:
	
	Drive *drive;
	OperatorInterface *oi;

	Main()
	{
		drive = new Drive();
		oi = new OperatorInterface();
		
		oi->dashboard->init();
	}

	void RobotInit()
	{
	
	}
	
	void DisabledInit()
	{
	
	}
	
	void AutonomousInit()
	{
	
	}
	
	void TeleopInit()
	{

	}

	void TestInit()
	{
		
	}
	
	void DisabledPeriodic()
	{
	
	}
	
	void AutonomousPeriodic()
	{
	
	}
	
	void TeleopPeriodic()
	{

	}
	
};

START_ROBOT_CLASS(Main);
