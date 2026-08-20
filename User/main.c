#include "stm32f10x.h"                  //Device header
#include "delay.h"                      //使用延时函数
#include "OLED.h"
#include "Servo.h"
#include "Serial.h"
#include <stdio.h>

float Angle1;
float Angle2;

int main(void)
{
	OLED_Init();
	Servo_Init();
	Serial_Init();
	
	OLED_ShowString(1,1,"Angle1:");
	OLED_ShowString(2,1,"Angle2:");

	while (1)
	{
		if(Serial_RxFlag)
		{
//			printf("RX=%s\r\n",Serial_RxPacket);
			Serial_SendString("Packet:");
			Serial_SendString(Serial_RxPacket);
			Serial_SendString("\r\n");
			
			sscanf(Serial_RxPacket,"%f,%f",&Angle1,&Angle2);
			
			if(Angle1<0) Angle1=0;
			if(Angle1>180) Angle1=180;
			
			if(Angle2<0) Angle2=0;
			if(Angle2>180) Angle2=180;
			
			Serial_RxFlag=0;
		}
		Servo1_SetAngle(Angle1);
		Servo2_SetAngle(Angle2);
		OLED_ShowNum(1,8,Angle1,3);
		OLED_ShowNum(2,8,Angle2,3);
	}
}
