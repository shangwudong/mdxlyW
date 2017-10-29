/***************************************
  LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)

  版权所有：
  @小崔  cuiwenjing@microduino.cc

  Sensor_Ultrasonic维基网址:
  https://wiki.microduino.cn/index.php/Sensor-Ultrasonic/zh

  本示例给出了使用超声波传感器测距离的方法
  并将测得的距离通过串口打印出来
  距离单位毫米（mm）
***************************************/

#include <Microduino_Ultrasonic.h>         //引用超声波库文件

Ultrasonic Ultrasonic1(ULTRASONIC_ADDR_1);//将Ultrasonic实例化

uint16_t Distance;   //定义变量

void setup() {
  Serial.begin(9600);                       // 串口初始化
  if (Ultrasonic1.begin()) {                //如果超声波初始化成功
    Serial.println("Ultrasonic is online");//串口打印信息
  }
  else {                                   //如果超声波初始化不成功
    Serial.println("error");              //串口打印信息
    while (1);                             //程序在此循环运行，即不再向下运行
  }
}

void loop() {
  Distance = Ultrasonic1.requstDistance(); //获取超声波测得的距离
  Serial.println(Distance);               //串口打印距离值
  delay(30);                              //延时30ms
}
