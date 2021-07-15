#ifndef KEYPAD_H
#define KEYPAD_H

#include "main.h"
#include "oled.h"

/*
左侧端口对H1引脚的情况下
*/
#if(0)
#define KEY_HOME			0x32
#define KEY_START			0x62
#define KEY_UP				0x52
#define KEY_DOWN			0x51
#define KEY_LEFT			0x31
#define KEY_RIGHT			0x61
#define KEY_OK				0x30
#define KEY_CANCEL		0x60

#else

#define KEY_HOME			50
#define KEY_START			48
#define KEY_UP				49
#define KEY_DOWN			81
#define KEY_LEFT			82
#define KEY_RIGHT			80
#define KEY_OK				98
#define KEY_CANCEL		96
#endif
void Keypad_Init();

u8 GetKey();

#endif