#include "main.h"
#include "keypad.h"
#include "oled.h"


/*
H1-PA1
H2-PA8
H3-PB1
L1-PA0
L2-PB3
L3-PA3
H设置为下拉输出，L设置为下拉输入
*/
void Keypad_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//设置H123
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_8;

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  //GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}


void Keypad_Init2()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//设置H123为输入
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_8;

  GPIO_InitStruct.Mode =GPIO_MODE_INPUT ;
  //GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode =GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);	
}


/*
H1-PA1
H2-PA8
H3-PB1
L1-PA0
L2-PB3
L3-PA3
H设置为下拉输出，L设置为下拉输入
*/

u8 GetKey()
{
 u8 keycode=0;        
 u8 scancode;
 u8 row,col;//按键所在的行和列，行从下往上数1-3，列从左往右数1-3，确认键在1行1列
 u8 i=0;
 GPIO_PinState l1,l2,l3;
 GPIO_PinState h1,h2,h3;

// HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
// HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
// HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
// h1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
// h2=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
// h3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
 Keypad_Init();//H输出，L输入，无按键L为0，有按键L有1
 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
 l1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
 l2=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
 l3=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);
	
//	if(h1&h2&h3) return keycode;
//	if(!(h1|h2|h3)) return keycode;
//	
	if(l1&l2&l3) return keycode;
	if(!(l1|l2|l3)) return keycode;//有键被按下，先分析是第几行
	if(l1)
		row=1;
	else if (l2)
		row=2;
	else if(l3)
		row=3;
	
	Keypad_Init2();//L输出，H输入，无按键H为1，有按键H有0
	
	 h1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
   h2=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
   h3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	
	if(!h1)
		col=1;
	else if(!h2)
		col=2;
	else if(!h3)
		col=3;
	else
		return keycode;
			
		//根据行列计算键码
	return (row<<4)|col;

		return keycode; 
			
}