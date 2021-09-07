
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


//�������ݽ��ջ���
uint8_t getBuffer[255];
uint8_t value;//�����жϴ�������������Ϣ,getBuffer[0]��ֵ
uint8_t frameSize;//�Ӵ����յ��ı��ľ��峤��



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
H����Ϊ�������룬���������룬L����Ϊ�������
*/


int main(void)
{

	
	
	
	u8 t=' ';
//	const char* x="��";
	HAL_Init();//��ʼ��ϵͳ�жϣ�ʱ�ӵȵײ�Ӳ����Դ��ϵͳ�Դ�
	SystemClock_Config();//��ʼ��CPU��AHB��APB������ʱ�ӣ�ϵͳ�Դ�
	Uart_Init();//��ʼ�����ڲ������粨���ʣ����Զ��壬PA9����-PA10���գ���ʼ��
	Spi_Init();//��ʼ��SPI����Ҫ�����ֿ�ķ��ʣ�����������źͲ�������Ҫ��PA5-7������ʱ�ӣ�MOSI��MISO���Զ���
	Timer_Init();//��ʼ����ʱ�����Զ���
//while(1){
//	printf("system core clock is %d",SystemCoreClock);
//}
//	char buf[20];
//	
//	printf("hello�й���");
//	sprintf(buf,"%s","��");
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
	OLED_Init();	//��ʼ��IICͨ������pin��PA2-RES,PB6-CLK,PB7-DIN��֮�������oled����һϵ�п������ȷ���ܵ�����
	
	UG_Init(&gui1309, Display_PSet, DISPLAY_WIDTH, DISPLAY_HEIGHT);//��ʼ��ugui�⣬�ؼ�������Display_PSet������ʵ�ֻ��㣨����OLED_DrawPoint��ʵ����ֻ���Դ棬����ug��������ˢ�²����������㣩
	Keypad_Init();//��ʼ��������̣�H-PA1��PA8��PB1��L-PA0��PA3��PB3��Щ������Ҫ��ʼ��
	//UG_FillScreen(0);
	
	//mc.currWnd =CreateWindow_SetTime();
	//mc.currWnd=CreateWindow_MainMenu();//���崰���С���������ݣ��ؼ����ݼ���ʾλ�ã����øô���Ϊ��Ҫ��ʾ�Ĵ��壬���ô�������봦����
	mc.currWnd=CreateWindow_Popup();

    UG_Update();//1.���Դ����ػ������Է�ӳǰ����Դ��������ĸ��ģ�2.���õ�ǰ����Ĵ�����ProcessInputData�Դ�������յ�������
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
u8 chr[]="�����hello";
u8 pBuff1[32];
//			ASCII_GetData('H',ASCII_6X12,pBuff1);//��ȡ6X12���� ASCII ����A�ĵ������ݣ������������ݴ���pBuff�����У����ݳ���Ϊ12 BYTE
//			OLED_ShowASCIIFromBuff(10,20,1,pBuff1);
			//gt_16_GetData(0xb0,0xa1,pBuff1); //��ȡ12X12�����֡������ĵ������ݣ������������ݴ���DZ_Data�����У����ݳ���Ϊ24 BYTE
			//OLED_ShowChineseFromBuff(10,20,16,1,pBuff1);
//GB2312_16_GetData_v2(*chr,*(chr+1),pBuff);
//OLED_ShowChineseFromBuff(10,20,16,1,pBuff);

		//r_dat_bat(0x3b7c0,12,pBuff1);
//		OLED_ShowString(10,20,chr,WORD_SIZE,1);
		//UG_PutString(10,20,"hello");
		//HAL_Delay(5000);
		OLED_Refresh();//����Ӳ��ָ��ˢ��oled�������Դ��е�����������ʾ��oled����
					//GetKey();
/*
��������������ڲ���������ķ����뺯��
static void _build(void *handler, uint8_t type, uint8_t command, uint8_t *payload, uint8_t size, struct StreamBuffer *buffer)
���¹���һ�����������ص�10���ֽڵı��ģ��鿴��buffer.buffer[0->9]

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
//1-2�ֽ�Ϊ��ͷ��3-���ͣ�4-����5-���6-���س��ȣ�����3-4crc������1-2��β
/*
�������������
*/


		while(1){

		while(!value){}//��û���κ�����ʱ��ѭ���������������жϴ�����SysTick_Handler
			if(mc.currWnd){
				CX_InputUpdate(value);//����valueֵ����gui->input����,value�����������������жϴ�����SysTick_Handler�������ð���ֵ��HAL_TIM_PeriodElapsedCallback�������ù����˸ֵ��USART2_IRQHandler�������ô�������
				value='\0';
				UG_Update();//����gui->input���ݣ��Դ�Ϊ���ݸ��Ĵ�������
				OLED_Refresh();	//�����Դ�ˢ��oled����ʾ����				
				
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
//�ڴ��ڶ˵ȴ����룬������ʱһֱ��ӡ�ȴ���Ϣ������������������ӡ�������ݲ��˳�
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
