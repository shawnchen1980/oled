#include "main.h"
#include "my_hal_spi.h"

#define CHARLIB_CS_PORT GPIOB
#define CHARLIB_CS_PIN GPIO_PIN_0


extern SPI_HandleTypeDef SpiHandle;
static void SPI_Address(unsigned char AddH,unsigned char AddM,unsigned char AddL);
//uint8_t pBuff[32];//32 BYTES FOR 16*16 BIT
/**
  * @brief  Receive an amount of data in blocking mode 
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be sent
  * @param  Timeout: Timeout duration
  * @retval HAL status

HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
  */
	
	/**
  * @brief  Transmit an amount of data in blocking mode
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be sent
  * @param  Timeout: Timeout duration
  * @retval HAL status
	HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
  */
/*******************************************************************************/
//                    Get N bytes sub-pro  (STM8,STM32��51)                                    //
/*******************************************************************************/
//�ͻ��Լ�ʵ�֣���address��ַ��ȡlen���ֽڵ����ݲ����뵽DZ_Data���鵱��
unsigned long r_dat_bat(unsigned long address,unsigned long DataLen,unsigned char *pBuff)
{
	unsigned long i;
	

	unsigned char addrHigh;
	unsigned char addrMid;
	unsigned char addrLow;
	unsigned char com=0x03;
	
	addrHigh=address>>16;
	addrMid=address>>8;
	addrLow=(unsigned char)address;

//	Rom_csL;          //Ƭѡѡ���ֿ�оƬ
	HAL_GPIO_WritePin(CHARLIB_CS_PORT, CHARLIB_CS_PIN, GPIO_PIN_RESET); // command
	HAL_SPI_Transmit(&SpiHandle,&com,1,0xffff);
	//SPI1_ReadWriteByte(0x03);	//��ͨ��ȡ������0X03,Ȼ���͵�ַ�߰�λaddrHigh���а�λaddrMid���Ͱ�λaddrLow��
	SPI_Address(addrHigh,addrMid,addrLow);	

//	for(i=0;i<DataLen;i++)
//	*(pBuff+i)=SPI1_ReadWriteByte(0x00);
	HAL_SPI_Receive(&SpiHandle,pBuff,DataLen,0xffff);

	//Rom_csH;
	HAL_GPIO_WritePin(CHARLIB_CS_PORT, CHARLIB_CS_PIN, GPIO_PIN_SET); // command
	return i;
}
/*******************************/
static void SPI_Address(unsigned char AddH,unsigned char AddM,unsigned char AddL) 
{
	HAL_SPI_Transmit(&SpiHandle,&AddH,1,0xffff);
	HAL_SPI_Transmit(&SpiHandle,&AddM,1,0xffff);
	HAL_SPI_Transmit(&SpiHandle,&AddL,1,0xffff);
//	SPI1_ReadWriteByte(AddH);
//	SPI1_ReadWriteByte(AddM);
//	SPI1_ReadWriteByte(AddL);
}