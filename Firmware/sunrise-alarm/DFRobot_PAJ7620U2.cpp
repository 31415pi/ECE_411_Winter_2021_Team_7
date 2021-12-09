/*!
 * @file DFRobot_PAJ7620U2.cpp
 * @brief Define the basic structure of DFRobot_Sensor Class
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      Alexander(ouki.wang@dfrobot.com)
 * @maintainer  [fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-15
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_PAJ7620U2
 */
#include "DFRobot_PAJ7620U2.h"

DFRobot_PAJ7620U2::DFRobot_PAJ7620U2(TwoWire * pWire)
  :_pWire(pWire)
{
  
}

#ifdef __DFROBOT_PAJ7620U2_H_NO_ARRAY
uint8_t initRegisterArrayPair(int i, int j);
#endif

int DFRobot_PAJ7620U2::begin(void)
{
  uint16_t partid;
  _pWire->begin();
  selectBank(eBank0);
  if(readReg(PAJ7620_ADDR_PART_ID_LOW, &partid, 2) == 0){
    DBG("bus data access error");
    return ERR_DATA_BUS;
  }
 // Serial.println(partid);
  DBG("part id=0X");DBG(partid, HEX);
  if(partid != PAJ7620_PARTID){
    return ERR_IC_VERSION;
  }
#ifndef __DFROBOT_PAJ7620U2_H_NO_ARRAY
  for (uint16_t i = 0; i < sizeof(initRegisterArray)/sizeof(initRegisterArray[0]); i++) {
    writeReg(initRegisterArray[i][0], &initRegisterArray[i][1],1);
  }
#else
  for (uint16_t i = 0; i < 219; i++) {
	uint8_t adr = initRegisterArrayPair(i, 0);
	uint8_t val = initRegisterArrayPair(i, 1);
    writeReg(adr, &val, 1);
  }
#endif
  selectBank(eBank0);
  return ERR_OK;
}

int DFRobot_PAJ7620U2::setNormalOrGamingMode(eRateMode_t mode)
{
    mode = mode;
    return 0;
}

#ifndef __DFROBOT_PAJ7620U2_H_NO_STRINGS
String DFRobot_PAJ7620U2::gestureDescription(eGesture_t gesture)
{
    for(uint16_t i=0;i<sizeof(gestureDescriptionsTable)/sizeof(gestureDescriptionsTable[0]);i++){
        if(gesture == gestureDescriptionsTable[i].gesture){
          return gestureDescriptionsTable[i].description;
        }
    }
    return "";
}
#endif

void DFRobot_PAJ7620U2::setGestureHighRate(bool b)
{
  _gestureHighRate  = b;
}

DFRobot_PAJ7620U2::eGesture_t DFRobot_PAJ7620U2::getGesture(void)
{
   readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_1, &_gesture, 1);
  _gesture =(DFRobot_PAJ7620U2::eGesture_t)(((uint16_t)_gesture)<<8);
  if (_gesture == eGestureWave){
    DBG("Wave1 Event Detected");
    delay(GES_QUIT_TIME);
  }else{
    _gesture = eGestureNone;
    readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_0, &_gesture, 1);  // Read Bank_0_Reg_0x43/0x44 for gesture result.
    _gesture = (DFRobot_PAJ7620U2::eGesture_t)(((uint16_t)_gesture)&0x00ff);
    if(!_gestureHighRate){
      uint8_t tmp;
      delay(GES_ENTRY_TIME);
      readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_0, &tmp, 1);
      DBG("tmp=0x");DBG(tmp,HEX);
      DBG("_gesture=0x");DBG(_gesture,HEX);
      _gesture = (DFRobot_PAJ7620U2::eGesture_t)(((uint16_t)_gesture)|tmp);
    }
    if (_gesture != eGestureNone){
      DBG("");
      switch (_gesture)
      {
        case eGestureRight:
          DBG("Right Event Detected");
        break;
    
        case eGestureLeft: 
          DBG("Left Event Detected");
        break;
    
        case eGestureUp:
          DBG("Up Event Detected");
        break;
    
        case eGestureDown:
          DBG("Down Event Detected");
        break;
    
        case eGestureForward:
          DBG("Forward Event Detected");
          if(!_gestureHighRate){
            delay(GES_QUIT_TIME);
          }else{
            delay(GES_QUIT_TIME/5);
          }
          break;
    
        case eGestureBackward:
          DBG("Backward Event Detected");
          if(!_gestureHighRate){
            delay(GES_QUIT_TIME);
          }else{
            delay(GES_QUIT_TIME/5);
          }
          break;
    
        case eGestureClockwise:
          DBG("Clockwise Event Detected");
          break;
    
        case eGestureAntiClockwise:
          DBG("anti-clockwise Event Detected");
          break;
        default:
          uint8_t tmp;
          readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_1, &tmp, 1);
          if(tmp){
            _gesture = eGestureWave;
            DBG("Wave2 Event Detected");
          }else{
            switch(_gesture)
            {
            case eGestureWaveSlowlyLeftRight:
              DBG("LeftRight Wave Event Detected");
              break;
            case eGestureWaveSlowlyUpDown:
              DBG("UpDown Wave Event Detected");
              break;
            case eGestureWaveSlowlyForwardBackward:
              DBG("ForwardBackward Wave Event Detected");
              break;
            default:
              _gesture = eGestureWaveSlowlyDisorder;
              DBG("Wave Disorder Event Detected");
              break;
            }
          }
          break;
        }
    }
  }
  return _gesture;
}

