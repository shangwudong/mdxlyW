'use strict';

goog.provide('Blockly.Blocks.Microduino');

goog.require('Blockly.Blocks');

//var colorSet=230;
var colorSet='#6c91ac';

Blockly.Blocks.smartRF_Init_Send = {
  init: function() {
        var BAUD = [['9600 baud', '9600'],
                    ['38400 baud', '38400'],
                    ['57600 baud', '57600'],
                    ['115200 baud', '115200'],
                    ['300 baud', '300'],
                    ['1200 baud', '1200'],
                    ['2400 baud', '2400'],
                    ['4800 baud', '4800'],
                    ['19200 baud', '19200'],
                    ['230400 baud', '230400'],
                    ['250000 baud', '250000']];
        var FREQ = [['433', 'CFREQ_433'],
                    ['868', 'CFREQ_868'],
                    ['915', 'CFREQ_915']];

    this.setColour(colorSet);
    this.appendDummyInput("")
    	   .appendField(Blockly.smartRF)
        .appendField(new Blockly.FieldImage("../../media/Microduino/smartRF.jpg", 45, 32))
        .appendField(Blockly.smartRF_Init_Send)
        .appendField(Blockly.Zigbee_Baud)
        .appendField(new Blockly.FieldDropdown(BAUD), 'BAUD')
		    .appendField(Blockly.Frequency)
        .appendField(new Blockly.FieldDropdown(FREQ), 'FREQ')
        .appendField(Blockly.SENDADDR)
        .appendField(new Blockly.FieldTextInput('4'),'SenderADDRESS')
        .appendField(Blockly.RECADDR)
        .appendField(new Blockly.FieldTextInput('5'),'ReceiverADDRESS');
    //this.appendStatementInput('DO')
   	 this.setPreviousStatement(true, null);
   	 this.setNextStatement(true, null);
     this.setInputsInline(true);
    },
};

Blockly.Blocks.smartRF_Init_Read = {
  init: function() {
        var BAUD = [['9600 baud', '9600'],
                    ['38400 baud', '38400'],
                    ['57600 baud', '57600'],
                    ['115200 baud', '115200'],
                    ['300 baud', '300'],
                    ['1200 baud', '1200'],
                    ['2400 baud', '2400'],
                    ['4800 baud', '4800'],
                    ['19200 baud', '19200'],
                    ['230400 baud', '230400'],
                    ['250000 baud', '250000']];
        var FREQ = [['433', 'CFREQ_433'],
                    ['868', 'CFREQ_868'],
                    ['915', 'CFREQ_915']];
    this.setColour(colorSet);
    this.appendDummyInput("")
        .appendField(Blockly.smartRF)
        .appendField(new Blockly.FieldImage("../../media/Microduino/smartRF.jpg", 45, 32))
        .appendField(Blockly.smartRF_Init_Read)
        .appendField(Blockly.Zigbee_Baud)
        .appendField(new Blockly.FieldDropdown(BAUD), 'BAUD')
        .appendField(Blockly.Frequency)
        .appendField(new Blockly.FieldDropdown(FREQ), 'FREQ')
        .appendField(Blockly.RECADDR)
        .appendField(new Blockly.FieldTextInput('5'),'ReceiverADDRESS');
    //this.appendStatementInput('DO')
     this.setPreviousStatement(true, null);
     this.setNextStatement(true, null);
     this.setInputsInline(true);
    },
};

Blockly.Blocks.smartRF_Send = {
  init: function() {
    this.setColour(colorSet);
    this.appendDummyInput("")
      .appendField(Blockly.smartRF)
      .appendField(new Blockly.FieldImage("../../media/Microduino/smartRF.jpg", 45, 32))
      .appendField(Blockly.smartRF_Send)
      .appendField(new Blockly.FieldTextInput('data'),'smartRF_Data')
      .appendField(Blockly.smartRF_Send_Length)
      .appendField(new Blockly.FieldTextInput('length'),'smartRF_Data_Length');
    this.appendStatementInput('DO');
    //this.setOutput(true, Boolean);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
  }
};

Blockly.Blocks.smartRF_Read = {
  init: function() {
    this.setColour(colorSet);
    this.appendDummyInput("")
      .appendField(Blockly.smartRF)
      .appendField(new Blockly.FieldImage("../../media/Microduino/smartRF.jpg", 45, 32))
      .appendField(Blockly.smartRF_Read)
      .appendField(new Blockly.FieldTextInput('data'),'smartRF_REC_Data')
    //this.appendStatementInput('DO');
    //this.setOutput(true, Boolean);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
  }
};
