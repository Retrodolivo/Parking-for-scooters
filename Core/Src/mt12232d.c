#include "mt12232d.h"


/*********************************************************************
 * �������� ���� � ����                                              *
 *********************************************************************/
void sendData(uint8_t data)
{
	if((data & 0x01) != 0) LL_GPIO_SetOutputPin(LCD_DB0_GPIO_Port, LCD_DB0_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB0_GPIO_Port, LCD_DB0_Pin);
	if((data & 0x02) != 0) LL_GPIO_SetOutputPin(LCD_DB1_GPIO_Port, LCD_DB1_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB1_GPIO_Port, LCD_DB1_Pin);
	if((data & 0x04) != 0) LL_GPIO_SetOutputPin(LCD_DB2_GPIO_Port, LCD_DB2_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB2_GPIO_Port, LCD_DB2_Pin);
	if((data & 0x08) != 0) LL_GPIO_SetOutputPin(LCD_DB3_GPIO_Port, LCD_DB3_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB3_GPIO_Port, LCD_DB3_Pin);
	if((data & 0x10) != 0) LL_GPIO_SetOutputPin(LCD_DB4_GPIO_Port, LCD_DB4_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB4_GPIO_Port, LCD_DB4_Pin);
	if((data & 0x20) != 0) LL_GPIO_SetOutputPin(LCD_DB5_GPIO_Port, LCD_DB5_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB5_GPIO_Port, LCD_DB5_Pin);
	if((data & 0x40) != 0) LL_GPIO_SetOutputPin(LCD_DB6_GPIO_Port, LCD_DB6_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB6_GPIO_Port, LCD_DB6_Pin);
	if((data & 0x80) != 0) LL_GPIO_SetOutputPin(LCD_DB7_GPIO_Port, LCD_DB7_Pin);
	else
		LL_GPIO_ResetOutputPin(LCD_DB7_GPIO_Port, LCD_DB7_Pin);
}

/*********************************************************************
 * �������� ���� � LCD                                               *
 *********************************************************************/
void writeByte(uint8_t data, int cd, int lr)
{
	LL_GPIO_ResetOutputPin(LCD_R_W_GPIO_Port, LCD_R_W_Pin);
	if(cd == 0)
	{
		LL_GPIO_ResetOutputPin(LCD_A0_GPIO_Port, LCD_A0_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LCD_A0_GPIO_Port, LCD_A0_Pin);
	}
	if(lr == 0)
	{
		LL_GPIO_ResetOutputPin(LCD_CS_GPIO_Port, LCD_CS_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LCD_CS_GPIO_Port, LCD_CS_Pin);
	}
	LL_GPIO_ResetOutputPin(LCD_ES_GPIO_Port, LCD_ES_Pin);
	sendData(data);
	LL_GPIO_SetOutputPin(LCD_ES_GPIO_Port, LCD_ES_Pin);
}

/*********************************************************************
 * �������� ������� � ����� �������� ����������                      *
 *********************************************************************/
void writeCodeL(uint8_t data)
{
	writeByte(data, 0, 1);
}

/*********************************************************************
 * �������� ������� � ������ �������� ����������                     *
 *********************************************************************/
void writeCodeR(uint8_t data)
{
	writeByte(data, 0, 0);
}

/*********************************************************************
 * �������� ������ � ����� �������� ����������                       *
 *********************************************************************/
void writeDataL(uint8_t data)
{
	writeByte(data, 1, 1);
}

/*********************************************************************
 * �������� ������ � ������ �������� ����������                      *
 *********************************************************************/
void writeDataR(uint8_t data)
{
	writeByte(data ,1 ,0);
}

/*********************************************************************
 * �������� LCD                                                      *
 *********************************************************************/
void clearLcd(void)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		writeCodeL(i|0xB8);
		writeCodeL(0x13);
		for(uint8_t j = 0; j < 61; j++)
		{
			writeDataL(0x00);
		}
		writeCodeR(i|0xB8);
		writeCodeR(0x00);
		for(uint8_t j = 61; j < 122; j++)
		{
			writeDataR(0x00);
		}
	}
}

/*********************************************************************
 * ������������� LCD                                                 *
 *********************************************************************/
void initLcd(void)
{
	LL_GPIO_SetOutputPin(LCD_ES_GPIO_Port, LCD_ES_Pin); // ��������� �������� ������� ����������
	LL_GPIO_ResetOutputPin(LCD_RES_GPIO_Port, LCD_RES_Pin); // ������ ������ RES=0 ����������
	HAL_Delay(1);
	LL_GPIO_SetOutputPin(LCD_RES_GPIO_Port, LCD_RES_Pin); //LCD.RES=1;//����� ������ RES
	HAL_Delay(2);
	writeCodeL(0xE2);//Reset
	writeCodeR(0xE2);//Reset
	writeCodeL(0xEE);//ReadModifyWrite off
	writeCodeR(0xEE);//ReadModifyWrite off
	writeCodeL(0xA4);//�������� ������� �����
	writeCodeR(0xA4);//�������� ������� �����
	writeCodeL(0xA9);//����������� 1/32
	writeCodeR(0xA9);//����������� 1/32
	writeCodeL(0xC0);//������� ������ �� 0
	writeCodeR(0xC0);//������� ������ �� 0
	writeCodeL(0xA1);//Invert scan RAM
	writeCodeR(0xA0);//NonInvert scan RAM
	writeCodeL(0xAF);//Display on
	writeCodeR(0xAF);//Display on
	clearLcd();
}
