'use strict';

goog.provide('Blockly.Arduino.Microduino');

goog.require('Blockly.Arduino');

Blockly.Arduino.MDSerialMotionPre = function() {

  var SerialMotionInclude="";
  SerialMotionInclude+="#include <Sensor_Motion.h>\n";
  Blockly.Arduino.definitions_['var_SerialMotionInclude'] = SerialMotionInclude;

  var SerialMotionVar='';
  SerialMotionVar+='//Core UART Port: [SoftSerial] [D2,D3]\n';
  SerialMotionVar+='#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)\n';
  SerialMotionVar+='SoftwareSerial mySerial(2, 3);\n';
  SerialMotionVar+='#define MotionSerial mySerial\n';
  SerialMotionVar+='#endif\n';
  SerialMotionVar+='//Core+ UART Port: [Serial1] [D2,D3]\n';
  SerialMotionVar+='#if defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)\n';
  SerialMotionVar+='#define MotionSerial Serial1\n';
  SerialMotionVar+='#endif\n';
  SerialMotionVar+='\n';
  SerialMotionVar+='float s_ypr[3];\n';
  SerialMotionVar+='sensorMotion motion(&MotionSerial);\n';
  Blockly.Arduino.definitions_['var_SerialMotionVar'] = SerialMotionVar;

  var SerialMotionSetup='';
  SerialMotionSetup+='motion.begin();\n';
  Blockly.Arduino.setups_['setup_SerialMotionSetup'] = SerialMotionSetup;

  var code='motion.getData(MOTION_3, s_ypr);\n';

  return code;

};


Blockly.Arduino.MDSerialMotionGet = function() {
  var s_ypr = this.getFieldValue('s_ypr');
  var code='s_ypr['+s_ypr+']';
  return [code, Blockly.Arduino.ORDER_ATOMIC];

};

