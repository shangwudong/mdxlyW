'use strict';

goog.provide('Blockly.Blocks.Microduino');

goog.require('Blockly.Blocks');


var colorSet='#efa752';

Blockly.Blocks.MDSerialMotionPre = {
  init: function() {
    this.setColour(colorSet);
    this.appendDummyInput("")
        .appendField(Blockly.MDSerialMotion);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    var tip="接收串口姿态角\n";
    this.setTooltip(tip);

  }
};

Blockly.Blocks.MDSerialMotionGet = {
  init: function() {
    this.setColour(colorSet);
    var s_ypr =[[Blockly.motionYaw, "0"], 
              [Blockly.motionPitch, "1"],
              [Blockly.motionRoll, "2"]
             ];
    this.appendDummyInput("")
        .appendField(Blockly.GetMotionDegree)
        .appendField(new Blockly.FieldDropdown(s_ypr), "s_ypr");
    this.setOutput(true, Number);

    var tip="获取姿态角\n";
    this.setTooltip(tip);

  }
};

