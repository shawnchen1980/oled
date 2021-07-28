//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-0101
//  最近修改   : 
//  功能描述   : STM32L053C8T6开发板点亮显示屏实验
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   PA0（SCL）
//              D1   PA1（SDA）
//              RES  PA2
//              DC   PA3
//              CS   PA4 
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018
#include "main.h"



#include "my_hal_uart.h"
#include "my_hal_spi.h"
#include "my_hal_tim.h"
#include "oled_menu.h"
//#include "GT20L16P1Y.h"
#include "GT21L16S2Y.h"
#include "ugui_SSD1309.h"
#include "ugui.h"
#include "wnd_settime.h"
#include "wnd_mainmenu.h"
#include "keypad.h"

//unsigned long GB2312_16_GetData_v2( unsigned char MSB,unsigned char LSB , unsigned char * DZ_Data);


extern __IO ITStatus UartReady;
extern UART_HandleTypeDef UartHandle;
uint8_t pBuff[25];

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****UART_TwoBoards_ComIT****  ****UART_TwoBoards_ComIT****  ****UART_TwoBoards_ComIT**** ";

/* Buffer used for reception */
uint8_t aRxBuffer[255];
uint8_t value;


void SystemClock_Config(void);
void Uart_Action(void);

/* *** Glogal GUI structure for this. *** */
UG_GUI gui1309;

/*
H1-PA1
H2-PA8
H3-PB1
L1-PA15
L2-PB3
L3-PB6
H设置为上拉输入，或悬浮输入，L设置为上拉输出
*/


