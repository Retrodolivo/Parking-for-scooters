#include "nfc.h"

static uint8_t countStepNfc = 0;

static uint8_t success = 0;
static uint8_t uidLength = 0;
static uint8_t uid[7] = {0};

static uint8_t KeyTypeA = 0;
static uint8_t KeyTypeB = 1;
static uint8_t TroykaBlockAddr = 32; // Sector 8, block 0 (block number 32)
static uint32_t troykaserial;

static uint8_t apdusuccess;
static uint32_t cardID;
static uint8_t berBuffer[255];
static uint8_t berLength = 255;
static uint8_t aid[7];
static uint8_t pan[8] = {0x00};
static uint8_t pan_found = 0;
static uint8_t pdol[255];
static uint8_t answer_pdol[255];

//static uint8_t *searchresult; //void

static const uint8_t aid_marker[] = {0x4F, 0x07};
static const uint8_t pan_marker[] = {0x5A, 0x08};
static const uint8_t pan_marker_visa[] = {0x57, 0x13};

uint32_t firmware = 0;

/*********************************************************************
 * Инициализация модуля                                              *
 *********************************************************************/
void nfcInit(void)
{
	firmware = getFirmwareVersion();
	SAMConfig();
}

/*********************************************************************
 * Разрешить работу модуля NFC                                       *
 *********************************************************************/
void nfcStartRun(void)
{
	if(countStepNfc == 0)
	{
		countStepNfc = 1;
	}
}

/*********************************************************************
 * Остановить монуль NFC                                             *
 *********************************************************************/
void nfcStop(void)
{
	countStepNfc = 0;
	cardID = 0;
}

/*********************************************************************
 * Получить ID карты                                                 *
 *********************************************************************/
uint32_t getCardID(void)
{
	return cardID;
}
/*********************************************************************
 * Первые 4 uid                                                 *
 *********************************************************************/
static void uid2cardID(void)
{
	cardID = (uint32_t)uid[0] << 24 |
			 (uint32_t)uid[1] << 16 |
			 (uint32_t)uid[2] << 8  |
			 (uint32_t)uid[3];
}

/*********************************************************************
 * Получение серийного номера карты "Тройка"                         *
 *********************************************************************/
uint32_t gettroykaserial(uint8_t * blockdata)
{

    uint32_t serial_temp;
    // Parse Troyka 10 digits serial number (not UID) that printed on card
    // located from 3 byte up to 4 lower bits of 3 byte
    memcpy(&serial_temp, &(blockdata[3]), 4);
    // Covert MSB to LSB byte order
    serial_temp = ((serial_temp>>24)&0xf0) | // move half from byte 3 to byte 0
                    ((serial_temp<<8)&0xff0000) | // move byte 1 to byte 2
                    ((serial_temp>>8)&0xff00) | // move byte 2 to byte 1
                    ((serial_temp<<24)&0xff000000); // byte 0 to byte 3

    // Shift to half byte to the right
    serial_temp = serial_temp >> 4;
	memcpy(&troykaserial, &serial_temp, 8);
    // Add zero's padding from the left if necessary
    return serial_temp;
}

/*********************************************************************
 * apdu_form                                                         *
 *********************************************************************/
