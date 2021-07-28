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
H����Ϊ���������L����Ϊ��������
*/
void Keypad_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//����H123
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
	
	//����H123Ϊ����
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
H����Ϊ���������L����Ϊ��������
*/

u8 GetKey()
{
 u8 keycode=0;        
 u8 scancode;
 u8 row,col;//�������ڵ��к��У��д���������1-3���д���������1-3��ȷ�ϼ���1��1��
 u8 i=0;
 GPIO_PinState l1,l2,l3;
 GPIO_PinState h1,h2,h3;

// HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
// HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
// HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
// h1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
// h2=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
// h3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
 Keypad_Init();//H�����L���룬�ް���LΪ0���а���L��1
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
	if(!(l1|l2|l3)) return keycode;//�м������£��ȷ����ǵڼ���
	if(l1)
		row=1;
	else if (l2)
		row=2;
	else if(l3)
		row=3;
	
	Keypad_Init2();//L�����H���룬�ް���HΪ1���а���H��0
	
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
			
		//�������м������
	return (row<<4)|col;

		return keycode; 
			
}