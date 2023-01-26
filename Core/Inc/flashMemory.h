#ifndef _FLASHMEMORY_H
#define _FLASHMEMORY_H

#include "main.h"
#include "bitOperations.h"

uint8_t flashErasePage(uint32_t address); // ������� �������� ����
uint8_t flashWriteWord(uint32_t address, uint32_t data); // ������ � ����
uint8_t flashWrite_16(uint32_t address, uint16_t data); // ������ 16 ��� � ����.
uint8_t flashRead_8(uint32_t address); // ������ 8 ��� ������ �� ����
uint16_t flashRead_16(uint32_t address); // ������ 16 ��� ������ �� ����
uint32_t flashReadWord(uint32_t address); // ������ ������ �� ����
void flashReadDataWord(uint32_t startAddresData, uint32_t *buffer, uint32_t lenght); // ������ ������ ������� � lenght ����  �� FLASH
uint8_t flashWriteDataWord(uint32_t address, uint32_t *data, uint16_t lenght); // ������ ������ ������� lenght � ����. ������ ������� �� 16 ���

#endif