int apdu_form()
{
	uint8_t pdollen = 0;
	uint8_t pdolstart = 0;
	int i;
	for(i=0; i<sizeof(berBuffer); i++)
	{
		if((berBuffer[i]==0x38)&&(berBuffer[i-1]==0x9f))
		{
			pdollen=berBuffer[i+1];
			pdolstart=i+2;
		}
	}
	for(i=0; i<pdollen; i++)
	{
		pdol[i]=berBuffer[i+pdolstart];
	}
	answer_pdol[0]=0x80;
	answer_pdol[1]=0xa8;
	answer_pdol[2]=0x00;
	answer_pdol[3]=0x00;
	answer_pdol[5]=0x83;
	int k=7;
	int z;
	for(z=0; z<pdollen; z++)
	{
		if(pdol[z]==0x9f)
		{
			if(pdol[z+1]==0x66)
			{
				answer_pdol[k]=0x36;
				answer_pdol[k+1]=0xa0;
				answer_pdol[k+2]=0x40;
				answer_pdol[k+3]=0x00;
				k=k+4;
			}
			else if(pdol[z+1]==0x02)
			{
				answer_pdol[k]=0x00;
				answer_pdol[k+1]=0x00;
				answer_pdol[k+2]=0x00;
				answer_pdol[k+3]=0x00;
				answer_pdol[k+4]=0x00;
				answer_pdol[k+5]=0x00;
				k=k+6;
			}
			else if(pdol[z+1]==0x03)
			{
				answer_pdol[k]=0x00;
				answer_pdol[k+1]=0x00;
				answer_pdol[k+2]=0x00;
				answer_pdol[k+3]=0x00;
				answer_pdol[k+4]=0x00;
				answer_pdol[k+5]=0x00;
				k=k+6;
			}
			else if(pdol[z+1]==0x1a)
			{
				answer_pdol[k]=0x06;
				answer_pdol[k+1]=0x43;
				k=k+2;
			}
			else if(pdol[z+1]==0x37)
			{
				answer_pdol[k]=0x00;
				answer_pdol[k+1]=0x00;
				answer_pdol[k+2]=0x00;
				answer_pdol[k+3]=0x00;
				k=k+4;
			}
			else if(pdol[z+1]==0x4e)
			{
        int lenp = pdol[z+2];
				int c;
				for(c=0; c<lenp; c++)
				{
					answer_pdol[k+c]=0x00;
				}
				k=k+lenp;
			}
		}
		else if(pdol[z]==0x95)
		{
				answer_pdol[k]=0x00;
				answer_pdol[k+1]=0x00;
				answer_pdol[k+2]=0x00;
				answer_pdol[k+3]=0x00;
			  answer_pdol[k+4]=0x00;
				k=k+5;
		}
		else if(pdol[z]==0x5f)
		{
			if(pdol[z+1]==0x2a)
			{
				answer_pdol[k]=0x06;
				answer_pdol[k+1]=0x43;
				k=k+2;
			}
		}
		else if(pdol[z]==0x9a)
		{
				answer_pdol[k]=0x00;
				answer_pdol[k+1]=0x00;
			  answer_pdol[k+2]=0x00;
				k=k+3;
		}
		else if(pdol[z]==0x9c)
		{
				answer_pdol[k]=0x00;
				k=k+1;
		}
	}
	answer_pdol[6]=k-7;
	answer_pdol[4]=k-5;
	answer_pdol[k]=0x00;
	return k+1;
}

/*********************************************************************
 * Работа с nfc                                                      *
 *********************************************************************/
