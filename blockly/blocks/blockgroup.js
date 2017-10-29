'use strict';

goog.provide('Blockly.Blocks.blockgroup');

goog.require('Blockly.Blocks');

Blockly.Blocks.blockgroup.HUE = '#b1bd65';
Blockly.Blocks.blockgroup.HUE1 = '#efa752';
Blockly.Blocks.blockgroup.HUE2 = '#70bd94';
Blockly.Blocks.blockgroup.HUE3 = '6c91ac';

Blockly.Blocks['serial_begin'] = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
    this.appendValueInput("CONTENT", Number)
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
		.appendField(Blockly.MIXLY_SERIAL_BEGIN)
		.setCheck(Number);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

Blockly.Blocks['serial_write'] = {
    init: function () {
        this.setColour(Blockly.Blocks.blockgroup.HUE);
        this.appendValueInput("CONTENT", String)
            .appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
            .appendField(Blockly.MIXLY_SERIAL_WRITE);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip(Blockly.Msg.TEXT_WRITE_TOOLTIP);
    }
};

Blockly.Blocks['serial_print'] = {
  init: function() {
   this.setColour(Blockly.Blocks.blockgroup.HUE);
    this.appendValueInput("CONTENT", String)
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_PRINT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.Msg.TEXT_PRINT_TOOLTIP);
  }
};

Blockly.Blocks['serial_println'] = {
   init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
    this.appendValueInput("CONTENT", String)
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_PRINTLN);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.Msg.TEXT_PRINT_TOOLTIP);
  }
};
//��ӡ16������
Blockly.Blocks['serial_print_hex'] = {
   init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
    this.appendValueInput("CONTENT", Number)
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_PRINT_HEX)
        .setCheck(Number);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
	this.setTooltip(Blockly.Msg.TEXT_PRINT_HEX_TOOLTIP);
  }
};

Blockly.Blocks['serial_available'] = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
	this.appendDummyInput()
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_AVAILABLE);
	this.setOutput(true, Boolean);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERIAL_AVAILABLE);
  }
};

Blockly.Blocks['serial_readstr'] = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
	this.appendDummyInput()
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_READSTR);
	this.setOutput(true, String);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERIAL_READ_STR);
  }
};

Blockly.Blocks['serial_readstr_until'] = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
	this.appendValueInput("CONTENT", Number)
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_READSTR_UNTIL)
		.setCheck(Number);
	this.setOutput(true, String);
  }
};

Blockly.Blocks['serial_parseInt_Float'] = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE);
	this.appendDummyInput()
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        //.appendField(Blockly.MIXLY_SERIAL_READ)
		.appendField(new Blockly.FieldDropdown([["read", "read"],["peek", "peek"],["parseInt", "parseInt"], ["parseFloat", "parseFloat"]]), "STAT");
	this.setOutput(true, Number);
	var thisBlock = this;
    this.setTooltip(function() {
      var op = thisBlock.getFieldValue('STAT');
      var TOOLTIPS = {
        'parseInt': Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERIAL_READ_INT,
        'parseFloat': Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERIAL_READ_FLOAT
      };
      return TOOLTIPS[op];
    });
  }
};

