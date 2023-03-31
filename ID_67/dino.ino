#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ADXL345_U.h>
//obs1 hex
static const unsigned char PROGMEM obs1[] = {0x00,0x00,0x00,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0xce,0x03,0xc0,0x00
,0xea,0x03,0xe0,0x00
,0xf9,0x07,0xe0,0x00
,0x19,0x87,0xe0,0x00
,0x0f,0xcf,0xf0,0x00
,0x0f,0xdf,0xf8,0x00
,0x1f,0xdf,0xf8,0x00
,0x3f,0xff,0xfc,0x00
,0x30,0xff,0xfe,0x00
,0x30,0xff,0xfe,0x00
,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x80
,0x00,0xff,0xff,0x80
,0x00,0xff,0xff,0x80
,0x00,0xff,0xff,0x00
,0x00,0xcf,0xff,0x80
,0x1f,0xc7,0xff,0x80
,0x1f,0xc3,0xff,0x80
,0x14,0xc3,0xff,0x00
,0x14,0xc3,0xff,0x00
,0x00,0x03,0xfb,0x80
,0x00,0x03,0xf9,0xc0
,0x00,0x01,0x99,0xc0
,0x00,0x01,0x98,0xe0
,0x00,0x01,0x88,0x60
,0x00,0x01,0x8c,0x60
,0x00,0x01,0x8c,0x20
,0x00,0x01,0x8c,0x30
,0x00,0x01,0x8c,0x10
,0x00,0x01,0x8c,0x18
,0x00,0x01,0x8c,0x08
,0x00,0x03,0x9c,0x04
,0x00,0x03,0x9c,0x00
,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00

};
//tree3 hex
static const unsigned char PROGMEM tree3[] = {0x00,0x00,0x00,0x00
,0x00,0x00,0xc0,0x00
,0x00,0x03,0x80,0x00
,0x00,0x07,0x00,0x80
,0x00,0x0e,0x01,0x00
,0x01,0x9e,0x0e,0x00
,0x0f,0xff,0xfe,0x00
,0x1f,0xff,0xff,0x80
,0x3f,0xff,0xff,0xc0
,0x73,0xff,0xff,0xf8
,0xe3,0xff,0xff,0xf8
,0x83,0xff,0xff,0xf0
,0x07,0xcf,0xff,0xe0
,0x0f,0x87,0xff,0x00
,0x1c,0x07,0x9f,0x80
,0x38,0x07,0x1f,0xc0
,0x30,0x01,0x8f,0xc0
,0x20,0x01,0x83,0x80
,0x00,0x01,0x83,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x01,0x80,0x00
,0x00,0x03,0x80,0x00
,0x00,0x07,0xc0,0x00
,0x00,0x8f,0xec,0x00
,0x00,0x7f,0xfc,0x00
,0x00,0x3f,0xf8,0x00


};
//startup page hex
static const unsigned char PROGMEM start[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xe0,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0x83,0xe0,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0x0f,0x80,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xfc,0x3e,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xe0,0x38,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x80,0xe0,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xfc,0x00,0xc0,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xe0,0x07,0xff,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xf0,0x1f,0xff,0xf0,0x00,0xc0,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,0xf8,0xff,0xff,0x80,0x00,0xc0,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xfd,0xff,0xfe,0x00,0x00,0x60,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0xf0,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,0xfb,0xff,0xff,0xf0,0x00,0x01,0xf8,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0xff,0xf8,0x00,0xff,0xff,0xc0,0x00,0x03,0xfc,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0xff,0xe0,0x00,0xff,0x7f,0x00,0x00,0x0f,0xfe,0x00,0x00
,0x00,0x00,0x00,0x0f,0xff,0xff,0xc0,0x00,0x3f,0x3e,0x00,0x00,0x3f,0xff,0x00,0x00
,0x00,0x00,0x3f,0xff,0xff,0xff,0x00,0x00,0x0f,0x18,0x00,0x0f,0xff,0xff,0x00,0x00
,0x00,0x03,0xff,0xff,0xff,0xff,0x00,0x00,0x1f,0x00,0x00,0x7f,0xff,0xff,0xc0,0x00
,0x00,0x1f,0xff,0xff,0xff,0xff,0x00,0x00,0x1f,0x00,0x01,0xe0,0x7f,0xff,0xe0,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x1f,0x00,0x03,0x00,0x1f,0xff,0xe0,0x00
,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x0f,0x00,0x0f,0xff,0xe0,0x00
,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x1c,0x00,0x07,0xff,0xe0,0x00
,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x38,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xf0,0x3f,0xff,0xff,0xff,0xff,0xff,0x00,0xe0,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xc0,0x1f,0xff,0xff,0xff,0xff,0xff,0x01,0xc0,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0x03,0x80,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xc0,0x00,0x00,0x00,0x1f,0xff,0xff,0x18,0x00,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xc0,0x00,0x00,0x00,0x3f,0xff,0xff,0x18,0x00,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xf0,0x00,0x00,0x00,0x3f,0xff,0xff,0x0c,0x00,0x00,0x03,0xff,0xe0,0x00
,0x0f,0xff,0xf0,0x00,0x00,0x00,0x00,0x7f,0xff,0x06,0x00,0x00,0x03,0xff,0xef,0x00
,0x0f,0xff,0xf0,0x00,0x00,0x00,0x00,0x7f,0xff,0x06,0x00,0x00,0x03,0xff,0xef,0x00
,0x0f,0xff,0xf0,0x00,0x00,0x00,0x00,0x7f,0xff,0x06,0x00,0x00,0x03,0xff,0xef,0x80
,0x0f,0xff,0xc0,0x00,0x0e,0x00,0x00,0x7f,0xff,0x06,0x00,0x00,0x03,0xff,0xed,0x80
,0x0f,0xfe,0x00,0x07,0x0e,0x00,0x00,0x7f,0xff,0x06,0x00,0x00,0x03,0xff,0xec,0xc0
,0x0f,0x00,0x00,0xc7,0x0e,0x00,0x00,0x7f,0xfe,0x06,0x00,0x00,0x03,0xff,0xec,0xc0
,0x0f,0x06,0x66,0xc7,0x0e,0x00,0x00,0x7f,0xfe,0x06,0x00,0x00,0x00,0x3f,0xec,0xe0
,0x0f,0x37,0x66,0xc7,0x00,0x00,0x00,0x7f,0xfe,0x06,0x00,0x00,0x00,0x3f,0xec,0x60
,0x0f,0x37,0x66,0xc3,0x00,0x00,0x00,0x7f,0xfc,0x06,0x00,0x00,0x00,0x3f,0xcc,0x60
,0x07,0x37,0x66,0xc0,0x00,0x00,0x00,0x7f,0xf8,0x06,0x00,0x00,0x00,0x3f,0x8c,0x60
,0x03,0xb7,0x66,0xf0,0x00,0x00,0x00,0x7f,0xf0,0x06,0x00,0x00,0x00,0x3f,0x0c,0x60
,0x01,0xf7,0x06,0x38,0x00,0x00,0x00,0x7f,0xc0,0x06,0x00,0x00,0x00,0x3e,0x0c,0x60
,0x00,0x60,0x00,0x1c,0x00,0x00,0x00,0xfe,0x00,0x06,0x00,0x00,0x00,0x3c,0x0c,0x60
,0x00,0x40,0x00,0x0e,0x00,0x00,0x01,0x80,0x00,0x07,0x00,0x00,0x00,0x38,0x0c,0x60
,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x30,0x1c,0x60
,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x01,0xc0,0x00,0x00,0x20,0x1c,0x60
,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x01,0xe0,0x00,0x00,0x00,0x38,0x60
,0x00,0x00,0x00,0x03,0x00,0x07,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x38,0x60
,0x00,0x00,0x00,0x03,0x00,0x0f,0xc0,0x00,0x00,0x00,0x78,0xf0,0x00,0x00,0x78,0x60
,0x00,0x00,0x00,0x07,0x00,0x0f,0xc0,0x00,0x00,0x00,0x7f,0xf8,0x00,0x00,0x70,0x60
,0x00,0x00,0x00,0x0f,0x00,0x7f,0x80,0x00,0x00,0x00,0x7f,0xfc,0x00,0x00,0xf0,0x60
,0x00,0x00,0x00,0x1f,0x0f,0xfe,0x00,0x00,0x00,0x00,0x7f,0xff,0xf0,0x01,0xe0,0x60
,0x00,0x00,0x00,0x1e,0x0f,0xfc,0x00,0x00,0x00,0x00,0x7f,0xff,0xf8,0x01,0xe0,0xe0
,0x00,0x00,0x00,0x3c,0x0f,0xf0,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0x07,0xc0,0xf0
,0x00,0x00,0x01,0xf9,0xef,0xc0,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xc0,0xf0
,0x00,0x00,0x0f,0xf1,0xff,0x00,0x00,0x0e,0x00,0x00,0x07,0xff,0xff,0xff,0x00,0xf0
,0x00,0x00,0x1f,0xfd,0xfc,0x00,0x0f,0xff,0xfe,0x00,0x00,0x07,0xff,0xff,0x00,0xf0
,0x00,0x01,0xff,0x9c,0xf8,0x00,0x7f,0xff,0xfe,0x00,0x00,0x00,0xcf,0xfc,0x01,0xf0
,0x03,0xff,0xff,0x9c,0xe0,0x03,0xff,0xff,0xfe,0x00,0x00,0x00,0xc8,0x10,0x01,0xf0
,0x1f,0xff,0xff,0x9f,0x00,0x0f,0xff,0xff,0xfe,0x00,0x00,0x01,0xc0,0x00,0x01,0xf0
,0x1f,0xff,0xff,0xfc,0x00,0x3f,0xff,0xff,0xff,0x00,0x00,0x03,0xc0,0x00,0x01,0xf0
,0x1f,0xff,0xff,0xf0,0x01,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xe0,0x00,0x01,0xf0
,0x1f,0xff,0xff,0xc0,0x07,0xff,0xff,0xff,0xff,0x80,0x00,0x0f,0xf0,0x00,0x03,0xf0
,0x1f,0xff,0xfc,0x00,0x1f,0xff,0xff,0xff,0xff,0xc0,0x00,0x1f,0xf0,0x00,0x03,0xf0
,0x1f,0xff,0xfe,0x00,0x7f,0xff,0xff,0xff,0xff,0xc0,0x00,0x3f,0xf8,0x00,0x07,0xf0
,0x1f,0xff,0xff,0x01,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x7f,0xf8,0x00,0x07,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x7f,0xf0,0x00,0x07,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0xff,0xf0,0x00,0x0f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x01,0xff,0xe0,0x00,0x0f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x03,0xff,0xe0,0x00,0x0f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x07,0xff,0xc0,0x00,0x1f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0f,0xff,0x80,0x00,0x1f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0f,0xff,0x00,0x00,0x3f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9f,0xff,0x00,0x00,0x3f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9f,0xfe,0x00,0x00,0x7f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xfc,0x00,0x00,0x7f,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd,0xff,0xdf,0xfc,0x00,0x00,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xff,0xff,0xf8,0x00,0x00,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xff,0xff,0xf0,0x00,0x01,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x7f,0xff,0xe0,0x00,0x03,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3f,0xff,0xc0,0x00,0x07,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x1f,0xff,0xc0,0x00,0x0f,0xff,0xc0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0f,0xff,0x80,0x00,0x0f,0xff,0xc0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0xff,0x00,0x00,0x1f,0xff,0x80
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x03,0xfe,0x00,0x00,0x3f,0xff,0x00
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0xe8,0x00,0x00,0x3f,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x00,0x00,0x3f,0xff,0xf0
,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x3f,0xff,0xf0
,0x1f,0xff,0xfe,0x3f,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x7f,0xff,0xf0
,0x1f,0xff,0xfe,0x3f,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0xff,0xff,0xf0
,0x1f,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x01,0xff,0xff,0xf0
,0x1f,0xff,0xf8,0x0f,0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x03,0xff,0xff,0xf0
,0x1f,0xff,0xf0,0x0f,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x07,0xff,0xff,0xf0
,0x1f,0xfd,0xe0,0x0f,0xff,0xff,0xff,0xef,0xff,0xfe,0x00,0x00,0x07,0xff,0xff,0xf0
,0x1f,0xf0,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0xc0,0x07,0xff,0xff,0xf0
,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xfe,0x01,0xe0,0x07,0xff,0xff,0xf0
,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xfe,0x03,0xf0,0x06,0x7f,0xff,0xf0
,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xf8,0x03,0xf0,0x00,0xff,0xff,0xf0
,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xf0,0x03,0xff,0xff,0xf0
,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0x03,0xf0,0x07,0xff,0xff,0xf0

};
//dino hex
static const unsigned char PROGMEM dino1[]={
0x00,0x00,0x07,0x30
,0x00,0x00,0x07,0x30
,0x00,0x00,0x07,0xf8
,0x00,0x00,0x0f,0xf8
,0x00,0x00,0x0e,0xf8
,0x00,0x00,0x1e,0xf0
,0x00,0x00,0x1e,0xf0
,0x00,0x00,0x3f,0xf0
,0x00,0x00,0x3f,0xc0
,0x00,0x00,0x3f,0x80
,0x00,0x00,0x7f,0xc0
,0x00,0x00,0x7f,0xe0
,0x00,0x1f,0xff,0xf0
,0x00,0x3f,0xff,0xf0
,0x08,0x7f,0xfd,0xe0
,0x08,0x7f,0xfd,0xe0
,0x18,0xff,0xfd,0xe0
,0x30,0xff,0xfc,0x00
,0x21,0xff,0xfc,0x00
,0x71,0xff,0xfc,0x00
,0x73,0xff,0xfc,0x00
,0x7f,0xff,0xff,0x00
,0x7f,0xff,0xff,0x00
,0x3f,0xff,0xcf,0x00
,0x0f,0xff,0xe7,0x00
,0x0f,0xff,0xe5,0x00
,0x00,0xfb,0xe0,0x00
,0x00,0xfb,0xe0,0x00
,0x00,0xf1,0xe0,0x00
,0x00,0xf1,0xe0,0x00
,0x00,0x71,0xc0,0x00
,0x00,0x60,0x80,0x00
,0x00,0x60,0x80,0x00
,0x00,0x60,0x80,0x00
,0x00,0x60,0x80,0x00
,0x00,0x70,0xc0,0x00
,0x00,0x70,0xe0,0x00
,0x00,0x38,0xf0,0x00
,0x00,0x3c,0x78,0x00
,0x00,0x1c,0x78,0x00

};
// Defines
#define SCREEN_WIDTH 128 // LCD display width, in pixels
#define SCREEN_HEIGHT 128 // LCD display height, in pixels

