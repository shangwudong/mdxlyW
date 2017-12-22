// LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
// ==============

// 版权所有：
// @老潘orz  wasdpkj@hotmail.com
// ==============

#include <Microduino_Matrix.h>
/*
  uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {  //2x2
  { 64, 63},
  { 62, 61}
  };
*/

uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {  //1x4
  { 64, 63, 62 , 61}
};


/*
  uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {  //3x2
  { 64, 63, 62},
  { 61, 60, 59}
  };
*/

/*
  uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {  //4x4
  { 64, 63, 62, 61},
  { 60, 59, 58, 57},
  { 56, 55, 54, 53},
  { 52, 51, 50, 49}
  };
*/

Matrix display = Matrix(Addr, TYPE_COLOR); //TYPE_COLOR or TYPE_S2

static const uint8_t logoA[] PROGMEM = {   //低位在前 逐行
  0x00, 0x00, 0x14, 0x2A, 0x2A, 0x2A, 0x00, 0x00
};

static const uint8_t logoB[] PROGMEM = {  //Windows Bitmap (BMP) file,24bit
  0x42, 0x4D, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC2, 0x00, 0x00, 0x00, 0x20, 0x2E, 0x00, 0x00, 0x20, 0x2E, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xEE, 0xEE, 0xEE,
  0xEE, 0xEE, 0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0xDD, 0xEE, 0xEE,
  0xEE, 0x4D, 0x8E, 0x65, 0x26, 0x94, 0x50, 0x26, 0x94, 0x50, 0x26, 0x94, 0x50, 0x26, 0x94, 0x50,
  0x24, 0x60, 0x51, 0xEE, 0xEE, 0xDD, 0xEE, 0xEE, 0xEE, 0xDD, 0xBB, 0x99, 0xDD, 0xBB, 0x99, 0x4B,
  0x94, 0xD4, 0x2B, 0x69, 0x96, 0xCC, 0xBB, 0x84, 0xCC, 0xAA, 0x88, 0xFF, 0xEE, 0xDD, 0xFF, 0xEE,
  0xEE, 0xC7, 0xBB, 0x99, 0x50, 0xB2, 0x70, 0x26, 0x94, 0x50, 0x26, 0x94, 0x50, 0x47, 0x94, 0x4D,
  0xCC, 0xAA, 0x88, 0xEE, 0xEE, 0xDD, 0xEE, 0xEE, 0xEE, 0xDB, 0xCC, 0xB3, 0x53, 0xBB, 0x88, 0x53,
  0xBB, 0x88, 0x53, 0xBB, 0x88, 0x26, 0x94, 0x50, 0xB5, 0xAA, 0x92, 0xEE, 0xEE, 0xDD, 0xFF, 0xEE,
  0xEE, 0xDD, 0xDD, 0xCC, 0x53, 0xBB, 0x88, 0x3A, 0xD5, 0x95, 0x53, 0xBB, 0x88, 0x48, 0xAF, 0x50,
  0xCC, 0xAA, 0x99, 0xEE, 0xEE, 0xDD, 0xEE, 0xEE, 0xEE, 0xE2, 0xCB, 0xCD, 0x53, 0xBB, 0x88, 0x53,
  0xBB, 0x88, 0x3A, 0xD5, 0x95, 0x50, 0xB2, 0x70, 0xD6, 0xBB, 0xB1, 0xFF, 0xEE, 0xDD, 0xDD, 0xEE,
  0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
  0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xDD, 0x00, 0x00,
};

void setup() {
  Serial.begin(115200); // See the connection status in Serial Monitor
  Wire.begin();

  //display.clearFastMode();
  //display.setFastMode();
  //display.setBrightness(255);

  //getDeviceAddr
  for (int a = 0; a < display.getMatrixNum(); a++) {
    Serial.print(display.getDeviceAddr(a));
    Serial.print(" ");
  }
  Serial.println("");

  display.clearDisplay();
  //setLedColor
  for (int y = 0; y < display.getHeight() * 8; y++) {
    for (int x = 0; x < display.getWidth() * 8; x++) {
      display.setLedColor(x, y, random(0, 255), random(0, 255), random(0, 255));   //x, y, r, g, b
      //display.setLedBrightness(x, y, random(0, 255));   //x, y, brightness
      delay(5);
    }
  }
  delay(1000);

  //setLed
  display.clearDisplay();
  display.setColor(0, 255, 255);
  for (int y = 0; y < display.getHeight() * 8; y++) {
    for (int x = 0; x < display.getWidth() * 8; x++) {
      display.setLed(x, y, true);   //x, y, sta
      delay(5);
    }
  }
  delay(1000);

  display.clearDisplay();
  display.setColor(0, 255, 0);
  display.drawBMP(0, 0, 8, 8, logoA);  //x,y,w,h,data
  delay(2000);

  display.clearDisplay();
  //Windows Bitmap (BMP) file,24bit
  display.drawBMP(0, 0, logoB);   //x,y,data
  delay(2000);

  //clearColor
  display.clearColor();
  display.writeString("Microduino", 20, 0); //string, time ,y
  display.clearDisplay();
}

int i;
void loop() {
  display.setColor(255, 255, 0);

  display.drawBox(0, 0, display.getWidth() * 8, display.getHeight() * 8);  //x,y,w,h
  delay(2000);
  display.clearDisplay();

  display.drawRBox(0, 0, display.getWidth() * 8, display.getHeight() * 8, 2);  //x,y,w,h,r
  delay(2000);
  display.clearDisplay();

  display.drawFrame(0, 0, display.getWidth() * 8, display.getHeight() * 8);  //x,y,w,h
  delay(2000);
  display.clearDisplay();

  display.drawRFrame(0, 0, display.getWidth() * 8, display.getHeight() * 8, 2);  //x,y,w,h,r
  delay(2000);
  display.clearDisplay();

  display.drawCircle(display.getWidth() * 8 / 2, display.getHeight() * 8 / 2, 3); //x,y,r
  delay(2000);
  display.clearDisplay();

  display.drawDisc(display.getWidth() * 8 / 2, display.getHeight() * 8 / 2, 3); //x,y,r
  delay(2000);
  display.clearDisplay();

  display.drawLine(0, 0, 7, 7); //x,y,x1,y1
  delay(2000);
  display.clearDisplay();

  i = display.getStringWidth("mCookie!");
  display.setColor(255, 255, 0);
  for (int a = display.getWidth() * 8; a > -i - display.getWidth() * 8; a--) {
    display.setCursor(a, 0);   //x, y
    display.print("mCookie!");
    delay(20);
  }
  display.clearDisplay();


  //Print
  unsigned long timer = millis();
  display.setColor(0, 255, 255);
  while (millis() - timer < 5000) {
    display.setCursor(0, 0);   //x, y
    display.print((millis() - timer) / 100);
    delay(20);
  }
  display.clearDisplay();

  //String to char*
  String _buffer_data = "Analog(A0):";
  _buffer_data +=  analogRead(A0);

  char buffer_data[128];
  for (int a = 0; a < 128; a++) {
    buffer_data[a] = NULL;
  }

  for (int a = 0; a < _buffer_data.length(); a++) {
    buffer_data[a] = _buffer_data[a];
  }

  display.setColor(255, 255, 255);
  display.clearDisplay();
  display.writeString(buffer_data, 50, 1);
}