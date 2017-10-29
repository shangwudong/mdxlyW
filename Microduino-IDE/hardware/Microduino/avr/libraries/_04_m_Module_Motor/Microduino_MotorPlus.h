/*********************************************************
//  LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)

//  版权所有：
//  @小崔  cuiwenjing@microduino.cc

// 支持Microduino_MotorPlus

// Microduino wiki:
// http://wiki.microduino.cn

// E-mail:
// Wenjing Cui
// cuiwenjing@microduino.cc

// Weibo:
// @路蝶-6

//日期：2017.06
*********************************************************/

#ifndef _MICRODUINO_MOTOR_PLUSE_H_
#define _MICRODUINO_MOTOR_PLUSE_H_

#include <Arduino.h>
#include <Wire.h>

#define MOTOR_ADDR1  0x70
#define MOTOR_ADDR2  0x71
#define MOTOR_ADDR3  0x72
#define MOTOR_ADDR4  0x73

#define BIT_14  14  //速度设置值二进制位数
#define BIT_13  13
#define BIT_12  12
#define BIT_11  11
#define BIT_10  10
#define BIT_9  	9
#define BIT_8  	8

#define FREE  	0   //释放
#define BRAKE  	20000  //刹车
#define SLEEP  -20000   //休眠

#define ADDR16_MOTOR1   0x00
#define ADDR16_MOTOR2   0x02

class MotorPlus {

  public:
    MotorPlus(uint8_t _addr=0X73); 
    bool begin(uint8_t _bit = BIT_8);
    bool setSpeed1(int16_t _speed);
    bool setSpeed2(int16_t _speed);
    bool setSpeed(int16_t _speed1, int16_t _speed2);

  private:  
	uint8_t devAddr;
    uint8_t multiple;
	
    bool write16(uint8_t writeAddr, uint16_t *data, uint8_t len);
	bool requestData();
};

#endif /* LINERCCDLIB_LINERCCD_H_ */