#define TFT_CS        10
#define TFT_RST       9
#define TFT_DC        8

#define DINO_WIDTH 25
#define DINO_HEIGHT 26
#define DINO_INIT_X 10 // Dino initial spawn location
#define DINO_INIT_Y 99 // Dino initial spawn location

#define BASE_LINE_X 0
#define BASE_LINE_Y 117
#define BASE_LINE_X1 127
#define BASE_LINE_Y1 117

#define TREE1_WIDTH 11
#define TREE1_HEIGHT 23

#define TREE2_WIDTH 22
#define TREE2_HEIGHT 23

#define TREE_Y 94

#define JUMP_PIXEL 22 // Number of pixels dino will jump

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

bool gameOver = false;
bool isJumping = false;

int score = 0;
int el=0;
int coinX,coinY;
int dinoX = DINO_INIT_X;
int dinoY = DINO_INIT_Y;
int treeX = SCREEN_WIDTH;
int treeType = 1; // 1: tree1, 2: tree2
int batteryPin = A1;
const int LED_PIN = 3;
int coin=0;
void setup() {
 
  

Serial.begin(9600);


  pinMode(LED_PIN, OUTPUT);
  pinMode(batteryPin, INPUT);
  
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3); // Rotate the display 270 degrees

  accel.begin();
  accel.setRange(ADXL345_RANGE_2_G);
  accel.setDataRate(ADXL345_DATARATE_100_HZ);

  tft.fillScreen(ST7735_WHITE);

  drawDino(dinoX, dinoY);
  drawBaseLine(BASE_LINE_X, BASE_LINE_Y, BASE_LINE_X1, BASE_LINE_Y1);
  drawTree(treeX, TREE_Y, treeType);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(30, 60);
  tft.setTextSize(1);
  tft.println("Battery");
  tft.setCursor(50, 80);
  tft.println("Level");
  //Starting Page
  tft.drawBitmap(0,0,start,128,128,0x11F1);
 tft.setCursor(5, 5);
