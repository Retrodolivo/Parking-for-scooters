#include <flashMemory.h>

/*********************************************************************
 * �������������� ���� ��� ������                                    *
 *********************************************************************/
void flashUnlock(void)
{
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
}

/*********************************************************************
 * ������������� ���� ��� ������                                     *
 *********************************************************************/
void flashLock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}

/*********************************************************************
 * �������� ��������� ���� FALSE - ������                            *
 *********************************************************************/
uint8_t flasReady(void)
{
	return !(FLASH->SR & FLASH_SR_BSY);
}

/*********************************************************************
 * �������� ��������� ��������                                       *
 *********************************************************************/
uint8_t flasCheckEOP(void)
{
	if(FLASH->SR & FLASH_SR_EOP)
	{
		FLASH->SR |= FLASH_SR_EOP;
		return TRUE;
	}
	return FALSE;
}

/*********************************************************************
 * ������� �������� ����                                             *
 *********************************************************************/
uint8_t flashErasePage(uint32_t address)
{
	while(!flasReady());
	flashUnlock();
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = address;
	FLASH->CR |= FLASH_CR_STRT;
	while(!flasReady());
	FLASH->CR &= ~FLASH_CR_PER;
	flashLock();
	return flasCheckEOP();
}

/*********************************************************************
 * ������ ������ ����� � ����. ������ ������� �� 16 ���              *
 *********************************************************************/
uint8_t flashWriteWord(uint32_t address, uint32_t data)
{
	while(!flasReady());
	flashUnlock();
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint16_t*)address = (uint16_t)data;
	while(!flasReady());
	if(!flasCheckEOP()) return FALSE;
	address += 2;
	*(__IO uint16_t*)address = (uint16_t)(data >> 16);
	while(!flasReady());
	FLASH->CR &= ~(FLASH_CR_PG);
	flashLock();
	return flasCheckEOP();
}

/*********************************************************************
 * ������ 16 ��� � ����.                                             *
 *********************************************************************/
uint8_t flashWrite_16(uint32_t address, uint16_t data)
{
	while(!flasReady());
	flashUnlock();
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint16_t*)address = (uint16_t)data;
	while(!flasReady());
	FLASH->CR &= ~(FLASH_CR_PG);
	flashLock();
	return flasCheckEOP();
}

/*********************************************************************
 * ������ ������ ������� lenght � ����. ������ ������� �� 16 ���     *
 *********************************************************************/
uint8_t flashWriteDataWord(uint32_t address, uint32_t *data, uint16_t lenght)
{
	while(lenght)
	{
		if(!flashWriteWord(address, *data)) return FALSE;
		data++;
		address += 4;
		lenght--;
	}
	return TRUE;
}

/*********************************************************************
 * ������ 8 ��� ������ �� ����                                       *
 *********************************************************************/
uint8_t flashRead_8(uint32_t address)
{
	return (*(__IO uint8_t*) address);
}

/*********************************************************************
 * ������ 16 ��� ������ �� ����                                       *
 *********************************************************************/
uint16_t flashRead_16(uint32_t address)
{
	return (*(__IO uint16_t*) address);
}

/*********************************************************************
* ������ ������ �� ����                                             *
*********************************************************************/
uint32_t flashReadWord(uint32_t address)
{
	return (*(__IO uint32_t*) address);
}

/************************************************************************/
/* ������ ������ ������� � lenght ����  �� FLASH                        */
/************************************************************************/
void flashReadDataWord(uint32_t startAddresData, uint32_t *buffer, uint32_t lenght)
{
	uint32_t temp;
	while(lenght)
	{
		temp = (*(__IO uint32_t *)startAddresData);
		*buffer = temp;
		startAddresData += 4;
		buffer++;
		lenght--;
	}
}
