'use strict';

goog.provide('Blockly.Arduino.Microduino');

goog.require('Blockly.Arduino');




Blockly.Arduino.NumberTubePre = function() {

  var indexNum = Blockly.Arduino.valueToCode(this, 'indexNum', Blockly.Arduino.ORDER_ATOMIC);
  var upsideDown = this.getFieldValue('upsideDown');

  var NumberTubeInclude="";
  NumberTubeInclude+="#include <Microduino_Number.h>\n";
  Blockly.Arduino.definitions_['var_NumberTubeInclude'] = NumberTubeInclude;


  var NumberTubeVar='';
  NumberTubeVar+='//Core UART Port: [SoftSerial] [D2,D3]\n';
  NumberTubeVar+='#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)\n';
  NumberTubeVar+='SoftwareSerial mySerial(2, 3);\n';
  NumberTubeVar+='#define NumberSerial mySerial\n';
  NumberTubeVar+='#endif\n';
  NumberTubeVar+='//Core+ UART Port: [Serial1] [D2,D3]\n';
  NumberTubeVar+='#if defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)\n';
  NumberTubeVar+='#define NumberSerial Serial1\n';
  NumberTubeVar+='#endif\n';
  NumberTubeVar+='\n';
  NumberTubeVar+='Number LED('+indexNum+', &NumberSerial);\n';
  Blockly.Arduino.definitions_['var_NumberTubeVar'] = NumberTubeVar;

  var NumberTubeSetup='';
  NumberTubeSetup+='LED.begin();\n';
  NumberTubeSetup+='LED.direction('+upsideDown+');\n';
  Blockly.Arduino.setups_['setup_NumberTubeSetup'] = NumberTubeSetup;


  var code='';

  return code;

};



Blockly.Arduino.NumberTubeSet = function() {

var index = Blockly.Arduino.valueToCode(this, 'index', Blockly.Arduino.ORDER_ATOMIC);
var number = Blockly.Arduino.valueToCode(this, 'number', Blockly.Arduino.ORDER_ATOMIC);
var light = Blockly.Arduino.valueToCode(this, 'light', Blockly.Arduino.ORDER_ATOMIC);
var pointHas = this.getFieldValue('pointHas');

  var code='';
  code+='LED.setNumber('+index+', '+number+', '+light+');\n';
  code+='LED.setPoint('+index+', '+pointHas+');\n';
  code+='LED.show();\n';
  return code;

};


Blockly.Arduino.NumberTubeShow = function() {
  var code='';
  code+='LED.show();\n';
  return code;
};