void taskNfc(void)
{
	switch(countStepNfc)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			//startGTimer(TIMER_NFC, 10);
			countStepNfc++;
			break;
		}
		case 2:
		{
			//if(getGTimer(TIMER_NFC).stateFlag == fTrue)
			//{
				//SAMConfig();
				success = readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 200);
				/*if(!success)
					success = readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 10);
				if(!success)
					success = readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 10);*/
				/*if(!success)
					success = readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 500);*/
				if (success)
				{
					//display_nfc(1);
					if (uidLength == 7)
					{
						//display_nfc(2);
						// If 7 bytes UID, we probably have a Troyka card
						// TODO: check ATS for detect mifare plus instead of UID length
						uint8_t TroykaKeyA[6] = { 0xA7, 0x3F, 0x5D, 0xC1, 0xD3, 0x33 };
						success = mifareclassic_AuthenticateBlock(uid+3, uidLength - 3, TroykaBlockAddr, KeyTypeA, TroykaKeyA);
						if (success)
						{
						//display_nfc(3);
							uint8_t data[16];
							// Try to read content of block 32 (sector 8 block 0)
							success = mifareclassic_ReadDataBlock(TroykaBlockAddr, data);
							// Extract Troyka serial from block data
							cardID =  gettroykaserial(data);
							//card_lock();
							//HAL_Delay(2000);
						} // end of if (success)
						else
						{
							uint8_t apdu[] = {0x00, 0xA4, 0x04, 0x00, 0x0e, 0x32, 0x50, 0x41, 0x59, 0x2e, 0x53, 0x59, 0x53, 0x2e, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};
							apdusuccess = inDataExchange(apdu, sizeof(apdu), berBuffer, &berLength);
							if (apdusuccess)
							{
								//display_nfc(3);
								if (berLength > 10)
								{
									uint8_t* tempbuf[2];
									if (2 < berLength)
									{
										int i;
										for (i=0; i<berLength-3; i++)
										{
											memcpy(&tempbuf,&berBuffer[i],2);
											if (memcmp(&tempbuf,aid_marker,2)==0)
											{
												//memcpy(&searchresult,&berBuffer[i],berLength-i);
												memcpy(&aid, &berBuffer[i+2], 7);
											}
										}
									}
								}
								// Now start application on card (AID)
								uint8_t startAID[] = {0x00, 0xa4, 0x04, 0x00, 0x07, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
								memcpy(&startAID[5], &aid, 7);
								berLength = 255;
								apdusuccess = inDataExchange(startAID, sizeof(startAID), berBuffer, &berLength);
								memset(pan, 0x00, 8);
								pan_found = 0;
								int apdulen=apdu_form();
								uint8_t apdu3[apdulen];
								int k;
								for(k=0;k<apdulen;k++)
								{
									apdu3[k]=answer_pdol[k];
								}
								berLength = 255;
								apdusuccess = inDataExchange(apdu3, sizeof(apdu3), berBuffer, &berLength);
								if (!pan_found)
								{
									//void * searchresult;
									uint8_t* temppanbuf[2];
									if (2 < berLength)
									{
										int i;
										for (i=0; i<berLength-3; i++)
										{
											memcpy(&temppanbuf,&berBuffer[i],2);
											if (memcmp(&temppanbuf,pan_marker_visa,2)==0)
											{
												//memcpy(&searchresult,&berBuffer[i],berLength-i);
												for(uint8_t j=0; j<8; j++)
												{
													pan[j] = berBuffer[i+2+j];
												}
												pan_found = 1;
											}
										}
									}
								}
								if (pan_found)
								{
									//display_nfc(4);
									char strpan[8];
									for (int i = 4; i < 8; i++)
									{
										char str[2];
										sprintf(str, "%02x", pan[i]);
										memcpy(&strpan[(i-4)*2],&str,2);
									}
									cardID = (uint32_t)atol(strpan);
									memcpy(&strpan,&strpan,2);
									//card_lock();
									//HAL_Delay(2000);
								}
							}
							else
							{
								uid2cardID();
							}
						}

						//ClearDisplay();
						//display_header_exept(0);
						//cell_selected=0;
						//checkdiod();
					} // end of if (uidLength == 7)
					else if (uidLength == 4)
					{
						if((uid[0]==0xF3)&&(uid[1]==0xB9)&&(uid[2]==0x00)&&(uid[3]==0x0B))
						{
							//card_lock();
							//HAL_Delay(2000);
						}
						uint8_t apdu[] = {0x00, 0xA4, 0x04, 0x00, 0x0e, 0x32, 0x50, 0x41, 0x59, 0x2e, 0x53, 0x59, 0x53, 0x2e, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};
						apdusuccess = inDataExchange(apdu, sizeof(apdu), berBuffer, &berLength);
						if (apdusuccess)
						{
							//display_nfc(2);
							if (berLength > 10)
							{
								uint8_t* tempbuf[2];
								if (2 < berLength)
								{
									int i;
									for (i=0; i<berLength-3; i++)
									{
										memcpy(&tempbuf,&berBuffer[i],2);
										if (memcmp(&tempbuf,aid_marker,2)==0)
										{
											//memcpy(&searchresult,&berBuffer[i],berLength-i);
											memcpy(&aid, &berBuffer[i+2], 7);
										}
									}
								}
							}
							// Now start application on card (AID)
							uint8_t startAID[] = {0x00, 0xa4, 0x04, 0x00, 0x07, 0xa0, 0x0, 0x0, 0x0, 0x00, 0x00, 0x00, 0x00};
							memcpy(&startAID[5], &aid, 7);
							berLength = 255;
							apdusuccess = inDataExchange(startAID, sizeof(startAID), berBuffer, &berLength);
							memset(pan, 0x00, 8);
							pan_found = 0;
							int apdulen=apdu_form();
							uint8_t apdu5[apdulen];
							int k;
							for(k=0;k<apdulen;k++)
							{
								apdu5[k]=answer_pdol[k];
							}
							uint8_t berLength = 255;
							//display_nfc(3);
							apdusuccess = inDataExchange(apdu5, sizeof(apdu5), berBuffer, &berLength);
							if (!pan_found)
							{
								//void * searchresult;
								uint8_t* temppanbuf[2];
								if (2 < berLength)
								{
									int i;
									for (i=0; i<berLength-3; i++)
									{
										memcpy(&temppanbuf,&berBuffer[i],2);
										if (memcmp(&temppanbuf,pan_marker_visa,2)==0)
										{
											//memcpy(&searchresult,&berBuffer[i],berLength-i);
											for(uint8_t j=0; j<8; j++)
											{
												pan[j] = berBuffer[i+2+j];
											}
											pan_found = 1;
										}
									}
								}
							}
							if (!pan_found)
							{
								uint8_t apdu3[] = {0x00, 0xb2, 0x01, 0x14, 0x00};
								berLength = 255;
								apdusuccess = inDataExchange(apdu3, sizeof(apdu3), berBuffer, &berLength);
								//void * searchresult;
								uint8_t* temppanbuf[2];
								if (2 < berLength)
								{
									int i;
									for (i=0; i<berLength-3; i++)
									{
										memcpy(&temppanbuf,&berBuffer[i],2);
										if (memcmp(&temppanbuf,pan_marker,2)==0)
										{
											//memcpy(&searchresult,&berBuffer[i],berLength-i);
											for(uint8_t j=0; j<8; j++)
											{
												pan[j] = berBuffer[i+2+j];
											}
											pan_found = 1;
										}
									}
								}
							}
							if (!pan_found)
							{
								uint8_t apdu4[] = {0x00, 0xb2, 0x02, 0x14, 0x00};
								berLength = 255;
								apdusuccess = inDataExchange(apdu4, sizeof(apdu4), berBuffer, &berLength);
								//void * searchresult;
								uint8_t* temppanbuf[2];
								if (2 < berLength)
								{
									int i;
									for (i=0; i<berLength-3; i++)
									{
										memcpy(&temppanbuf,&berBuffer[i],2);
										if (memcmp(&temppanbuf,pan_marker,2)==0)
										{
											//memcpy(&searchresult,&berBuffer[i],berLength-i);
											for(uint8_t j=0; j<8; j++)
											{
												pan[j] = berBuffer[i+2+j];
											}
											pan_found = 1;
										}
									}
								}
							}
							if (pan_found)
							{
								//display_nfc(4);
								char strpan[8];
								for (int i = 4; i < 8; i++)
								{
									char str[2];
									sprintf(str, "%02x", pan[i]);
									memcpy(&strpan[(i-4)*2],&str,2);
								}
								cardID = (uint32_t)atol(strpan);
								memcpy(&strpan,&strpan,2);
								//card_lock();
								//HAL_Delay(2000);
							}
						}
						else
						{
							uid2cardID();
							//HAL_Delay(2000);
						}
						//ClearDisplay();
						//display_header_exept(0);
						//cell_selected=0;
						//checkdiod();
					}
				}
				startGTimer(TIMER_NFC, 30);
				countStepNfc++;
			//}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_NFC).stateFlag == fTrue)
			{
				countStepNfc = 2;
			}
			break;
		}
	}
}