int main(void)
{

	
	
	
	u8 t=' ';
//	const char* x="中";
	HAL_Init();
	SystemClock_Config();
	Uart_Init();
	Spi_Init();
	Timer_Init();
//while(1){
//	printf("system core clock is %d",SystemCoreClock);
//}
//	char buf[20];
//	
//	printf("hello中国中");
//	sprintf(buf,"%s","景");
//	GB2312_16_GetData_v2(buf[0],buf[1],pBuff);
//	
//	char a=buf[5];
	//MC_Init();
//	MC_AddItem(0,1);
//	MC_AddItem(1,2);
//	MC_AddItem(2,3);
//	MC_AddItem(0,4);
//	MC_AddItem(4,5);
//	MC_AddItem(4,6);
//	MC_AddItem(6,7);
	OLED_Init();	
	
	UG_Init(&gui1309, Display_PSet, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	Keypad_Init();
	//UG_FillScreen(0);
	
	//mc.currWnd =CreateWindow_SetTime();
	mc.currWnd=CreateWindow_MainMenu();

    UG_Update();
//		
//		UG_FontSelect(&FONT_4X6);
//		UG_PutChar ( ':' , 58 , 43 , C_WHITE, C_BLACK );
//		UG_PutChar ( ':' , 72 , 43 , C_WHITE, C_BLACK );
		
		//OLED_ShowPicture(0,0,128,64,star,1);
//		UG_FillFrame(10,20,26,28,C_BLACK);
//		UG_DrawFrame(11,21,24,27,C_WHITE);
//		UG_FillFrame(25,23,25,25,C_WHITE);
//		UG_FillFrame(13,23,22,25,C_WHITE);
const u8 *menus1[]={
	"hello"

	
};
u8 chr[]="你好吗hello";
u8 pBuff1[32];
//			ASCII_GetData('H',ASCII_6X12,pBuff1);//读取6X12点阵 ASCII 编码A的点阵数据，并将点阵数据存在pBuff数组中；数据长度为12 BYTE
//			OLED_ShowASCIIFromBuff(10,20,1,pBuff1);
			//gt_16_GetData(0xb0,0xa1,pBuff1); //读取12X12点阵汉字“啊”的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为24 BYTE
			//OLED_ShowChineseFromBuff(10,20,16,1,pBuff1);
//GB2312_16_GetData_v2(*chr,*(chr+1),pBuff);
//OLED_ShowChineseFromBuff(10,20,16,1,pBuff);

		//r_dat_bat(0x3b7c0,12,pBuff1);
		OLED_ShowString(10,20,chr,WORD_SIZE,1);
		//UG_PutString(10,20,"hello");
		//HAL_Delay(5000);
		OLED_Refresh();
					//GetKey();
		while(1){

		while(!value){}
			if(mc.currWnd){
				CX_InputUpdate(value);
				value='\0';
				UG_Update();
				OLED_Refresh();					
				
			}
//			t=GetKey();
//			if(t){
//				switch(t){
//					case KEY_LEFT:
//						value='l';
//						break;
//					case KEY_RIGHT:
//						value='r';
//						break;
//					case KEY_UP:
//						value='u';
//						break;
//					case KEY_DOWN:
//						value='d';
//						break;

//				}
//			}
//			if(value=='t'){
//				value=0;
////			CX_TextboxToggleColor(&window_1, TXB_ID_0);
////							CX_TextboxToggleColor(&window_1, TXB_ID_1);
////											CX_TextboxToggleColor(&window_1, TXB_ID_2);
//			    UG_Update();
//					OLED_Refresh();
//				
//			}
				

		}
	HAL_Delay(5000);
	
//	MC_DisplayCurrentMenu();
//	HAL_Delay(1500);
//	
//	MC_MoveToNextItem();
//	MC_DisplayCurrentMenu();
//	HAL_Delay(1500);
//	
//	MC_MoveToSubMenu();
//	MC_DisplayCurrentMenu();
//	HAL_Delay(1500);
//	
//	MC_MoveToParentMenu();
//	MC_DisplayCurrentMenu();
//	HAL_Delay(1500);
//	MC_PrintConfig();


	//LED_ON;
	//Uart_Action();
	while(1)
	{
		switch(value) {
			case 'u':
				MC_MoveToPrevItem();
				MC_DisplayCurrentMenu();
				value=0;
				break;
			case 'd':
				MC_MoveToNextItem();
				MC_DisplayCurrentMenu();
				value=0;
				break;
			case 'e':
				MC_MoveToSubMenu();
				MC_DisplayCurrentMenu();
				value=0;
				break;
			case 'b':
				MC_MoveToParentMenu();
				MC_DisplayCurrentMenu();
				value=0;
				break;
			default:
				break;
		}
		
		/*
		概念代码
		while(!input){}//假如没有输入就一直停止
		if(!currentWndProc) 
			menuProc(input);//menuProc就是上述的菜单处理例程
		else
			currentWndProc(input)
		
		*/
		//HAL_UART_Receive_IT(&UartHandle, (uint8_t *)&value,1);
			if(0){
//			OLED_ShowPicture(0,0,128,64,BMP1,1);
	//		OLED_Refresh();
	//		HAL_Delay(500);
	//		OLED_Clear();
	//		OLED_ShowChinese(0,0,0,16,1);//中
	//		OLED_ShowChinese(18,0,1,16,1);//景
	//		OLED_ShowChinese(36,0,2,16,1);//园
	//		OLED_ShowChinese(54,0,3,16,1);//电
	//		OLED_ShowChinese(72,0,4,16,1);//子
	//		OLED_ShowChinese(90,0,5,16,1);//技
	//		OLED_ShowChinese(108,0,6,16,1);//术
			//OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
	//		OLED_ShowString(20,32,"2014/05/01",16,1);
	//		OLED_ShowString(0,48,"ASCII:",16,1);  
	//		OLED_ShowString(63,48,"CODE:",16,1);
	//		OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
	//		t++;
	//		if(t>'~')t=' ';
			OLED_ShowChar(0,5,'>',16,1);
			OLED_ShowNum(10,5,123,3,16,1);
			OLED_ShowNum(10,20,456,3,16,1);
			OLED_ShowNum(10,35,789,3,16,1);
			OLED_ShowNum(10,50,999,3,16,1);
			OLED_Refresh();
			HAL_Delay(500);
			OLED_Clear();
			OLED_ShowChinese(0,0,0,16,1);  //16*16 中
	//	  OLED_ShowChinese(16,0,0,24,1); //24*24 中
	//		OLED_ShowChinese(24,20,0,32,1);//32*32 中
	//	  OLED_ShowChinese(64,0,0,64,1); //64*64 中
	//		OLED_Refresh();
	//	  HAL_Delay(500);
	//  	OLED_Clear();
	//		OLED_ShowString(0,0,"ABC",8,1);//6*8 “ABC”
	//		OLED_ShowString(0,8,"ABC",12,1);//6*12 “ABC”
	//	  OLED_ShowString(0,20,"ABC",16,1);//8*16 “ABC”
	//		OLED_ShowString(0,36,"ABC",24,1);//12*24 “ABC”
			OLED_Refresh();
			HAL_Delay(1500);
			OLED_ScrollDisplay(11,4,1);
		}
	}
}

void Uart_Action(void)
{
		Uart_Init();
	__HAL_UART_ENABLE_IT(&UartHandle, UART_IT_IDLE);
	
	  if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)&value, 1) != HAL_OK)
  {
    printf("something is wrong!\n");
  }
  
  /*##-3- Wait for the end of the transfer ###################################*/   
  /* While waiting for message to come from the other board, LED3 is
     blinking according to the following pattern: a double flash every half-second */  
  while (UartReady != SET)
  {
      printf("I'm waiting for input!\n");
      HAL_Delay(5000); 
  } 
  
  /* Reset transmission flag */
  UartReady = RESET;
	printf("echo completed!  \n %s",aRxBuffer);
}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {

  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {

  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
