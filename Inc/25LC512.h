#ifndef __25LC512_H
#define __25LC512_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"


/*EEProm Definitions */
#define MC25LCxxx_SPI_READ 		0x03 	//0000 0011 Read data from memory array beginning at selected address
#define MC25LCxxx_SPI_WRITE 	0x02  //0000 0010 Write data to memory array beginning at selected address
#define MC25LCxxx_SPI_WREN 		0x06	//0000 0110 Set the write enable latch (enable write operations)
#define MC25LCxxx_SPI_WRDI 		0x04	//0000 0100 Reset the write enable latch (disable write operations)
#define MC25LCxxx_SPI_RDSR 		0x05	//0000 0101 Read STATUS register
#define MC25LCxxx_SPI_WRSR 		0x01	//0000 0001 Write STATUS register
#define MC25LCxxx_SPI_PE 			0x42	//0100 0010 Page Erase – erase one page in memory array
#define MC25LCxxx_SPI_SE 			0xD8	//1101 1000 Sector Erase – erase one sector in memory array
#define MC25LCxxx_SPI_CE 			0xC7	//1100 0111 Chip Erase – erase all sectors in memory array
#define MC25LCxxx_SPI_RDID 		0xAB	//1010 1011 Release from Deep power-down and read electronic signature
#define MC25LCxxx_SPI_DPD 		0xB9	//1011 1001 Deep Power-Down mode

#define MC25LCxxx_STATUS_WPEN	0x80  //Read Write Array Address Write Protect Bit 1
#define MC25LCxxx_STATUS_BP1	0x08	//Read Write Array Address Write Protect Bit 1
#define MC25LCxxx_STATUS_BP0	0x04	//Read Write Array Address Write Protect Bit 0
#define MC25LCxxx_STATUS_WEL	0x02	//Read only Write Enable Latch
#define MC25LCxxx_STATUS_WIP	0x01	//Read only Write In Process 

#define EEPROM_Enable 1
#define EEPROM_Disable 0
#define EEPROM_CS_PIN_SET 1
#define EEPROM_CS_PIN_RESET 0
//extern unsigned char Enable,Disable;

class 	EEPROM{

	public:
		EEPROM(SPI_HandleTypeDef *hspi_,GPIO_TypeDef *GPIOx_,uint16_t GPIO_Pin_);
		~EEPROM(){};
		
		void MC25LC512_Initilize(void);
		void MC25LC512_Write(uint16_t AddresOfData, unsigned char *WriteArrayOfEEProm,unsigned short SizeOfArray);
		void MC25LC512_Write(uint16_t AddresOfData, unsigned short *WriteArrayOfEEProm,unsigned short sizeOfArray);
		void MC25LC512_Write(uint16_t AddresOfData, unsigned int *WriteArrayOfEEProm,unsigned short sizeOfArray);
			
		unsigned char MC25LC512_ReadStatusRegister(void);		
		unsigned char MC25LC512_Read(uint16_t AddresOfData, unsigned char *DataArrayOfEEProm,unsigned short SizeOfArray);	
		unsigned char MC25LC512_Read(uint16_t AddresOfData, unsigned short *DataArrayOfEEProm,unsigned short SizeOfArray);	
		unsigned char MC25LC512_Read(uint16_t AddresOfData, unsigned int *DataArrayOfEEProm,unsigned short SizeOfArray);	
			
		private:
		void MC25LC512_CS(unsigned char CS_Status);
		void MC25LC512_WriteEnableOrDisable(unsigned char EnableOrDisable);
		unsigned char MC25LC512_ReleaseDeepPowerDownMode(void);
		
		SPI_HandleTypeDef *hspi_eeprom;	
		GPIO_TypeDef *GPIOx_Port_eeprom;
		uint16_t GPIO_Pin_eeprom;
};



#ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */


