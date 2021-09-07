
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
#include "wnd_popup.h"
#include "keypad.h"

//unsigned long GB2312_16_GetData_v2( unsigned char MSB,unsigned char LSB , unsigned char * DZ_Data);


extern __IO ITStatus UartReady;
extern UART_HandleTypeDef UartHandle;
uint8_t pBuff[25];


//串口数据接收缓存
uint8_t getBuffer[255];
uint8_t value;//来自中断处理函数传来的消息,getBuffer[0]的值
uint8_t frameSize;//从串口收到的报文具体长度



/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****UART_TwoBoards_ComIT****  ****UART_TwoBoards_ComIT****  ****UART_TwoBoards_ComIT**** ";

/* Buffer used for reception */
uint8_t aRxBuffer[255];


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
	HAL_Init();//初始化系统中断，时钟等底层硬件资源，系统自带
	SystemClock_Config();//初始化CPU、AHB、APB等总线时钟，系统自带
	Uart_Init();//初始化串口参数（如波特率），自定义，PA9发送-PA10接收，初始化
	Spi_Init();//初始化SPI，主要用于字库的访问，配置相关引脚和参数，主要是PA5-7，包括时钟，MOSI和MISO，自定义
	Timer_Init();//初始化定时器，自定义
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
	OLED_Init();	//初始化IIC通信三个pin，PA2-RES,PB6-CLK,PB7-DIN，之后是针对oled屏的一系列开启命令，确保能点亮屏
	
	UG_Init(&gui1309, Display_PSet, DISPLAY_WIDTH, DISPLAY_HEIGHT);//初始化ugui库，关键是设置Display_PSet函数，实现画点（调用OLED_DrawPoint，实际上只改显存，调用ug函数后还需刷新才能真正画点）
	Keypad_Init();//初始化矩阵键盘，H-PA1，PA8，PB1，L-PA0，PA3，PB3这些引脚需要初始化
	//UG_FillScreen(0);
	
	//mc.currWnd =CreateWindow_SetTime();
	//mc.currWnd=CreateWindow_MainMenu();//定义窗体大小，标题内容，控件内容及显示位置，设置该窗体为将要显示的窗体，设置窗体的输入处理函数
	mc.currWnd=CreateWindow_Popup();

    UG_Update();//1.在显存中重画窗体以反映前面针对窗体所作的更改，2.调用当前窗体的处理函数ProcessInputData以处理窗体接收到的命令
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
//		OLED_ShowString(10,20,chr,WORD_SIZE,1);
		//UG_PutString(10,20,"hello");
		//HAL_Delay(5000);
		OLED_Refresh();//调用硬件指令刷新oled屏，将显存中的内容真正显示到oled屏上
					//GetKey();
/*
代码测试区，用于测试新引入的方法与函数
static void _build(void *handler, uint8_t type, uint8_t command, uint8_t *payload, uint8_t size, struct StreamBuffer *buffer)
以下构造一个不包含负载的10个字节的报文，查看从buffer.buffer[0->9]

struct StreamBuffer buffer;

stream_frame_type *handler= stream_frame_create_handler();
handler->ops->init(handler);
uint8_t type=0x01;
uint8_t command=0x02;
uint8_t size=0;
uint8_t *payload=0;
handler->ops->build(handler,type,command,payload,size,&buffer);
buffer.buffer[100]=0;
uint8_t sample[10]={58 4A 01 01 02 00 27 e6 ee ee};
//1-2字节为包头，3-类型，4-方向，5-命令，6-负载长度，倒数3-4crc，倒数1-2包尾
/*
代码测试区结束
*/


		while(1){

		while(!value){}//当没有任何输入时死循环，输入来自于中断处理函数SysTick_Handler
			if(mc.currWnd){
				CX_InputUpdate(value);//根据value值设置gui->input内容,value的设置来自于三个中断处理函数SysTick_Handler负责设置按键值，HAL_TIM_PeriodElapsedCallback负责设置光标闪烁值，USART2_IRQHandler负责设置串口输入
				value='\0';
				UG_Update();//处理gui->input数据，以此为依据更改窗体内容
				OLED_Refresh();	//根据显存刷新oled屏显示内容				
				
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
	
}
//在串口端等待输入，无输入时一直打印等待信息（阻塞），有输入后打印输入内容并退出
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
