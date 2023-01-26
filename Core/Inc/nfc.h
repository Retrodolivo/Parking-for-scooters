#ifndef _NFC_H
#define _NFC_H

#include "main.h"
#include "PN532.h"

void nfcInit(void); 		// Инициализация модуля
void nfcStartRun(void); 	// Разрешить работу модуля NFC
void nfcStop(void);			// Остановить монуль NFC
uint32_t getCardID(void);	// Получить ID карты

void taskNfc(void); // Работа с nfc

#endif
