#ifndef SRV_MOTOR_INTERFACE_H_
#define SRV_MOTOR_INTERFACE_H_

#define Max_angle 180
#define Min_duty 5
#define Max_duty 10
#define Frequency 100

void SRV_Init(void);
void SRV_setAngle(uint8);

#endif /* SRV_MOTOR_INTERFACE_H_ */