Blockly.Blocks['serial_flush'] = {
  init: function() {
   this.setColour(Blockly.Blocks.blockgroup.HUE);
    this.appendDummyInput()
		.appendField(new Blockly.FieldDropdown(profile.default.serial_select), "serial_select")
        .appendField(Blockly.MIXLY_SERIAL_FLUSH);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

Blockly.Blocks['serial_softserial'] = {
  init: function() {
   this.setColour(Blockly.Blocks.blockgroup.HUE);
   this.appendValueInput("TX", Number)
       .appendField(Blockly.MIXLY_SETUP)
	   .appendField("SoftwareSerial")
	   .appendField("TX#")
       .setCheck(Number)
	   .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("RX", Number)
	   .appendField("RX#")
       .setCheck(Number)
	   .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
	this.setInputsInline(true);
  }
};

//�������ģ��
Blockly.Blocks.ir_recv = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendValueInput("PIN", Number)
		.appendField(new Blockly.FieldTextInput('ir_item'), 'VAR')
        .appendField(Blockly.MIXLY_IR_RECEIVE)
        .setCheck(Number);
	this.appendStatementInput('DO')
        .appendField(Blockly.MIXLY_IR_RECEIVE_YES);
	this.appendStatementInput('DO2')
        .appendField(Blockly.MIXLY_IR_RECEIVE_NO);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_IR_RECIEVE_TOOLTIP);
  },
  getVars: function() {
    return [this.getFieldValue('VAR')];
  },
  renameVar: function(oldName, newName) {
    if (Blockly.Names.equals(oldName, this.getFieldValue('VAR'))) {
      this.setTitleValue(newName, 'VAR');
    }
  }
};
//���ⷢ��ģ�飨NEC��
Blockly.Blocks.ir_send_nec={
	init:function(){
		var TYPE = [['NEC', 'NEC'],['Whynter', 'Whynter'],['Sony', 'Sony'],['RC5', 'RC5'],['RC6', 'RC6'],['DISH', 'DISH'],['SharpRaw', 'SharpRaw'],['SAMSUNG', 'SAMSUNG']];
		this.setColour(Blockly.Blocks.blockgroup.HUE3);
		this.appendDummyInput("")
			.appendField(Blockly.MIXLY_IR_SEND_NEC1)
			.appendField(new Blockly.FieldDropdown(TYPE), 'TYPE')
			.appendField(Blockly.MIXLY_IR_SEND_NEC2)
			.appendField(new Blockly.FieldDropdown([["3", "3"]]), "PIN");
		this.appendValueInput('data')
			.setCheck(Number)
			.appendField(' '+Blockly.MIXLY_DATA);
		this.appendValueInput('bits')
			.setCheck(Number)
			.appendField(' '+Blockly.MIXLY_BITS);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setInputsInline(true);
		this.setTooltip(Blockly.MIXLY_IR_SEND_NEC_TOOLTIP);
	}
}

//�������ʹ��
Blockly.Blocks.ir_recv_enable = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_IR_RECEIVE_ENABLE);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
  }
};

//�������ģ��(raw)
Blockly.Blocks.ir_recv_raw = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_IR_RECEIVE_RAW)
        .setCheck(Number);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_IR_RECIEVE_RAW_TOOLTIP);
  }
};

//���ⷢ��ģ��(raw)
Blockly.Blocks.ir_send_raw = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendDummyInput("")
	    .appendField(Blockly.MIXLY_IR_SEND_RAW)
	    .appendField(new Blockly.FieldDropdown([["3", "3"]]), "PIN");
    this.appendDummyInput("")
        .appendField(' '+Blockly.MIXLY_LIST_NAME)
        .appendField(new Blockly.FieldTextInput('0,0,0'), 'TEXT');
	this.appendValueInput('length')
        .setCheck(Number)
        .appendField(' '+Blockly.MIXLY_LIST_LENGTH);
	this.appendValueInput('freq')
        .setCheck(Number)
        .appendField(' '+Blockly.MIXLY_FREQUENCY);
	this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_IR_SEND_RAW_TOOLTIP);
  }
};

//I2Cͨ��
Blockly.Blocks.i2c_master_writer = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendValueInput('device')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_I2C_MASTER_WRITE);
	this.appendValueInput('value')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MIXLY_I2C_VALUE);
	this.setPreviousStatement(true);
    this.setNextStatement(true);
  }
};
Blockly.Blocks.i2c_master_reader = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendValueInput('device')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_I2C_MASTER_READ);
	this.appendValueInput('bytes')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MIXLY_I2C_BYTES);
	this.setPreviousStatement(true);
    this.setNextStatement(true);
  }
};
Blockly.Blocks.i2c_master_reader2 = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendDummyInput()
        .appendField(Blockly.MIXLY_I2C_MASTER_READ2);
	this.setOutput(true, Number);
  }
};
Blockly.Blocks.i2c_available = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendDummyInput()
        .appendField(Blockly.MIXLY_I2C_AVAILABLE);
	this.setOutput(true, Boolean);
  }
};

//SPI
Blockly.Blocks.spi_transfer={
	init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE3);
	this.appendValueInput('pin')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.TO_SPI_SLAVE_PIN);
	this.appendValueInput('value')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.SPI_TRANSFER);
	this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setInputsInline(true);
  }
}

//���������
Blockly.Blocks.chaoshengbo={
	init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE1);
	this.appendDummyInput("")
	    .appendField(Blockly.MIXLY_CHAOSHENGBO)
	    .appendField('Trig#')
	    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN1")
		.appendField(' Echo#')
	    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN2");
	this.setOutput(true, Number);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_CHAOSHENGBO);
  }
};

Blockly.Blocks.chaoshengbo2={
	init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE1);
	this.appendDummyInput("")
	    .appendField(Blockly.MIXLY_CHAOSHENGBO);
	this.appendValueInput("PIN1", Number)
        .appendField('Trig#')
        .setCheck(Number);
	this.appendValueInput("PIN2", Number)
        .appendField('Echo#')
        .setCheck(Number);
	this.setInputsInline(true);
	this.setOutput(true, Number);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_CHAOSHENGBO);
  }
};

//DHT11������
Blockly.Blocks.dht11={
	init: function() {
	var WHAT = [[Blockly.MIXLY_DHT11_T, 'temperature'],[Blockly.MIXLY_DHT11_H, 'humidity']];
    this.setColour(Blockly.Blocks.blockgroup.HUE1);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_DHT11)
        .setCheck(Number);
	this.appendDummyInput("")
	    .appendField(new Blockly.FieldDropdown(WHAT), "WHAT");
	this.setOutput(true, Number);
	var thisBlock = this;
    this.setTooltip(function() {
      var op = thisBlock.getFieldValue('WHAT');
      var TOOLTIPS = {
        'temperature': Blockly.MIXLY_TOOLTIP_BLOCKGROUP_DHT11_TEM,
        'humidity': Blockly.MIXLY_TOOLTIP_BLOCKGROUP_DHT11_HUM
      };
      return TOOLTIPS[op];
    });
  }
};

//DS18B20�¶ȴ�����
Blockly.Blocks.ds18b20={
	init: function() {
	var UNIT = [[Blockly.MIXLY_DS18B20_C, '0'],[Blockly.MIXLY_DS18B20_F, '1']];
    this.setColour(Blockly.Blocks.blockgroup.HUE1);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_DS18B20)
        .setCheck(Number);
	this.appendDummyInput("")
		.appendField(Blockly.MIXLY_DS18B20_GET_TEMP)
	    .appendField(new Blockly.FieldDropdown(UNIT), "UNIT");
	this.setOutput(true, Number);
  }
};

Blockly.Blocks.servo_move = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_SERVO)
        .appendField(Blockly.MIXLY_PIN)
        .setCheck(Number);
    this.appendValueInput("DEGREE", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_DEGREE_0_180);
    this.appendValueInput("DELAY_TIME", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_DELAY+'('+Blockly.MIXLY_DELAY_MS+')');
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERVO_MOVE);
  }
};

Blockly.Blocks.servo_writeMicroseconds = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_SERVO)
        .appendField(Blockly.MIXLY_PIN)
        .setCheck(Number);
    this.appendValueInput("DEGREE", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField('writeMicroseconds');
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
	this.setInputsInline(true);
  }
};

Blockly.Blocks.servo_read_degrees = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_SERVO)
        .appendField(Blockly.MIXLY_PIN)
        .setCheck(Number);
    this.appendDummyInput("")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_READ_DEGREES)
    this.setOutput(true, Number);
	this.setInputsInline(true);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERVO_READ);
  }
};


var TONE_NOTES=[["NOTE_C3", "131"],["NOTE_D3", "147"],["NOTE_E3", "165"],["NOTE_F3", "175"],["NOTE_G3", "196"],["NOTE_A3", "220"],["NOTE_B3", "247"],
           ["NOTE_C4", "262"],["NOTE_D4", "294"],["NOTE_E4", "330"],["NOTE_F4", "349"],["NOTE_G4", "392"],["NOTE_A4", "440"],["NOTE_B4", "494"],
           ["NOTE_C5", "532"],["NOTE_D5", "587"],["NOTE_E5", "659"],["NOTE_F5", "698"],["NOTE_G5", "784"],["NOTE_A5", "880"],["NOTE_B5", "988"]];


Blockly.Blocks.tone_notes = {
   init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TONE_NOTES), 'STAT');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks.controls_tone={
init:function(){
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_TONE_PIN)
        .setCheck(Number);
    this.appendValueInput('FREQUENCY')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_FREQUENCY);
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_TONE);
  }
};

Blockly.Blocks.controls_tone2={
init:function(){
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_TONE_PIN)
        .setCheck(Number);
    this.appendValueInput('FREQUENCY')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_FREQUENCY);
    this.appendValueInput('DURATION')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_DURATION);
	this.appendDummyInput("")
		.appendField(Blockly.MIXLY_DELAY_MS);
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_TONE2);
  }
};

Blockly.Blocks.controls_notone={
init:function(){
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput("PIN", Number)
        .appendField(Blockly.MIXLY_NOTONE_PIN)
        .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_NOTONE);
  }
};

Blockly.Blocks.group_lcd_init = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput('device')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MIXLY_SETUP)
		.appendField(Blockly.MIXLY_DF_LCD)
		.appendField(new Blockly.FieldDropdown([['1602','16,2'],['2004','20,4']]),'TYPE')
		.appendField(new Blockly.FieldTextInput('mylcd'), 'VAR')
        .appendField(Blockly.MIXLY_LCD_ADDRESS);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
	this.setInputsInline(true);
  }
};

Blockly.Blocks.group_lcd_init2 = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput('device')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MIXLY_SETUP)
        .appendField(Blockly.MIXLY_DF_LCD)
		.appendField(new Blockly.FieldDropdown([['1602','16,2'],['2004','20,4']]),'TYPE')
		.appendField(new Blockly.FieldTextInput('mylcd'), 'VAR')
        .appendField(Blockly.MIXLY_LCD_ADDRESS);
    this.appendValueInput("PIN1")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField('sclPin#');
    this.appendValueInput("PIN2")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField('sdaPin#')
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
	this.setInputsInline(true);
  }
};

Blockly.Blocks.group_lcd_print = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendValueInput("TEXT", String)
        .setCheck([String,Number])
        .setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MIXLY_DF_LCD)
		.appendField(new Blockly.FieldTextInput('mylcd'), 'VAR')
        .appendField(Blockly.MIXLY_LCD_PRINT1);
    this.appendValueInput("TEXT2", String)
        .setCheck([String,Number])
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_LCD_PRINT2);
	/*
	this.appendValueInput("TEXT3", String)
        .setCheck([String,Number])
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_LCD_PRINT3);
	this.appendValueInput("TEXT4", String)
        .setCheck([String,Number])
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_LCD_PRINT4);
	*/
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

Blockly.Blocks.group_lcd_print2 = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
	this.appendValueInput("row", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MIXLY_DF_LCD)
		.appendField(new Blockly.FieldTextInput('mylcd'), 'VAR')
        .appendField(Blockly.MIXLY_LCD_ROW);
	this.appendValueInput("column", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_LCD_COLUMN);
    this.appendValueInput("TEXT", String)
        .setCheck([String,Number])
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_LCD_PRINT);
    this.setPreviousStatement(true, null);
	this.setInputsInline(true);
    this.setNextStatement(true, null);
  }
};

Blockly.Blocks.group_lcd_power = {
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendDummyInput()
		.appendField(Blockly.MIXLY_DF_LCD)
		.appendField(new Blockly.FieldTextInput('mylcd'), 'VAR')
        .appendField(new Blockly.FieldDropdown([[Blockly.MIXLY_LCD_STAT_ON, "display"], [Blockly.MIXLY_LCD_STAT_OFF, "noDisplay"], [Blockly.MIXLY_LCD_STAT_CURSOR, "cursor"], [Blockly.MIXLY_LCD_STAT_NOCURSOR, "noCursor"], [Blockly.MIXLY_LCD_STAT_BLINK, "blink"], [Blockly.MIXLY_LCD_STAT_NOBLINK, "noBlink"], [Blockly.MIXLY_LCD_STAT_CLEAR, "clear"]]), "STAT");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

Blockly.Blocks.group_stepper_setup={
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendDummyInput()
		.appendField(Blockly.MIXLY_STEPPER_SETUP_STEPPER)
        .appendField(new Blockly.FieldTextInput('mystepper'), 'VAR');
	this.appendValueInput("PIN1", Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_PIN1)
        .setCheck(Number);
	this.appendValueInput("PIN2", Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_PIN2)
        .setCheck(Number);
    this.appendValueInput('steps')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPSPERREVOLUTION);
	this.appendValueInput('speed')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_SET_SPEED);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
}

Blockly.Blocks.group_stepper_setup2={
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendDummyInput()
		.appendField(Blockly.MIXLY_STEPPER_SETUP_STEPPER)
        .appendField(new Blockly.FieldTextInput('mystepper'), 'VAR');
	this.appendValueInput("PIN1", Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_PIN1)
        .setCheck(Number);
	this.appendValueInput("PIN2", Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_PIN2)
        .setCheck(Number);
	this.appendValueInput("PIN3", Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_PIN3)
        .setCheck(Number);
	this.appendValueInput("PIN4", Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_PIN4)
        .setCheck(Number);
    this.appendValueInput('steps')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPSPERREVOLUTION);
	this.appendValueInput('speed')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_SET_SPEED);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
}

Blockly.Blocks.group_stepper_move={
  init: function() {
    this.setColour(Blockly.Blocks.blockgroup.HUE2);
    this.appendDummyInput()
		.appendField(Blockly.MIXLY_STEPPER)
        .appendField(new Blockly.FieldTextInput('mystepper'), 'VAR');
    this.appendValueInput('step')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MIXLY_STEPPER_STEP);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
	this.setInputsInline(true);
  }
}