tft.setTextColor(ST7735_RED);
tft.setTextSize(2);
tft.print("DINO GAME");

delay(4000);
 tft.fillScreen(ST7735_WHITE);
 tft.setCursor(5, 5);
tft.setTextColor(ST7735_RED);
tft.setTextSize(3);
tft.print("TEAM 78");
tft.setTextSize(2);
 tft.setCursor(2, 50);
tft.print("Starting...");
tone(2, 3136, 10);
delay(1000);
tone(2, 3136, 10);
delay(1000);
tone(2, 3136, 10);
delay(1000);
tone(2, 3136, 10);

}

void loop() {
  //for sound
  tone(2, 3136, 1);
  //control display brightness
  int potValue = analogRead( A0);
  int brightness = map(potValue, 0, 1023, 0, 255);
   analogWrite(3,brightness);
   //display battery percentage
  int batteryValue = analogRead(batteryPin);
  float batteryVoltage = batteryValue * (5.0 / 1023.0); 
  int batteryPercentage = map(batteryVoltage, 3.0, 4.2, 0, 100); 
  tft.setCursor(5,5);
  tft.setTextSize(1);
  tft.println("Battery");
   tft.setCursor(15,15);
  tft.print(batteryPercentage);
  tft.print("%");

  //initialise ADXL345
  sensors_event_t event;
  accel.getEvent(&event);
  a:
if((event.acceleration.x>9)&& gameOver==1){
        gameOver=0;
      treeX-=45;
        goto a;
      }
  if (!gameOver) {
    // Move the tree to the left
    treeX -= 2;

    // Draw the new frame
    drawFrame();

    // Check for collision
    if (checkCollision()) {
      gameOver = true;
      drawGameOver();
      
      
    }

    // Check if the dino should jump
    if (event.acceleration.y > 5.0) {
      isJumping = true;
      jump();
    }

    // If the dino is jumping, move it up
    if (isJumping) {
      isJumping= false;
      dinoY -= 4;
      drawDino(dinoX, dinoY);
      // delay(5);
    }

    // If the dino is not jumping, move it down
    if (!isJumping && dinoY < DINO_INIT_Y) {
      dinoY += 4;
      drawDino(dinoX, dinoY);
      delay(5);
    }

    // If the dino has landed, stop jumping
    if (dinoY >= DINO_INIT_Y) {
      isJumping = false;
    }

    // Increase the score
    score++;
  }
}

