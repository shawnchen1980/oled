#ifndef KEYPAD_H
#define KEYPAD_H

#include "main.h"
#include "oled.h"

/*
左侧端口对H1引脚的情况下，row x col
*/
#if(1)
#define KEY_HOME			0x31
#define KEY_START			0x33
#define KEY_UP				0x32
#define KEY_DOWN			0x22
#define KEY_LEFT			0x21
#define KEY_RIGHT			0x23
#define KEY_OK				0x11
#define KEY_CANCEL		0x13

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