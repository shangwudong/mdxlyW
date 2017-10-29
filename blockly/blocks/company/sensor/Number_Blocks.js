'use strict';

goog.provide('Blockly.Blocks.Microduino');

goog.require('Blockly.Blocks');

var colorSet='#70bd94';


Blockly.Blocks.NumberTubePre = {
  init: function() {
    this.setColour(colorSet);

    var upsideDown =[[Blockly.MD_NixiePositive, "POSITIVE"], 
                    [Blockly.MD_NixieNegative, "NEGATIVE"]
                    ];


    this.appendDummyInput("")
        .appendField(Blockly.MD_NixieTube)
        .appendField(Blockly.MDStpperPrepare);
        

    this.appendValueInput("indexNum", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MD_NixieSumNum);

    this.appendDummyInput()
    .appendField(Blockly.MD_NixieUpDown)
    .appendField(new Blockly.FieldDropdown(upsideDown), "upsideDown");

    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

    var tip="数码管准备\n";
    this.setTooltip(tip);

  }
};



Blockly.Blocks.NumberTubeSet = {
  init: function() {
    this.setColour(colorSet);

    var pointHas =[[Blockly.MD_NixieNull, "false"], 
                    [Blockly.MD_NixieHas, "true"]
                    ];


    this.appendDummyInput("")
        .appendField(Blockly.MD_NixieTube);
        

    this.appendValueInput("index", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MD_NixieIndexNum);


    this.appendValueInput("number", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MD_NixieNum);

    this.appendValueInput("light", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.MD_NixieLight);

    this.appendDummyInput()
    .appendField(Blockly.MD_NixiePoint)
    .appendField(new Blockly.FieldDropdown(pointHas), "pointHas");

    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

    var tip="数码管设置\n";
    this.setTooltip(tip);

  }
};



Blockly.Blocks.NumberTubeShow = {
  init: function() {
    this.setColour(colorSet);

    this.appendDummyInput("")
        .appendField(Blockly.MD_NixieTube)
        .appendField(Blockly.MD_NixieShow);
        
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

    var tip="数码管显示\n";
    this.setTooltip(tip);

  }
};

