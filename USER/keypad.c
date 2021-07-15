#include "main.h"
#include "keypad.h"
#include "oled.h"


/*
H1-PA1
H2-PA8
H3-PB1
L1-PA15
L2-PB3
L3-PB6
H设置为上拉输入，或悬浮输入，L设置为上拉输出
*/
void Keypad_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//设置H123
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_8;

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_6;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}


/*
H1-PA1
H2-PA8
H3-PB1
L1-PA15
L2-PB3
L3-PB6
H设置为上拉输入，或悬浮输入，L设置为上拉输出
*/

u8 GetKey()
{
 u8 keycode=0;        
 u8 scancode;
 u8 i=0;
 GPIO_PinState l1,l2,l3;
 GPIO_PinState h1,h2,h3;
	
 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
 h1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
 h2=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
 h3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	
	if(h1&h2&h3) return keycode;
	if(!(h1|h2|h3)) return keycode;
 scancode = 0x4;     //行扫描 100
	scancode=~scancode;//11011

 for(i=0; i<3; i++)
 {  
		//GPIO_Write(GPIOA, ~scancode);
	 l1=(scancode>>2)&GPIO_PIN_SET;
	 l2=(scancode>>1)&GPIO_PIN_SET;
	 l3=(scancode)&GPIO_PIN_SET;
	 
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,l1);
	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,l2);
	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,l3);
	 h1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
	 h2=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
	 h3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	 
//		if((GPIO_ReadInputData(GPIOA)&0x0f) != 0x0f)
	 if((h1&h2&h3)!=GPIO_PIN_SET)
		{
			 keycode = (h1<<6)|(h2<<5)|(h3<<4)|i; //读出的列值
			 while((h1&h2&h3)!=GPIO_PIN_SET) //等待按键松开
			 {
				 h1=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
				 h2=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
				 h3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);				 
			 }
			 printf("keycode is %d",keycode);
			 return keycode;
		}  
		scancode >>= 1;    //循环扫描
	}
		
//		keycode &= 0x0f;   //有按键按下为0，0x0f，只考虑低四位的处理，低四位为输入
//		switch(keycode)
//		{
//			case 0x0e:          
//						 num = 4 * i + 1;
//						 break;
//			case 0x0d:
//						 num = 4 * i + 2;
//						 break;
//			case 0x0b:
//						 num = 4 * i + 3;
//						 break;
//			case 0x07:
//						 num = 4 * i + 4;
//						 break;
//		      default:
//						 keycode = 0xff;   
//						 break;
//		 }
// }
		return keycode; 
			
}