int DFRobot_PAJ7620U2::selectBank(eBank_t bank)
{
  writeReg(PAJ7620_REGITER_BANK_SEL, &bank, 1);
  return 0;
}

void DFRobot_PAJ7620U2::writeReg(uint8_t reg, const void* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf is null pointer");
    return;
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  for(uint16_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_PAJ7620U2::readReg(uint8_t reg, void* pBuf,size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf is null pointer");
    return 0;
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if( _pWire->endTransmission() != 0){
      DBG("Wire Read Error");
      return 0;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for(uint16_t i = 0; i < size; i++)
    _pBuf[i] = _pWire->read();
  _pWire->endTransmission();
  return size;
}

#ifndef __DFROBOT_PAJ7620U2_H_NO_STRINGS
const DFRobot_PAJ7620U2::sGestureDescription_t DFRobot_PAJ7620U2::gestureDescriptionsTable[]={
  {eGestureNone, "None"},
  {eGestureRight, "Right"},
  {eGestureLeft, "Left"},
  {eGestureUp, "Up"},
  {eGestureDown, "Down"},
  {eGestureForward, "Forward"},
  {eGestureBackward, "Backward"},
  {eGestureClockwise, "Clockwise"},
  {eGestureAntiClockwise, "Anti-Clockwise"},
  {eGestureWave, "Wave"},
  {eGestureWaveSlowlyDisorder, "WaveSlowlyDisorder"},
  {eGestureWaveSlowlyLeftRight, "WaveSlowlyLeftRight"},
  {eGestureWaveSlowlyUpDown, "WaveSlowlyUpDown"},
  {eGestureWaveSlowlyForwardBackward, "WaveSlowlyForwardBackward"}
};
#endif

#ifndef __DFROBOT_PAJ7620U2_H_NO_ARRAY
const uint8_t /*PROGMEM*/ DFRobot_PAJ7620U2::initRegisterArray[219][2] = {
    {0xEF,0x00},
    {0x32,0x29},
    {0x33,0x01},
    {0x34,0x00},
    {0x35,0x01},
    {0x36,0x00},
    {0x37,0x07},
    {0x38,0x17},
    {0x39,0x06},
    {0x3A,0x12},
    {0x3F,0x00},
    {0x40,0x02},
    {0x41,0xFF},
    {0x42,0x01},
    {0x46,0x2D},
    {0x47,0x0F},
    {0x48,0x3C},
    {0x49,0x00},
    {0x4A,0x1E},
    {0x4B,0x00},
    {0x4C,0x20},
    {0x4D,0x00},
    {0x4E,0x1A},
    {0x4F,0x14},
    {0x50,0x00},
    {0x51,0x10},
    {0x52,0x00},
    {0x5C,0x02},
    {0x5D,0x00},
    {0x5E,0x10},
    {0x5F,0x3F},
    {0x60,0x27},
    {0x61,0x28},
    {0x62,0x00},
    {0x63,0x03},
    {0x64,0xF7},
    {0x65,0x03},
    {0x66,0xD9},
    {0x67,0x03},
    {0x68,0x01},
    {0x69,0xC8},
    {0x6A,0x40},
    {0x6D,0x04},
    {0x6E,0x00},
    {0x6F,0x00},
    {0x70,0x80},
    {0x71,0x00},
    {0x72,0x00},
    {0x73,0x00},
    {0x74,0xF0},
    {0x75,0x00},
    {0x80,0x42},
    {0x81,0x44},
    {0x82,0x04},
    {0x83,0x20},
    {0x84,0x20},
    {0x85,0x00},
    {0x86,0x10},
    {0x87,0x00},
    {0x88,0x05},
    {0x89,0x18},
    {0x8A,0x10},
    {0x8B,0x01},
    {0x8C,0x37},
    {0x8D,0x00},
    {0x8E,0xF0},
    {0x8F,0x81},
    {0x90,0x06},
    {0x91,0x06},
    {0x92,0x1E},
    {0x93,0x0D},
    {0x94,0x0A},
    {0x95,0x0A},
    {0x96,0x0C},
    {0x97,0x05},
    {0x98,0x0A},
    {0x99,0x41},
    {0x9A,0x14},
    {0x9B,0x0A},
    {0x9C,0x3F},
    {0x9D,0x33},
    {0x9E,0xAE},
    {0x9F,0xF9},
    {0xA0,0x48},
    {0xA1,0x13},
    {0xA2,0x10},
    {0xA3,0x08},
    {0xA4,0x30},
    {0xA5,0x19},
    {0xA6,0x10},
    {0xA7,0x08},
    {0xA8,0x24},
    {0xA9,0x04},
    {0xAA,0x1E},
    {0xAB,0x1E},
    {0xCC,0x19},
    {0xCD,0x0B},
    {0xCE,0x13},
    {0xCF,0x64},
    {0xD0,0x21},
    {0xD1,0x0F},
    {0xD2,0x88},
    {0xE0,0x01},
    {0xE1,0x04},
    {0xE2,0x41},
    {0xE3,0xD6},
    {0xE4,0x00},
    {0xE5,0x0C},
    {0xE6,0x0A},
    {0xE7,0x00},
    {0xE8,0x00},
    {0xE9,0x00},
    {0xEE,0x07},
    {0xEF,0x01},
    {0x00,0x1E},
    {0x01,0x1E},
    {0x02,0x0F},
    {0x03,0x10},
    {0x04,0x02},
    {0x05,0x00},
    {0x06,0xB0},
    {0x07,0x04},
    {0x08,0x0D},
    {0x09,0x0E},
    {0x0A,0x9C},
    {0x0B,0x04},
    {0x0C,0x05},
    {0x0D,0x0F},
    {0x0E,0x02},
    {0x0F,0x12},
    {0x10,0x02},
    {0x11,0x02},
    {0x12,0x00},
    {0x13,0x01},
    {0x14,0x05},
    {0x15,0x07},
    {0x16,0x05},
    {0x17,0x07},
    {0x18,0x01},
    {0x19,0x04},
    {0x1A,0x05},
    {0x1B,0x0C},
    {0x1C,0x2A},
    {0x1D,0x01},
    {0x1E,0x00},
    {0x21,0x00},
    {0x22,0x00},
    {0x23,0x00},
    {0x25,0x01},
    {0x26,0x00},
    {0x27,0x39},
    {0x28,0x7F},
    {0x29,0x08},
    {0x30,0x03},
    {0x31,0x00},
    {0x32,0x1A},
    {0x33,0x1A},
    {0x34,0x07},
    {0x35,0x07},
    {0x36,0x01},
    {0x37,0xFF},
    {0x38,0x36},
    {0x39,0x07},
    {0x3A,0x00},
    {0x3E,0xFF},
    {0x3F,0x00},
    {0x40,0x77},
    {0x41,0x40},
    {0x42,0x00},
    {0x43,0x30},
    {0x44,0xA0},
    {0x45,0x5C},
    {0x46,0x00},
    {0x47,0x00},
    {0x48,0x58},
    {0x4A,0x1E},
    {0x4B,0x1E},
    {0x4C,0x00},
    {0x4D,0x00},
    {0x4E,0xA0},
    {0x4F,0x80},
    {0x50,0x00},
    {0x51,0x00},
    {0x52,0x00},
    {0x53,0x00},
    {0x54,0x00},
    {0x57,0x80},
    {0x59,0x10},
    {0x5A,0x08},
    {0x5B,0x94},
    {0x5C,0xE8},
    {0x5D,0x08},
    {0x5E,0x3D},
    {0x5F,0x99},
    {0x60,0x45},
    {0x61,0x40},
    {0x63,0x2D},
    {0x64,0x02},
    {0x65,0x96},
    {0x66,0x00},
    {0x67,0x97},
    {0x68,0x01},
    {0x69,0xCD},
    {0x6A,0x01},
    {0x6B,0xB0},
    {0x6C,0x04},
    {0x6D,0x2C},
    {0x6E,0x01},
    {0x6F,0x32},
    {0x71,0x00},
    {0x72,0x01},
    {0x73,0x35},
    {0x74,0x00},
    {0x75,0x33},
    {0x76,0x31},
    {0x77,0x01},
    {0x7C,0x84},
    {0x7D,0x03},
    {0x7E,0x01}
  };

#else

uint8_t initRegisterArrayPair(int i, int j) {
	switch (i) {
	case   0: return !j ? 0xEF : 0x00;
	case   1: return !j ? 0x32 : 0x29;
	case   2: return !j ? 0x33 : 0x01;
	case   3: return !j ? 0x34 : 0x00;
	case   4: return !j ? 0x35 : 0x01;
	case   5: return !j ? 0x36 : 0x00;
	case   6: return !j ? 0x37 : 0x07;
	case   7: return !j ? 0x38 : 0x17;
	case   8: return !j ? 0x39 : 0x06;
	case   9: return !j ? 0x3A : 0x12;
	case  10: return !j ? 0x3F : 0x00;
    case  11: return !j ? 0x40 : 0x02;
    case  12: return !j ? 0x41 : 0xFF;
    case  13: return !j ? 0x42 : 0x01;
    case  14: return !j ? 0x46 : 0x2D;
    case  15: return !j ? 0x47 : 0x0F;
    case  16: return !j ? 0x48 : 0x3C;
    case  17: return !j ? 0x49 : 0x00;
    case  18: return !j ? 0x4A : 0x1E;
    case  19: return !j ? 0x4B : 0x00;
	case  20: return !j ? 0x4C : 0x20;
    case  21: return !j ? 0x4D : 0x00;
    case  22: return !j ? 0x4E : 0x1A;
    case  23: return !j ? 0x4F : 0x14;
    case  24: return !j ? 0x50 : 0x00;
    case  25: return !j ? 0x51 : 0x10;
    case  26: return !j ? 0x52 : 0x00;
    case  27: return !j ? 0x5C : 0x02;
    case  28: return !j ? 0x5D : 0x00;
    case  29: return !j ? 0x5E : 0x10;
	case  30: return !j ? 0x5F : 0x3F;
    case  31: return !j ? 0x60 : 0x27;
    case  32: return !j ? 0x61 : 0x28;
    case  33: return !j ? 0x62 : 0x00;
    case  34: return !j ? 0x63 : 0x03;
    case  35: return !j ? 0x64 : 0xF7;
    case  36: return !j ? 0x65 : 0x03;
    case  37: return !j ? 0x66 : 0xD9;
    case  38: return !j ? 0x67 : 0x03;
    case  39: return !j ? 0x68 : 0x01;
	case  40: return !j ? 0x69 : 0xC8;
    case  41: return !j ? 0x6A : 0x40;
    case  42: return !j ? 0x6D : 0x04;
    case  43: return !j ? 0x6E : 0x00;
    case  44: return !j ? 0x6F : 0x00;
    case  45: return !j ? 0x70 : 0x80;
    case  46: return !j ? 0x71 : 0x00;
    case  47: return !j ? 0x72 : 0x00;
    case  48: return !j ? 0x73 : 0x00;
    case  49: return !j ? 0x74 : 0xF0;
	case  50: return !j ? 0x75 : 0x00;
    case  51: return !j ? 0x80 : 0x42;
    case  52: return !j ? 0x81 : 0x44;
    case  53: return !j ? 0x82 : 0x04;
    case  54: return !j ? 0x83 : 0x20;
    case  55: return !j ? 0x84 : 0x20;
    case  56: return !j ? 0x85 : 0x00;
    case  57: return !j ? 0x86 : 0x10;
    case  58: return !j ? 0x87 : 0x00;
    case  59: return !j ? 0x88 : 0x05;
	case  60: return !j ? 0x89 : 0x18;
    case  61: return !j ? 0x8A : 0x10;
    case  62: return !j ? 0x8B : 0x01;
    case  63: return !j ? 0x8C : 0x37;
    case  64: return !j ? 0x8D : 0x00;
    case  65: return !j ? 0x8E : 0xF0;
    case  66: return !j ? 0x8F : 0x81;
    case  67: return !j ? 0x90 : 0x06;
    case  68: return !j ? 0x91 : 0x06;
    case  69: return !j ? 0x92 : 0x1E;
	case  70: return !j ? 0x93 : 0x0D;
    case  71: return !j ? 0x94 : 0x0A;
    case  72: return !j ? 0x95 : 0x0A;
    case  73: return !j ? 0x96 : 0x0C;
    case  74: return !j ? 0x97 : 0x05;
    case  75: return !j ? 0x98 : 0x0A;
    case  76: return !j ? 0x99 : 0x41;
    case  77: return !j ? 0x9A : 0x14;
    case  78: return !j ? 0x9B : 0x0A;
    case  79: return !j ? 0x9C : 0x3F;
	case  80: return !j ? 0x9D : 0x33;
    case  81: return !j ? 0x9E : 0xAE;
    case  82: return !j ? 0x9F : 0xF9;
    case  83: return !j ? 0xA0 : 0x48;
    case  84: return !j ? 0xA1 : 0x13;
    case  85: return !j ? 0xA2 : 0x10;
    case  86: return !j ? 0xA3 : 0x08;
    case  87: return !j ? 0xA4 : 0x30;
    case  88: return !j ? 0xA5 : 0x19;
    case  89: return !j ? 0xA6 : 0x10;
	case  90: return !j ? 0xA7 : 0x08;
    case  91: return !j ? 0xA8 : 0x24;
    case  92: return !j ? 0xA9 : 0x04;
    case  93: return !j ? 0xAA : 0x1E;
    case  94: return !j ? 0xAB : 0x1E;
    case  95: return !j ? 0xCC : 0x19;
    case  96: return !j ? 0xCD : 0x0B;
    case  97: return !j ? 0xCE : 0x13;
    case  98: return !j ? 0xCF : 0x64;
    case  99: return !j ? 0xD0 : 0x21;
	case 100: return !j ? 0xD1 : 0x0F;
	case 101: return !j ? 0xD2 : 0x88;
	case 102: return !j ? 0xE0 : 0x01;
	case 103: return !j ? 0xE1 : 0x04;
	case 104: return !j ? 0xE2 : 0x41;
	case 105: return !j ? 0xE3 : 0xD6;
	case 106: return !j ? 0xE4 : 0x00;
	case 107: return !j ? 0xE5 : 0x0C;
	case 108: return !j ? 0xE6 : 0x0A;
	case 109: return !j ? 0xE7 : 0x00;
	case 110: return !j ? 0xE8 : 0x00;
    case 111: return !j ? 0xE9 : 0x00;
    case 112: return !j ? 0xEE : 0x07;
    case 113: return !j ? 0xEF : 0x01;
    case 114: return !j ? 0x00 : 0x1E;
    case 115: return !j ? 0x01 : 0x1E;
    case 116: return !j ? 0x02 : 0x0F;
    case 117: return !j ? 0x03 : 0x10;
    case 118: return !j ? 0x04 : 0x02;
    case 119: return !j ? 0x05 : 0x00;
	case 120: return !j ? 0x06 : 0xB0;
    case 121: return !j ? 0x07 : 0x04;
    case 122: return !j ? 0x08 : 0x0D;
    case 123: return !j ? 0x09 : 0x0E;
    case 124: return !j ? 0x0A : 0x9C;
    case 125: return !j ? 0x0B : 0x04;
    case 126: return !j ? 0x0C : 0x05;
    case 127: return !j ? 0x0D : 0x0F;
    case 128: return !j ? 0x0E : 0x02;
    case 129: return !j ? 0x0F : 0x12;
	case 130: return !j ? 0x10 : 0x02;
    case 131: return !j ? 0x11 : 0x02;
    case 132: return !j ? 0x12 : 0x00;
    case 133: return !j ? 0x13 : 0x01;
    case 134: return !j ? 0x14 : 0x05;
    case 135: return !j ? 0x15 : 0x07;
    case 136: return !j ? 0x16 : 0x05;
    case 137: return !j ? 0x17 : 0x07;
    case 138: return !j ? 0x18 : 0x01;
    case 139: return !j ? 0x19 : 0x04;
	case 140: return !j ? 0x1A : 0x05;
    case 141: return !j ? 0x1B : 0x0C;
    case 142: return !j ? 0x1C : 0x2A;
    case 143: return !j ? 0x1D : 0x01;
    case 144: return !j ? 0x1E : 0x00;
    case 145: return !j ? 0x21 : 0x00;
    case 146: return !j ? 0x22 : 0x00;
    case 147: return !j ? 0x23 : 0x00;
    case 148: return !j ? 0x25 : 0x01;
    case 149: return !j ? 0x26 : 0x00;
	case 150: return !j ? 0x27 : 0x39;
    case 151: return !j ? 0x28 : 0x7F;
    case 152: return !j ? 0x29 : 0x08;
    case 153: return !j ? 0x30 : 0x03;
    case 154: return !j ? 0x31 : 0x00;
    case 155: return !j ? 0x32 : 0x1A;
    case 156: return !j ? 0x33 : 0x1A;
    case 157: return !j ? 0x34 : 0x07;
    case 158: return !j ? 0x35 : 0x07;
    case 159: return !j ? 0x36 : 0x01;
	case 160: return !j ? 0x37 : 0xFF;
    case 161: return !j ? 0x38 : 0x36;
    case 162: return !j ? 0x39 : 0x07;
    case 163: return !j ? 0x3A : 0x00;
    case 164: return !j ? 0x3E : 0xFF;
    case 165: return !j ? 0x3F : 0x00;
    case 166: return !j ? 0x40 : 0x77;
    case 167: return !j ? 0x41 : 0x40;
    case 168: return !j ? 0x42 : 0x00;
    case 169: return !j ? 0x43 : 0x30;
	case 170: return !j ? 0x44 : 0xA0;
    case 171: return !j ? 0x45 : 0x5C;
    case 172: return !j ? 0x46 : 0x00;
    case 173: return !j ? 0x47 : 0x00;
    case 174: return !j ? 0x48 : 0x58;
    case 175: return !j ? 0x4A : 0x1E;
    case 176: return !j ? 0x4B : 0x1E;
    case 177: return !j ? 0x4C : 0x00;
    case 178: return !j ? 0x4D : 0x00;
    case 179: return !j ? 0x4E : 0xA0;
	case 180: return !j ? 0x4F : 0x80;
    case 181: return !j ? 0x50 : 0x00;
    case 182: return !j ? 0x51 : 0x00;
    case 183: return !j ? 0x52 : 0x00;
    case 184: return !j ? 0x53 : 0x00;
    case 185: return !j ? 0x54 : 0x00;
    case 186: return !j ? 0x57 : 0x80;
    case 187: return !j ? 0x59 : 0x10;
    case 188: return !j ? 0x5A : 0x08;
    case 189: return !j ? 0x5B : 0x94;
	case 190: return !j ? 0x5C : 0xE8;
    case 191: return !j ? 0x5D : 0x08;
    case 192: return !j ? 0x5E : 0x3D;
    case 193: return !j ? 0x5F : 0x99;
    case 194: return !j ? 0x60 : 0x45;
    case 195: return !j ? 0x61 : 0x40;
    case 196: return !j ? 0x63 : 0x2D;
    case 197: return !j ? 0x64 : 0x02;
    case 198: return !j ? 0x65 : 0x96;
    case 199: return !j ? 0x66 : 0x00;
	case 200: return !j ? 0x67 : 0x97;
	case 201: return !j ? 0x68 : 0x01;
	case 202: return !j ? 0x69 : 0xCD;
	case 203: return !j ? 0x6A : 0x01;
	case 204: return !j ? 0x6B : 0xB0;
	case 205: return !j ? 0x6C : 0x04;
	case 206: return !j ? 0x6D : 0x2C;
	case 207: return !j ? 0x6E : 0x01;
	case 208: return !j ? 0x6F : 0x32;
	case 209: return !j ? 0x71 : 0x00;
	case 210: return !j ? 0x72 : 0x01;
    case 211: return !j ? 0x73 : 0x35;
    case 212: return !j ? 0x74 : 0x00;
    case 213: return !j ? 0x75 : 0x33;
    case 214: return !j ? 0x76 : 0x31;
    case 215: return !j ? 0x77 : 0x01;
    case 216: return !j ? 0x7C : 0x84;
    case 217: return !j ? 0x7D : 0x03;
    case 218: return !j ? 0x7E : 0x01;
    case 219:
	default:  return !j ? 0x00 : 0x00;
	}
}

#endif
