// LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
// ==============

// 版权所有：
// @Microduino_sy  shenyang@microduino.com
// ==============

// Microduino-IDE
// ==============
// Microduino Getting start:
// http://www.microduino.cc/download/

// ==============
// Microduino wiki:
// http://wiki.microduino.cc

#include "Microduino_AT24Cxx.h"

AT24Cxx::AT24Cxx(uint8_t _addr)
{
  devAddr = _addr;
}
//
// PUBLIC FUNCTIONS


bool AT24Cxx::begin(void)
{
	Wire.begin();
	Wire.beginTransmission(devAddr);
	if (Wire.endTransmission())
		return false;
	return true;
}


uint16_t AT24Cxx::read(uint16_t iAddr, uint8_t *buf, uint16_t iCnt)
{
  uint8_t iRead=0, iBytes;
  while (iCnt>0) {
    Wire.beginTransmission(devAddr);
    Wire.write(iAddr>>8);   // Address MSB
    Wire.write(iAddr&0xff); // Address LSB
    Wire.endTransmission();

    iBytes = min(iCnt, 128);
    Wire.requestFrom(devAddr, iBytes);

    while (Wire.available() && iCnt>0) {
      buf[iRead] = Wire.read();
      iRead++; iCnt--; iAddr++;
    }  /* while */
  }
  return (iRead);
}

uint16_t AT24Cxx::readStr(uint16_t iAddr, uint8_t *buf, uint16_t iCnt)
{
  uint8_t iRead=0, iBytes;
  char c;
  while (iCnt>0) {
    Wire.beginTransmission(devAddr);
    Wire.write(iAddr>>8);   // Address MSB
    Wire.write(iAddr&0xff); // Address LSB
    Wire.endTransmission();

    iBytes = min(iCnt, 128);
    Wire.requestFrom(devAddr, iBytes);

    while (Wire.available() && iCnt>0) {
      c = Wire.read();
      buf[iRead] = c;
      if (c == '\0') {
        iCnt=0; break;
      }  /* if */
      iRead++; iCnt--; iAddr++;
    }  /* while */
  }
  return (iRead);
}

uint8_t AT24Cxx::write(uint16_t iAddr, uint8_t iVal)
{
  uint8_t iRC=0;
  Wire.beginTransmission(devAddr);
  Wire.write(iAddr>>8);   // Address MSB
  Wire.write(iAddr&0xff); // Address LSB
  Wire.write(iVal);
  iRC = Wire.endTransmission();
  delay(5);

  return(iRC);
}

// BYTE WRITE:
// A write operation requires two 8-bit data word addresses following the device address word and acknowledgment.
// Upon receipt of this address, the EEPROM will again respond with a zero and then clock in the first 8-bit data
// word. Following receipt of the 8-bit data word, the EEPROM will output a zero and the addressing device, such as
// a microcontroller, must terminate the write sequence with a stop condition. At this time the EEPROM enters an
// internally-timed write cycle, tWR, to the nonvolatile memory. All inputs are disabled during this write cycle and
// the EEPROM will not respond until the write is complete (refer to Figure 2).

// PAGE WRITE:
// The 32K/64K EEPROM is capable of 32-byte page writes. A page write is initiated the same way as a byte write, but
// the microcontroller does not send a stop condition after the first data word is clocked in. Instead, after the EEPROM
// acknowledges receipt of the first data word, the microcontroller can transmit up to 31 more data words. The EEPROM
// will respond with a zero after each data word received. The microcontroller must terminate the page write sequence
// with a stop condition (refer to Figure 3).

// The data word address lower 5 bits are internally incremented following the receipt of each data word. The higher
// data word address bits are not incremented, retaining the memory page row location. When the word address, internally
// generated, reaches the page boundary, the following byte is placed at the beginning of the same page. If more than 32
// data words are transmitted to the EEPROM, the data word address will “roll over” and previous data will be overwritten.
uint8_t AT24Cxx::write(uint16_t iAddr, const char *pBuf, uint16_t iCnt)
{
  uint8_t iBytes, iRC=0;

// Writes are restricted to a single 32 byte page.  Therefore. if a write spans a page
// boundry we must split the write.

  while (iCnt > 0) {
    iBytes = min(iCnt, BUFFER_LENGTH-2);
    int iCurPage = iAddr & ~((int)0x1f);
    if (iAddr+iBytes > iCurPage+32) { // Number of bytes is too large
      iBytes = (iCurPage+32) - iAddr;
    }
    Wire.beginTransmission(devAddr);
    Wire.write( highByte(iAddr) ); // Address MSB
    Wire.write( lowByte(iAddr) );  // Address LSB
    Wire.write((uint8_t*)pBuf, iBytes);
    Wire.endTransmission();
    iRC  +=(int)iBytes;
    iCnt -=(int)iBytes;
    iAddr+=(int)iBytes;
    pBuf +=(int)iBytes;
    delay(5);  // Give the EEPROM time to write its data
  }  /* while */

  return(iRC);
}

uint8_t AT24Cxx::writeStr(uint16_t iAddr, const char *pBuf)
{
  uint8_t iRC=0;
  uint16_t iCnt = strlen(pBuf);

  iRC = write(iAddr, pBuf, iCnt+1); // Write the NULL terminator
  return(iRC);
}
