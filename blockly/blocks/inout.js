'use strict';

goog.provide('Blockly.Blocks.base');

goog.require('Blockly.Blocks');

var setColor='#d2c078';

Blockly.Blocks['inout_highlow'] = {
   init: function() {
    this.setColour(setColor);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_HIGH, "HIGH"], [Blockly.MIXLY_LOW, "LOW"]]), 'BOOL')
    this.setOutput(true, Boolean);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_HIGHLOW);
  }
};

Blockly.Blocks.inout_digital_write = {
  init: function() {
    this.setColour(setColor);
    this.appendDummyInput("")
	    .appendField(Blockly.MIXLY_DIGITALWRITE_PIN)
	    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
      	.appendField(Blockly.MIXLY_STAT)
      	.appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_HIGH, "HIGH"], [Blockly.MIXLY_LOW, "LOW"]]), "STAT");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.LANG_INOUT_DIGITAL_WRITE_TOOLTIP);
  }
};

Blockly.Blocks.inout_digital_write2 = {
  init: function() {
    this.setColour(setColor);
    this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_DIGITALWRITE_PIN)
        .setCheck(Number);
    this.appendValueInput("STAT")
        .appendField(Blockly.MIXLY_STAT)
        .setCheck([Number,Boolean]);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setTooltip(Blockly.LANG_INOUT_DIGITAL_WRITE_TOOLTIP);
  }
};

Blockly.Blocks.inout_digital_read = {
  init: function() {
    this.setColour(setColor);
    this.appendDummyInput("")
	      .appendField(Blockly.MIXLY_DIGITALREAD_PIN)
	      .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN");
    this.setOutput(true, [Boolean,Number]);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_DIGITAL_READ);
  }
};

Blockly.Blocks.inout_digital_read2 = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_DIGITALREAD_PIN)
        .setCheck(Number);
    this.setInputsInline(true);
    this.setOutput(true, [Boolean,Number]);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_DIGITAL_READ);
  }
};

Blockly.Blocks.inout_analog_write = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_ANALOGWRITE_PIN)
        .setCheck(Number);
    this.appendValueInput("NUM", Number)
        .appendField(Blockly.MIXLY_VALUE2)
        .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_ANALOG_WRITE);
  }
};

Blockly.Blocks.inout_analog_read = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_ANALOGREAD_PIN)
        .setCheck(Number);
    this.setOutput(true, Number);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_ANALOG_READ);
  }
};

Blockly.Blocks.inout_buildin_led = {
   init: function() {
     this.setColour(setColor);
     this.appendDummyInput("")
	       .appendField(Blockly.MIXLY_BUILDIN_LED)
	       .appendField(Blockly.MIXLY_STAT)
	       .appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_ON, "HIGH"], [Blockly.MIXLY_OFF, "LOW"]]), "STAT");
     this.setPreviousStatement(true, null);
     this.setNextStatement(true, null);
     this.setTooltip('light or off the build-in LED');
   }
};

Blockly.Blocks.controls_attachInterrupt = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_ATTACHINTERRUPT_PIN)
        .setCheck(Number);
    this.appendDummyInput("")
      	.appendField(Blockly.MIXLY_MODE)
      	.appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_RISING, "RISING"], [Blockly.MIXLY_FALLING, "FALLING"], [Blockly.MIXLY_CHANGE, "CHANGE"]]), "mode");
	this.appendStatementInput('DO')
        .appendField(Blockly.MIXLY_DO);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_ATTACHINTERRUPT);
  }/*,
  onchange: function() {
	  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
	  var interrupt_pin=digitalPinToInterrupt(dropdown_pin).toString();
	  if(interrupt_pin=='NOT_AN_INTERRUPT'){
		  this.setWarningText(Blockly.MIXLY_WARNING_INTERRUPT);
	  }else{
		  this.setWarningText(null);
	  }
  }*/
};

Blockly.Blocks.controls_detachInterrupt = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_DETACHINTERRUPT_PIN)
        .setCheck(Number);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_INOUT_DETACHINTERRUPT);
  }/*,
  onchange: function() {
	  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
	  var interrupt_pin=digitalPinToInterrupt(dropdown_pin).toString();
	  if(interrupt_pin=='NOT_AN_INTERRUPT'){
		  this.setWarningText(Blockly.MIXLY_WARNING_INTERRUPT);
	  }else{
		  this.setWarningText(null);
	  }
  }*/
};

Blockly.Blocks.inout_pulseIn = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_PULSEIN)
        .setCheck(Number);
    this.appendDummyInput("")
      	.appendField(Blockly.MIXLY_PULSEIN_STAT)
      	.appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_HIGH, "HIGH"], [Blockly.MIXLY_LOW, "LOW"]]), "STAT");
    this.setOutput(true, Number);
  }
};

Blockly.Blocks.inout_pulseIn2 = {
  init: function() {
    this.setColour(setColor);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_PULSEIN)
        .setCheck(Number);
    this.appendDummyInput("")
      	.appendField(Blockly.MIXLY_PULSEIN_STAT)
      	.appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_HIGH, "HIGH"], [Blockly.MIXLY_LOW, "LOW"]]), "STAT");
	this.appendValueInput("TIMEOUT", Number)
        .appendField(Blockly.MIXLY_PULSEIN_TIMEOUT)
        .setCheck(Number);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

Blockly.Blocks.inout_shiftout = {
  init: function() {
    this.setColour(setColor);
    this.appendDummyInput("")
        .appendField("ShiftOut");
	this.appendValueInput("PIN1", Number)
        .appendField(Blockly.MIXLY_DATAPIN)
        .setCheck(Number);
	this.appendValueInput("PIN2", Number)
        .appendField(Blockly.MIXLY_CLOCKPIN)
        .setCheck(Number);
	this.appendDummyInput("")
        .appendField(Blockly.MIXLY_BITORDER)
		.appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_MSBFIRST, "MSBFIRST"], [Blockly.MIXLY_LSBFIRST, "LSBFIRST"]]), "ORDER");
    this.appendValueInput("DATA", Number)
        .appendField(Blockly.MIXLY_DATA)
        .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};