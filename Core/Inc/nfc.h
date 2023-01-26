#ifndef _NFC_H
#define _NFC_H

#include "main.h"
#include "PN532.h"

void nfcInit(void); 		// ������������� ������
void nfcStartRun(void); 	// ��������� ������ ������ NFC
void nfcStop(void);			// ���������� ������ NFC
uint32_t getCardID(void);	// �������� ID �����

void taskNfc(void); // ������ � nfc

#endif
