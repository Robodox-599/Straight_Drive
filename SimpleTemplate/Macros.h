#ifndef MACROS_H
#define MACROS_H

#define PNEUMATICS_24V_SLOT						(1)

	//Digital Sidecar
#define DRIVE_FRONT_LEFT_MOTOR_CHANNEL          (1)
#define DRIVE_REAR_LEFT_MOTOR_CHANNEL           (2)
#define DRIVE_FRONT_RIGHT_MOTOR_CHANNEL         (3)
#define DRIVE_REAR_RIGHT_MOTOR_CHANNEL          (4)

	//PWM
#define SHIFTER_SOLENOID_CHANNEL_A				(1)
#define SHIFTER_SOLENOID_CHANNEL_B				(2)
#define LEFT_DRIVE_ENCODER_CHANNEL_A			(3)
#define LEFT_DRIVE_ENCODER_CHANNEL_B			(4)
#define RIGHT_DRIVE_ENCODER_CHANNEL_A			(5)
#define RIGHT_DRIVE_ENCODER_CHANNEL_B			(6)

#define DEADZONE								(10)
#define REDUCTION								(.5)
#define SYNC_STATE_OFF							(0)
	//RPM
#define TIME_COMPARISON							(.25)
#define MINUTE_CONVERSION						(240)
#define TICKS_PER_ROTATION						(250)


#endif