void drawFrame() {
  tft.fillScreen(ST7735_WHITE);
  drawDino(dinoX, dinoY);
  drawBaseLine(BASE_LINE_X, BASE_LINE_Y, BASE_LINE_X1, BASE_LINE_Y1);

// Draw the tree
if (treeType == 1) {
drawTree(treeX, TREE_Y, 1);
} else if (treeType==2){
drawTree(treeX, TREE_Y, 2);
}
else if (treeType==3){
drawTree(treeX, TREE_Y, 3);
}
else if (treeType==4){
drawTree(treeX, TREE_Y, 4);
}

// Check if the tree has passed the screen and reset it
if (treeX < -TREE1_WIDTH) {
treeX = SCREEN_WIDTH;
treeType = random(1, 5); // Randomize the obstacle type
}
// Randomize coin location
if(coin==0){
coinX=random(0,128);
coinY=random(60,128);

coin=1;
}
else{
  coinX-=4;
}
if(!checkCoin(coinX,coinY)||coinX<0){
  coin=0;
  coinX=-1;
  coinY=-1;
}
else if(checkCoin(coinX,coinY)){
  el++;
}
drawCoin(coinX,coinY);
// Draw the score
drawScore(score);
}
//Jump
void jump() {
  if(dinoY<0){
    drawinDino(dinoX, dinoY);
    delay(5);
    dinoY+=5;
    delay(5);
    dinoY+=15;

  }
  else{
drawinDino(dinoX, dinoY);
dinoY -= 10;
delay(5);
dinoY -= 10;
delay(5);
drawDino(dinoX, dinoY);
delay(0);}
}
//Gameover
void drawGameOver() {
tft.fillScreen(ST7735_WHITE);  
tft.setCursor(10, 50);
tft.setTextColor(ST7735_RED);
tft.setTextSize(2);
tft.print("GAME OVER");
tft.setCursor(40, 40);
tft.setTextColor(ST7735_BLACK);
tft.setTextSize(1);
tft.print("Score: ");
tft.print(el);
tft.setCursor(5,80);
tft.setTextColor(ST7735_BLACK);
tft.setTextSize(1);
tft.print("Rotate upward to \n restart the game.");
}

void drawDino(int x, int y) {
// Dino body

 tft.drawBitmap(x,y-11,dino1,30,30,0x1111);


}
void drawinDino(int x, int y) {
// Dino body
 tft.drawBitmap(x,y-11,dino1,30,30,ST7735_WHITE);

}
//Base line
void drawBaseLine(int x1, int y1, int x2, int y2) {
tft.drawLine(x1, y1, x2, y2, ST7735_BLACK);
}

//draw tree
void drawTree(int x, int y, int type) {
if (type == 1) {
// Draw tree type 1
tft.fillRect(x, y, TREE1_WIDTH, TREE1_HEIGHT, ST7735_BLACK);
tft.fillRect(x + 3, y - 5, 5, 5, ST7735_GREEN);
tft.fillRect(x + 3, y - 10, 5, 5, ST7735_GREEN);
tft.fillRect(x + 6, y - 15, 5, 5, ST7735_GREEN);
} else if (type==2){
// Draw tree type 2
tft.fillRect(x, y, TREE2_WIDTH, TREE2_HEIGHT, ST7735_BLACK);
tft.fillRect(x + 7, y - 5, 8, 5, ST7735_GREEN);
tft.fillRect(x + 3, y - 10, 15, 5, ST7735_GREEN);
tft.fillRect(x, y - 15, 22, 5, ST7735_GREEN);
}
else if(type==3){
  tft.drawBitmap(x,y-14,obs1,30,40,ST7735_BLACK);
}
else if(type==4){
  tft.drawBitmap(x,y-16,tree3,30,40,ST7735_GREEN);
}
}
//draw score
void drawScore(int score) {
tft.setCursor(80, 5);
tft.setTextColor(ST7735_BLACK);
tft.setTextSize(1);
tft.print("Score:");
tft.print(el);
}
//draw coin
void drawCoin(int coinX,int coinY){
  tft.fillCircle(coinX, coinY, 4, 0x1111);
}
bool checkCoin(int coinX,int coinY){
  return (dinoX < coinX+4 && dinoX+44 > coinX && dinoY < coinY+4 && dinoY+34 > coinY);
}

//check collision
bool checkCollision() {
  int treeHeight;

  if (treeType == 1) {
    treeHeight = TREE1_HEIGHT;
  } else if(treeType==2) {
    treeHeight = TREE2_HEIGHT;
  }
  else if(treeType==3) {
    treeHeight = 30;
  }
  else if(treeType==4) {
    treeHeight = 40;
  }
  // Check if the dino and the tree are overlapping
  if (treeX < dinoX+25 &&
      treeHeight < dinoY -25 ) {
    return true;
  }
else{
  return false;}
}