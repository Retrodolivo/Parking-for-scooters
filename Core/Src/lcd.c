#include "lcd.h"

// Маленькие цифры для вывода в область hider
static const uint8_t null_small[3] = {0x3e,0x22,0x3e};
static const uint8_t one_small[2] = {0x04,0x3e};
static const uint8_t two_small[3] = {0x3a,0x2a,0x2e};
static const uint8_t three_small[3] = {0x22,0x2a,0x36};
static const uint8_t four_small[3] = {0x0e,0x08,0x3e};
static const uint8_t five_small[3] = {0x2e,0x2a,0x3a};
static const uint8_t six_small[3] = {0x3c,0x2a,0x3a};
static const uint8_t seven_small[3] = {0x32,0x0a,0x06};
static const uint8_t eight_small[3] = {0x3e,0x2a,0x3e};
static const uint8_t nine_small[3] = {0x2e,0x2a,0x3e};
// Значек замка маленькийд ля вывода в область hider
static const uint8_t lock_small[5] = {0x38,0x3e,0x3a,0x3e,0x38};
// Значек замка инвертированный маленькийд для вывода в область hider
static const uint8_t lock_small_inv[5] = {0x47,0x41,0x45,0x41,0x47};

static const uint8_t one_small_pos[20] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t two_small_pos[20] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3A,0x2A,0x2E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t three_small_pos[20] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,0x2a,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t four_small_pos[20] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t five_small_pos[20] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2e,0x2a,0x3a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

// Маленькие цифры инвертированные для вывода в область hider
static const uint8_t one_small_inv[20] = {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7b,0x41,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f};
static const uint8_t two_small_inv[20] = {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x45,0x55,0x51,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f};
static const uint8_t three_small_inv[20] = {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x5d,0x55,0x49,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f};
static const uint8_t four_small_inv[20] = {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x71,0x77,0x41,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f};
static const uint8_t five_small_inv[20] = {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x51,0x55,0x45,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f};

static const uint8_t null[3][14] = {{0xf8,0xfc,0xfe,0xff,0x1f,0x0f,0x0f,0x0f,0x0f,0x1f,0xff,0xfe,0xfc,0xf8},
									{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
									{0x1f,0x3f,0x7f,0xff,0xf8,0xf0,0xf0,0xf0,0xf0,0xf8,0xff,0x7f,0x3f,0x1f}};
static const uint8_t one[3][14] = {{0x00,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff,0xff,0x00,0x00,0x00,0x00,0x00},
									{0x00,0x01,0x01,0x01,0x01,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00},
									{0xf0,0xf0,0xf0,0xf0,0xf0,0xff,0xff,0xff,0xff,0xf0,0xf0,0xf0,0xf0,0xf0}};
static const uint8_t two[3][14] = {{0x00,0x78,0x7c,0x7e,0x7f,0x1f,0x1f,0x1f,0x1f,0x3f,0xfe,0xfe,0xfc,0xf0},
									{0x00,0x00,0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0x7e,0x3f,0x1f,0x0f,0x03},
									{0xfc,0xfe,0xff,0xff,0xff,0xf7,0xf3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0}};
static const uint8_t three[3][14] = {{0x00,0x0f,0x0f,0x0f,0x0f,0x8f,0xcf,0xef,0xff,0xff,0x7f,0x3f,0x1f,0x00},
										{0x00,0x00,0x0c,0x0e,0x0f,0x0f,0x0f,0x1f,0x1f,0x3e,0xfe,0xfc,0xf8,0xf0},
										{0x0e,0x1e,0x3e,0x7e,0x78,0xf0,0xf0,0xf0,0xf8,0x7e,0x7f,0x3f,0x0f,0x07}};
static const uint8_t four[3][14] = {{0x00,0x00,0x00,0x00,0x00,0xc0,0xf0,0xfc,0xff,0xff,0xff,0xff,0x00,0x00},
									{0x00,0xc0,0xf0,0xfc,0xff,0xcf,0xc3,0xc0,0xff,0xff,0xff,0xff,0xc0,0x00},
									{0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xff,0xff,0xff,0xff,0x03,0x00}};
static const uint8_t five[3][14] = {{0x00,0xc0,0xff,0xff,0xff,0x3f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x00,0x00},
									{0x00,0x1f,0x1f,0x1f,0x1f,0x0f,0x0f,0x0f,0x0f,0x1f,0xfe,0xfe,0xf8,0xe0},
									{0x00,0x38,0x78,0x78,0xf8,0xf0,0xf0,0xf0,0xf8,0xfc,0x7f,0x3f,0x1f,0x07}};
static const uint8_t six[3][14] = {{0xf8,0xfc,0xfe,0xff,0x1f,0x0f,0x0f,0x0f,0x0f,0x1f,0x3f,0x3e,0x3c,0x38},
									{0xff,0xff,0xff,0xff,0x1f,0x0f,0x0f,0x0f,0x0f,0x1f,0xff,0xfe,0xfc,0xf8},
									{0x1f,0x3f,0x7f,0xff,0xf8,0xf0,0xf0,0xf0,0xf0,0xf8,0xff,0x7f,0x3f,0x1f}};
static const uint8_t seven[3][14] = {{0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0xcf,0xff,0xff,0x7f,0x1f},
										{0x00,0x00,0x00,0x00,0xc0,0xf0,0xf0,0xfc,0x7f,0x1f,0x07,0x01,0x00,0x00},
										{0xc0,0xf0,0xfc,0xff,0x7f,0x1f,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00}};
static const uint8_t eight[3][14] = {{0x00,0xf8,0xfc,0xfe,0xff,0x1f,0x0f,0x0f,0x1f,0xff,0xfe,0xfc,0xf8,0x00},
										{0xe0,0xf3,0xff,0xff,0x7f,0x3e,0x3c,0x3c,0x3e,0x7f,0xff,0xff,0xf3,0xe0},
										{0x1f,0x3f,0x7f,0xff,0xf8,0xf0,0xf0,0xf0,0xf0,0xf8,0xff,0x7f,0x3f,0x1f}};
static const uint8_t nine[3][14] = {{0xf8,0xfc,0xfe,0xff,0x1f,0x0f,0x0f,0x0f,0x0f,0x1f,0xff,0xfe,0xfc,0xf8},
									{0x1f,0x3f,0x7f,0xff,0xf8,0xf0,0xf0,0xf0,0xf0,0xf8,0xff,0xff,0xff,0xff},
									{0x1c,0x3c,0x7c,0xfc,0xf8,0xf0,0xf0,0xf0,0xf0,0xf8,0xff,0x7f,0x3f,0x1f}};
static const uint8_t zvezda[3][14] = {{0x00,0x00,0x80,0x80,0x00,0x00,0xe0,0xe0,0x00,0x00,0x80,0x80,0x00,0x00},
										{0x18,0x18,0x99,0xdb,0xff,0x7e,0xff,0xff,0x7e,0xff,0xdb,0x99,0x18,0x18},
										{0x00,0x00,0x01,0x01,0x00,0x00,0x07,0x07,0x00,0x00,0x01,0x01,0x00,0x00}};
static const uint8_t edenica_2[5] = {0x84,0x86,0xff,0x80,0x80};
static const uint8_t edenica_3[2][8] = {{0x00,0x0c,0x0e,0xff,0xff,0x00,0x00,0x00},
									{0xc0,0xc0,0xc0,0xff,0xff,0xc0,0xc0,0xc0}};
static const uint8_t two_2[5] = {0xc6,0xa1,0x91,0x89,0x86};
static const uint8_t two_3[2][9] = {{0x1c,0x1e,0x07,0x03,0x03,0x83,0xc7,0xfe,0x7c},
									{0xf0,0xf8,0xdc,0xce,0xc7,0xc3,0xc1,0xc0,0xc0}};
static const uint8_t three_2[5] = {0x41,0x89,0x8d,0x8b,0x71};
static const uint8_t three_3[2][9] = {{0x03,0x03,0xc3,0xe3,0xf3,0xfb,0xdf,0x8f,0x07},
									{0x30,0x70,0xe0,0xc0,0xc0,0xc0,0xe1,0x7f,0x3f}};
static const uint8_t four_2[5] = {0x38,0x24,0x22,0xff,0x20};
static const uint8_t four_3[2][9] = {{0x00,0x80,0xe0,0x78,0x1e,0x07,0xff,0xff,0x00},
									{0x0e,0x0f,0x0d,0x0c,0x0c,0x0c,0xff,0xff,0x0c}};
static const uint8_t five_2[5] = {0x4e,0x89,0x89,0x89,0x71};
static const uint8_t five_3[2][9] = {{0xf8,0xfe,0xcf,0x63,0x63,0x63,0xe3,0xc3,0x83},
									{0x30,0x70,0xe0,0xc0,0xc0,0xc0,0xe0,0x7f,0x3f}};
// ошибка
static const uint8_t error[30] = {0x1c,0x22,0x22,0x1c,0x00,0x3e,0x20,0x3e,0x20,0x3e,0x00,0x3e,0x10,0x08,0x3e,0x00,0x3e,0x2a,0x2a,0x3a,0x00,0x3e,0x08,0x14,0x22,0x00,0x38,0x14,0x12,0x3e};
// Повторить попытку
static const uint8_t try_again[74] = {0x3e,0x02,0x02,0x3e,0x00,0x1c,0x22,0x22,0x1c,0x00,0x3e,0x2a,0x2a,0x14,0x00,0x02,0x02,0x3e,0x02,0x02,0x00,0x1c,0x22,0x22,0x1c,
									 0x00,0x3e,0x12,0x12,0x0c,0x00,0x3e,0x10,0x08,0x3e,0x00,0x02,0x02,0x3e,0x02,0x02,0x00,0x3e,0x2a,0x2a,0x22,0x00,0x00,0x00,0x00,
									 0x00,0x00,0x00,0x3e,0x2a,0x2a,0x14,0x00,0x3e,0x2a,0x2a,0x14,0x00,0x1c,0x22,0x22,0x1c,0x00,0x20,0x38,0x24,0x22,0x3e,0x20};

static const uint8_t nfc_1[6] = {0x3c,0x7e,0x66,0x66,0x7e,0x3c};
static const uint8_t nfc_2[3][16] = {{0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00},
								{0x7e,0xff,0xc3,0x00,0x00,0x3c,0x7e,0x66,0x66,0x7e,0x3c,0x00,0x00,0xc3,0xff,0x7e},
								{0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00}};
static const uint8_t nfc_3[3][28] = {{0x00,0xe0,0xf8,0x3c,0x0e,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x0e,0x3c,0xf8,0xe0,0x00},
								{0xff,0xff,0x81,0x00,0x00,0x00,0x7e,0xff,0xc3,0x00,0x00,0x3c,0x7e,0x66,0x66,0x7e,0x3c,0x00,0x00,0x00,0xe7,0x3c,0x00,0x00,0x00,0x81,0xff,0xff},
								{0x00,0x07,0x1f,0x3c,0x70,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x70,0x3c,0x1f,0x07,0x00}};
static const uint8_t nfc_4[3][28] = {{0x00,0xe0,0xf8,0x3c,0x0e,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x0e,0x3c,0xf8,0xe0,0x00},
								{0xff,0xff,0x81,0x00,0x00,0x00,0x7e,0xff,0xc3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe7,0x3c,0x00,0x00,0x00,0x81,0xff,0xff},
								{0x00,0x07,0x1f,0x3c,0x70,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x70,0x3c,0x1f,0x07,0x00}};
static const uint8_t nfc_5[3][28] = {{0x00,0xe0,0xf8,0x3c,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x3c,0xf8,0xe0,0x00},
								{0xff,0xff,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xff,0xff},
								{0x00,0x07,0x1f,0x3c,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x3c,0x1f,0x07,0x00}};
static const uint8_t close[3][14] = {{0x00,0x80,0xe0,0xf0,0x38,0x18,0x18,0x18,0x18,0x38,0xf0,0xe0,0x80,0x00},
								{0xfc,0xff,0x0f,0x0c,0x0c,0xcc,0xec,0xec,0xcc,0x0c,0x0c,0x0f,0xff,0xfc},
								{0x3f,0x7f,0xe0,0xc0,0xcc,0xce,0xcf,0xcf,0xce,0xcc,0xc0,0xe0,0x7f,0x3f}};
static const uint8_t open[3][14] = {{0x00,0x80,0xe0,0xf0,0x38,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
								{0xfc,0xff,0x0f,0x0c,0x0c,0xcc,0xec,0xec,0xcc,0x0c,0x0c,0x0c,0xfc,0xfc},
								{0x3f,0x7f,0xe0,0xc0,0xcc,0xce,0xcf,0xcf,0xce,0xcc,0xc0,0xe0,0x7f,0x3f}};
static const uint8_t open_label[38] = {0x1c,0x22,0x22,0x1c,0x00,0x02,0x02,0x3e,0x02,0x02,0x00,0x3e,0x08,0x14,0x22,0x00,0x3e,0x12,0x12,
								  0x0c,0x00,0x3e,0x24,0x24,0x18,0x00,0x3e,0x00,0x02,0x02,0x3e,0x02,0x02,0x00,0x1c,0x22,0x22,0x1c};
static const uint8_t close_label[38] = {0x00,0x2a,0x2a,0x2a,0x36,0x00,0x38,0x14,0x12,0x3e,0x00,0x3e,0x08,0x14,0x22,0x00,0x3e,0x12,0x12,
								   0x0c,0x00,0x3e,0x24,0x24,0x18,0x00,0x3e,0x00,0x02,0x02,0x3e,0x02,0x02,0x00,0x1c,0x22,0x22,0x1c};

static const uint8_t service_mode[76] = {0x1C, 0x22, 0x22, 0x14, 0x00, 0x3E, 0x2A, 0x22, 0x00, 0x3E, 0x12, 0x12, 0x0C, 0x00, 0x3E, 0x2A, 0x2A, 0x14, 0x00, 0x3E, 0x10, 0x08, 0x3E, 0x00, 0x1C, 0x22, 0x22, 0x14, 0x00, 0x3E, 0x08, 0x08, 0x3E, 0x00, 0x3E, 0x24, 0x24, 0x18, 0x00, 0x3E, 0x00, 0x3C, 0x11, 0x09, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x3E, 0x12, 0x12, 0x0C, 0x00, 0x3E, 0x2A, 0x22, 0x00, 0x36, 0x08, 0x3E, 0x08, 0x36, 0x00, 0x3E, 0x10, 0x08, 0x3E, 0x00, 0x3E, 0x04, 0x08, 0x04, 0x3E, 0x00};

static const uint8_t master_key[] = {0x3E, 0x04, 0x08, 0x04, 0x3E, 0x00, 0x3C, 0x12, 0x12, 0x3C, 0x00, 0x1C, 0x22, 0x22, 0x14, 0x00, 0x02, 0x02, 0x3E, 0x02, 0x02, 0x00, 0x3E, 0x2A, 0x22, 0x00, 0x3E, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x3E, 0x08, 0x14, 0x22, 0x00, 0x20, 0x1C, 0x02, 0x3E, 0x00, 0x3E, 0x08, 0x1C, 0x22, 0x22, 0x1C, 0x00, 0x06, 0x08, 0x08, 0x3E, 0x00};
										//0x3E, 0x08, 0x14, 0x22, 0x00, 0x3C, 0x12, 0x12, 0x3C, 0x00, 0x3E, 0x12, 0x12, 0x0C, 0x00, 0x02, 0x02, 0x3E, 0x02, 0x02, 0x00,  0x3C, 0x12, 0x12, 0x3C, 0x00}; // карта

static const uint8_t time_charge[] = {0x3E, 0x2A, 0x2A, 0x14, 0x00, 0x3E, 0x12, 0x12, 0x0C, 0x00,  0x3E, 0x2A, 0x22, 0x00, 0x3E, 0x04, 0x08, 0x04, 0x3E, 0x00, 0x2C, 0x12, 0x12, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x14, 0x22, 0x2A, 0x14, 0x00, 0x3C, 0x12, 0x12, 0x3C, 0x00, 0x3E, 0x12, 0x12, 0x0C, 0x00, 0x2C, 0x12, 0x12, 0x3E, 0x00, 0x20, 0x38, 0x24, 0x22, 0x3E, 0x20, 0x00, 0x3C, 0x12, 0x12, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,0x3E, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x2E ,0x2A, 0x3E};

static const uint8_t general_code[46] = {0x1C, 0x22, 0x22, 0x1C, 0x00, 0x3E, 0x2A, 0x2A, 0x3A, 0x00, 0x1E, 0x10, 0x1C, 0x10, 0x1E, 0x38, 0x00, 0x3E, 0x10, 0x08, 0x3E, 0x00, 0x3C, 0x11, 0x09, 0x3C, 0x00, 0x00, 0x00, 0x00,
										0x3E, 0x08, 0x14, 0x22, 0x00, 0x1C, 0x22, 0x22, 0x1C, 0x00, 0x20, 0x38, 0x24, 0x22, 0x3E, 0x20};

static const uint8_t saved[] = {0x1C, 0x22, 0x22, 0x14, 0x00, 0x1C, 0x22, 0x22, 0x1C, 0x00, 0x36, 0x08, 0x36, 0x00, 0x3E, 0x12, 0x12, 0x0C, 0x00, 0x3C, 0x12, 0x12, 0x3C, 0x00, 0x3E, 0x08, 0x08, 0x3E, 0x00, 0x3E, 0x2A, 0x22, 0x00,  0x3E, 0x08, 0x08, 0x3E, 0x00, 0x1C, 0x22, 0x22, 0x1C, 0x00};

static const uint8_t expect_key[] = {0x1C, 0x22, 0x22, 0x1C, 0x00, 0x36, 0x08, 0x3E, 0x08, 0x36, 0x00, 0x3E, 0x10, 0x08, 0x3E,  0x20, 0x38, 0x24, 0x22, 0x3E, 0x20, 0x00, 0x3C, 0x12, 0x12, 0x3C, 0x00, 0x3E, 0x08, 0x1C, 0x22, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x3E, 0x08, 0x14, 0x22, 0x00, 0x20, 0x1C, 0x02, 0x3E, 0x00, 0x3E, 0x08, 0x1C, 0x22, 0x22, 0x1C, 0x00, 0x06, 0x08, 0x08, 0x3E, 0x00};

static uint8_t scrinNumberValue = START_SCREEN;
static uint8_t countEffects = 0;
static uint8_t flagEventOverLcd = FALSE;	//Флаг устанавливается когда анимация (эффект) полностью выпотнен

static uint8_t selectedCall = 0; 	// Переменная хранить номер выбранной ячейки
static uint8_t prevSelectedCall = 0; // Переменная хранить номер ячейки каторая была выбрана на предыдущем шаге

/*********************************************************************
 * Получить состояние флага о окончании анимации (эффекта)           *
 *********************************************************************/
uint8_t gerStateFlagEventOverLcd(void)
{
	return flagEventOverLcd;
}

/*********************************************************************
 * Сбросит состояние флага о окончании анимации (эффекта)            *
 *********************************************************************/
void resetStateFlagEventOverLcd(void)
{
	flagEventOverLcd = FALSE;
}

/*********************************************************************
 * Очистить весь дисплей за исключением хидера                       *
 *********************************************************************/
void clearLcdAllNoHider(void)
{
	for(uint8_t i = 1; i < 4; i++)
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
 * Установить какой экран будет отображаться LCD                     *
 *********************************************************************/
void setScreenNumber(screenNumber_t screenNumber)
{
	//clearLcd();
	clearLcdAllNoHider();
	scrinNumberValue = screenNumber;
	countEffects = 0;
	stopGTimer(TIMER_LCD_EFFECTS);
}

/*********************************************************************
 * Передать выбранную ячейку для анимации выбора                     *
 *********************************************************************/
void setSelectedEndPrevCell(uint8_t selectCall, uint8_t prevSelectCall)
{
	selectedCall = selectCall;
	prevSelectedCall = prevSelectCall;
	countEffects = 0;
}

/*********************************************************************
 * Вывод хидера на LCD                                               *
 *********************************************************************/
static void getLcdHider(void)
{
	if(getMaxChannels() == 5)
	{
		writeCodeL(0xB8);
		writeCodeL(0x13 + 11);
		for(uint8_t i = 0; i < sizeof(one_small_pos); i++)
		{
			writeDataL(one_small_pos[i]);
		}
		writeCodeL(0xB8);
		writeCodeL(0x13 + 23);
		if(getStateCh_1() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataL(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataL(0x00);
			}
		}

		writeCodeL(0xB8);
		writeCodeL(0x13 + 31);
		for(uint8_t i = 0; i < sizeof(two_small_pos); i++)
		{
			writeDataL(two_small_pos[i]);
		}
		writeCodeL(0xB8);
		writeCodeL(0x13 + 43);
		if(getStateCh_2() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataL(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataL(0x00);
			}
		}
		writeCodeL(0xB8);
		writeCodeL(0x13 + 51);
		for(uint8_t i = 0; i < 10; i++)
		{
			writeDataL(three_small_pos[i]);
		}
		writeCodeR(0xB8);
		//start_pos = 0x00;
		writeCodeR(0x00);
		for(uint8_t i = 10; i < 20; i++)
		{
			writeDataR(three_small_pos[i]);
		}

		writeCodeR(0xB8);
		writeCodeR(0x00 + 2);
		if(getStateCh_3() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(0x00);
			}
		}
		writeCodeR(0xB8);
		writeCodeR(0x00 + 11);
		for(uint8_t i = 0; i < sizeof(four_small_pos); i++)
		{
			writeDataR(four_small_pos[i]);
		}
		writeCodeR(0xB8);
		writeCodeR(0x00 + 23);
		if(getStateCh_4() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(0x00);
			}
		}

		writeCodeR(0xB8);
		writeCodeR(0x00 + 31);
		for(uint8_t i = 0; i < sizeof(five_small_pos); i++)
		{
			writeDataR(five_small_pos[i]);
		}
		writeCodeR(0xB8);
		writeCodeR(0x00 + 43);
		if(getStateCh_5() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(0x00);
			}
		}
	}
	else
	{
		writeCodeL(0xB8);
		writeCodeL(0x13 + 11);
		for(uint8_t i = 0; i < sizeof(one_small_pos); i++)
		{
			writeDataL(one_small_pos[i]);
		}
		writeCodeL(0xB8);
		writeCodeL(0x13 + 23);
		if(getStateCh_1() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataL(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataL(0x00);
			}
		}

		writeCodeL(0xB8);
		writeCodeL(0x13 + 51);
		for(uint8_t i = 0; i < 10; i++)
		{
			writeDataL(two_small_pos[i]);
		}
		writeCodeR(0xB8);
		//start_pos = 0x00;
		writeCodeR(0x00);
		for(uint8_t i = 10; i < 20; i++)
		{
			writeDataR(two_small_pos[i]);
		}

		writeCodeR(0xB8);
		writeCodeR(0x00 + 2);
		if(getStateCh_2() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(0x00);
			}
		}

		writeCodeR(0xB8);
		writeCodeR(0x00 + 31);
		for(uint8_t i = 0; i < sizeof(five_small_pos); i++)
		{
			writeDataR(three_small_pos[i]);
		}
		writeCodeR(0xB8);
		writeCodeR(0x00 + 43);
		if(getStateCh_3() == CH_CLOSE)
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(lock_small[i]);
			}
		}
		else
		{
			for(uint8_t i = 0; i < sizeof(lock_small); i++)
			{
				writeDataR(0x00);
			}
		}
	}
}

/*********************************************************************
 * Вывод хидера с инверсмей на LCD                                   *
 *********************************************************************/
static void display_header_inv(uint8_t num)
{
	uint8_t	c;
	uint8_t start_pos;
	if(getMaxChannels() == 5)
	{
		if(num==1)
		{
			writeCodeL(0xB8);
			uint8_t start_pos = 0x13 + 11;
			writeCodeL(start_pos);
			for(c=0; c<20; c++)
			{
				writeDataL(one_small_inv[c]);
			}
			if(getStateCh_1() == CH_CLOSE)
			{
				writeCodeL(0xB8);
				start_pos = 0x13 + 23;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(lock_small_inv[c]);
				}
			}
		}
		else if(num==2)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 31;
			writeCodeL(start_pos);
			for(c=0; c<20; c++)
			{
				writeDataL(two_small_inv[c]);
			}
			if(getStateCh_2() == CH_CLOSE)
			{
				writeCodeL(0xB8);
				start_pos = 0x13 + 43;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(lock_small_inv[c]);
				}
			}
		}
		else if(num==3)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 51;
			writeCodeL(start_pos);
			for(c=0; c<10; c++)
			{
				writeDataL(three_small_inv[c]);
			}
			writeCodeR(0xB8);
			start_pos = 0x00;
			writeCodeR(start_pos);
			for(c=10; c<20; c++)
			{
				writeDataR(three_small_inv[c]);
			}
			if(getStateCh_3() == CH_CLOSE)
			{
				writeCodeR(0xB8);
				start_pos = 0x00 + 2;
				writeCodeR(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataR(lock_small_inv[c]);
				}
			}
		}
		else if(num==4)
		{
			writeCodeR(0xB8);
			start_pos = 0x00 + 11;
			writeCodeR(start_pos);
			for(c=0; c<20; c++)
			{
				writeDataR(four_small_inv[c]);
			}
			if(getStateCh_4() == CH_CLOSE)
			{
				writeCodeR(0xB8);
				start_pos = 0x00 + 23;
				writeCodeR(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataR(lock_small_inv[c]);
				}
			}
		}
		else if(num==5)
		{
			writeCodeR(0xB8);
			start_pos = 0x00 + 31;
			writeCodeR(start_pos);
			for(c=0; c<20; c++)
			{
				writeDataR(five_small_inv[c]);
			}
			if(getStateCh_5() == CH_CLOSE)
			{
				writeCodeR(0xB8);
				start_pos = 0x00 + 43;
				writeCodeR(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataR(lock_small_inv[c]);
				}
			}
		}
	}
	else
	{
		if(num==1)
		{
			writeCodeL(0xB8);
			uint8_t start_pos = 0x13 + 11;
			writeCodeL(start_pos);
			for(c=0; c<20; c++)
			{
				writeDataL(one_small_inv[c]);
			}
			if(getStateCh_1() == CH_CLOSE)
			{
				writeCodeL(0xB8);
				start_pos = 0x13 + 23;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(lock_small_inv[c]);
				}
			}
		}
		else if(num==2)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 51;
			writeCodeL(start_pos);
			for(c=0; c<10; c++)
			{
				writeDataL(two_small_inv[c]);
			}
			writeCodeR(0xB8);
			start_pos = 0x00;
			writeCodeR(start_pos);
			for(c=10; c<20; c++)
			{
				writeDataR(two_small_inv[c]);
			}
			if(getStateCh_2() == CH_CLOSE)
			{
				writeCodeR(0xB8);
				start_pos = 0x00 + 2;
				writeCodeR(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataR(lock_small_inv[c]);
				}
			}
		}
		else if(num==3)
		{
			writeCodeR(0xB8);
			start_pos = 0x00 + 31;
			writeCodeR(start_pos);
			for(c=0; c<20; c++)
			{
				writeDataR(three_small_inv[c]);
			}
			if(getStateCh_3() == CH_CLOSE)
			{
				writeCodeR(0xB8);
				start_pos = 0x00 + 43;
				writeCodeR(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataR(lock_small_inv[c]);
				}
			}
		}
	}
}

/*********************************************************************
 * Вывод значка (анимации) NFC                                       *
 *********************************************************************/
static void display_nfc(uint8_t sect)
{
	uint8_t p;
	uint8_t c;
	clearLcdAllNoHider();
	if (sect==1)
	{
		writeCodeL(0xba);
		writeCodeL(0x4d);
		for(c=0; c<3; c++)
		{
			writeDataL(nfc_1[c]);
		}
		writeCodeR(0xba);
		writeCodeR(0x00);
		for(c=3; c<6; c--)
		{
			writeDataR(nfc_1[c]);
		}
	}
	else if(sect==2)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x48);
			for(c=0; c<8; c++)
			{
				writeDataL(nfc_2[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=8; c<16; c--)
			{
				writeDataR(nfc_2[p-1][c]);
			}
		}
	}
	else if(sect==3)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x42);
			for(c=0; c<14; c++)
			{
				writeDataL(nfc_3[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=14; c<28; c--)
			{
				writeDataR(nfc_3[p-1][c]);
			}
		}
	}
	else if(sect==4)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x42);
			for(c=0; c<14; c++)
			{
				writeDataL(nfc_4[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=14; c<28; c--)
			{
				writeDataR(nfc_4[p-1][c]);
			}
		}
	}
	else if(sect==5)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x42);
			for(c=0; c<14; c++)
			{
				writeDataL(nfc_5[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=14; c<28; c--)
			{
				writeDataR(nfc_5[p-1][c]);
			}
		}
	}
}

/*********************************************************************
 * Анимация открытия/закрытия                                        *
 *********************************************************************/
void animate_lock(uint8_t side)
{
	uint8_t	p;
	uint8_t	c;
	getLcdHider();
	display_header_inv(getChChoiseValue());
	clearLcdAllNoHider();
	if (side==0)
	{
		writeCodeL(0xBA);
		writeCodeL(0x4F-8);
		for(c=0; c<9; c++)
		{
			writeDataL(close_label[c]);
		}
		writeCodeR(0xBA);
		writeCodeR(0x00);
		for(c=9; c<38; c++)
		{
			writeDataR(close_label[c]);
		}
		for(p=1; p<4; p++)
		{
		writeCodeL(p|0xB8);
		writeCodeL(0x4F-28);
		for(c=0; c<14; c++)
		{
			writeDataL(open[p-1][c]);
		}
		}
		HAL_Delay(1000);
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x4F-28);
		for(c=0; c<14; c++)
		{
			writeDataL(close[p-1][c]);
		}
		}
		HAL_Delay(1000);
		clearLcdAllNoHider();
		writeCodeL(0xBA);
		writeCodeL(0x4F-8);
		for(c=0; c<9; c++)
		{
			writeDataL(close_label[c]);
		}
		writeCodeR(0xBA);
		writeCodeR(0x00);
		for(c=9; c<38; c++)
		{
			writeDataR(close_label[c]);
		}
		HAL_Delay(500);
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x4F-28);
			for(c=0; c<14; c++)
			{
				writeDataL(close[p-1][c]);
			}
		}
		HAL_Delay(1500);
	}
	else if(side==1)
	{
		writeCodeL(0xBA);
		writeCodeL(0x4F-8);
		for(c=0; c<9; c++)
		{
		writeDataL(open_label[c]);
		}
		writeCodeR(0xBA);
		writeCodeR(0x00);
		for(c=9; c<38; c++)
		{
			writeDataR(open_label[c]);
		}
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x4F-28);
			for(c=0; c<14; c++)
			{
				writeDataL(close[p-1][c]);
			}
		}
		HAL_Delay(1000);
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x4F-28);
			for(c=0; c<14; c++)
			{
				writeDataL(open[p-1][c]);
			}
		}
		HAL_Delay(1000);
		clearLcdAllNoHider();
		writeCodeL(0xBA);
		writeCodeL(0x4F-8);
		for(c=0; c<9; c++)
		{
			writeDataL(open_label[c]);
		}
		writeCodeR(0xBA);
		writeCodeR(0x00);
		for(c=9; c<38; c++)
		{
			writeDataR(open_label[c]);
		}
		HAL_Delay(500);
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x4F-28);
			for(c=0; c<14; c++)
			{
				writeDataL(open[p-1][c]);
			}
		}
		HAL_Delay(1500);
	}
	flagEventOverLcd = TRUE;
}

/*********************************************************************
 * Вывод больших цифр или звездочек в позицию pos                    *
 *********************************************************************/
static void display_symb(uint8_t pos, uint8_t symb)
{
	uint8_t	p;
	uint8_t	c;
	if(symb==0)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(null[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(null[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(null[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(null[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==1)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(one[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(one[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(one[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(one[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==2)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(two[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(two[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(two[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(two[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==3)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(three[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(three[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(three[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(three[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==4)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(four[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(four[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(four[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(four[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==5)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(five[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(five[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(five[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(five[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==6)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(six[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(six[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(six[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(six[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==7)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(seven[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(seven[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(seven[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(seven[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==8)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(eight[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(eight[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(eight[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(eight[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==9)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(nine[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(nine[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(nine[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(nine[p-1][c]);
				}
			}
			break;
		}
	}
	else if(symb==0xFF)
	{
		switch(pos)
		{
			case 1:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+27);
				for(c=0; c<14; c++)
				{
					writeDataL(zvezda[p-1][c]);
				}
			}
			break;
			case 2:
			for(p=1; p<4; p++)
			{
				writeCodeL(p|0xB8);
				writeCodeL(19+45);
				for(c=0; c<14; c++)
				{
					writeDataL(zvezda[p-1][c]);
				}
			}
			break;
			case 3:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x02);
				for(c=0; c<14; c++)
				{
					writeDataR(zvezda[p-1][c]);
				}
			}
			break;
			case 4:
			for(p=1; p<4; p++)
			{
				writeCodeR(p|0xB8);
				writeCodeR(0x14);
				for(c=0; c<14; c++)
				{
					writeDataR(zvezda[p-1][c]);
				}
			}
			break;
		}
	}
}

/*********************************************************************
 * Вывод анимации                                                    *
 *********************************************************************/
void animate_forward(uint8_t num)
{
	uint8_t start_pos;
	uint8_t	p;
	uint8_t	c;
	if(getMaxChannels() == 5)
	{
		if(num==1)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 20;
			writeCodeL(start_pos);
			for(c=0; c<2; c++)
			{
				writeDataL(0x00);
			}
			writeCodeL(0xB8);
			start_pos = 0x13 + 23;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(0x00);
			}
			HAL_Delay(100);
			writeCodeL(0xB9);
			start_pos = 0x13 + 30;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(edenica_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 40;
				writeCodeL(start_pos);
				for(c=0; c<8; c++)
				{
					writeDataL(edenica_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
		else if(num==2)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 39;
			writeCodeL(start_pos);
			for(c=0; c<3; c++)
			{
				writeDataL(0x00);
			}
			writeCodeL(0xB8);
			start_pos = 0x13 + 43;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(0x00);
			}
			HAL_Delay(100);
			writeCodeL(0xB9);
			start_pos = 0x13 + 38;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(two_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 46;
				writeCodeL(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataL(two_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
		else if(num==3)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 59;
			writeCodeL(start_pos);
			for(c=0; c<2; c++)
			{
				writeDataL(0x00);
			}
			writeCodeR(0xB8);
			start_pos = 0x00;
			writeCodeR(start_pos);
			writeDataR(0x00);
			writeCodeR(0xB8);
			start_pos = 0x00 + 2;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(0x00);
			}
			writeCodeR(start_pos);
			writeDataR(0x00);
			writeCodeL(0xB9);
			start_pos = 0x13 + 58;
			writeCodeL(start_pos);
			for(c=0; c<3; c++)
			{
				writeDataL(three_2[c]);
			}
			writeCodeR(0xB9);
			start_pos = 0x00;
			writeCodeR(start_pos);
			for(c=3; c<5; c++)
			{
				writeDataR(three_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 56;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(three_3[p-1][c]);
				}
				writeCodeR(p|0xB8);
				start_pos = 0x00;
				writeCodeR(start_pos);
				for(c=5; c<9; c++)
				{
					writeDataR(three_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
		else if(num==4)
		{
			writeCodeR(0xB8);
			start_pos = 0x00 + 19;
			writeCodeR(start_pos);
			for(c=0; c<3; c++)
			{
				writeDataR(0x00);
			}
			writeCodeR(0xB8);
			start_pos = 0x00 + 23;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(0x00);
			}
			HAL_Delay(100);
			writeCodeR(0xB9);
			start_pos = 0x00 + 18;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(four_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeR(p|0xB8);
				uint8_t start_pos = 0x00 + 4;
				writeCodeR(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataR(four_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
		else if(num==5)
		{
			writeCodeR(0xB8);
			start_pos = 0x00 + 39;
			writeCodeR(start_pos);
			for(c=0; c<3; c++)
			{
			writeDataR(0x00);
			}
			writeCodeR(0xB8);
			start_pos = 0x00 + 43;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
			writeDataR(0x00);
			}
			HAL_Delay(100);
			writeCodeR(0xB9);
			start_pos = 0x00 + 29;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(five_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeR(p|0xB8);
				uint8_t start_pos = 0x00 + 19;
				writeCodeR(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataR(five_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
	}
	else
	{
		if(num==1)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 20;
			writeCodeL(start_pos);
			for(c=0; c<2; c++)
			{
				writeDataL(0x00);
			}
			writeCodeL(0xB8);
			start_pos = 0x13 + 23;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(0x00);
			}
			HAL_Delay(100);
			writeCodeL(0xB9);
			start_pos = 0x13 + 30;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(edenica_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 40;
				writeCodeL(start_pos);
				for(c=0; c<8; c++)
				{
					writeDataL(edenica_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
		else if(num==2)
		{
			writeCodeL(0xB8);
			start_pos = 0x13 + 59;
			writeCodeL(start_pos);
			for(c=0; c<2; c++)
			{
				writeDataL(0x00);
			}
			writeCodeR(0xB8);
			start_pos = 0x00;
			writeCodeR(start_pos);
			writeDataR(0x00);
			writeCodeR(0xB8);
			start_pos = 0x00 + 2;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(0x00);
			}
			writeCodeR(start_pos);
			writeDataR(0x00);
			writeCodeL(0xB9);
			start_pos = 0x13 + 58;
			writeCodeL(start_pos);
			for(c=0; c<3; c++)
			{
				writeDataL(two_2[c]);
			}
			writeCodeR(0xB9);
			start_pos = 0x00;
			writeCodeR(start_pos);
			for(c=3; c<5; c++)
			{
				writeDataR(two_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 56;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(two_3[p-1][c]);
				}
				writeCodeR(p|0xB8);
				start_pos = 0x00;
				writeCodeR(start_pos);
				for(c=5; c<9; c++)
				{
					writeDataR(two_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
		else if(num==3)
		{
			writeCodeR(0xB8);
			start_pos = 0x00 + 39;
			writeCodeR(start_pos);
			for(c=0; c<3; c++)
			{
			writeDataR(0x00);
			}
			writeCodeR(0xB8);
			start_pos = 0x00 + 43;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
			writeDataR(0x00);
			}
			HAL_Delay(100);
			writeCodeR(0xB9);
			start_pos = 0x00 + 29;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(three_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			for(p=1; p<3; p++)
			{
				writeCodeR(p|0xB8);
				uint8_t start_pos = 0x00 + 19;
				writeCodeR(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataR(three_3[p-1][c]);
				}
			}
			HAL_Delay(100);
		}
	}
}

/*********************************************************************
 * Вывод анимации в обратной последовательности                      *
 *********************************************************************/
void animate_back(uint8_t num)
{
	//clearLcd();
	clearLcdAllNoHider();
	uint8_t start_pos;
	uint8_t	p;
	uint8_t	c;
	if(getMaxChannels() == 5)
	{
		if(num==1)
		{
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 40;
				writeCodeL(start_pos);
				for(c=0; c<8; c++)
				{
					writeDataL(edenica_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			start_pos = 0x13 + 30;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(edenica_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
		else if(num==2)
		{
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 46;
				writeCodeL(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataL(two_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			start_pos = 0x13 + 38;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(two_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
		else if(num==3)
		{
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 56;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(three_3[p-1][c]);
				}
				writeCodeR(p|0xB8);
				start_pos = 0x00;
				writeCodeR(start_pos);
				for(c=5; c<9; c++)
				{
					writeDataR(three_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			start_pos = 0x13 + 58;
			writeCodeL(start_pos);
			for(c=0; c<3; c++)
			{
				writeDataL(three_2[c]);
			}
			writeCodeR(0xB9);
			start_pos = 0x00;
			writeCodeR(start_pos);
			for(c=3; c<5; c++)
			{
				writeDataR(three_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
		else if(num==4)
		{
			for(p=1; p<3; p++)
			{
				writeCodeR(p|0xB8);
				uint8_t start_pos = 0x00 + 4;
				writeCodeR(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataR(four_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeR(0xB9);
			start_pos = 0x00 + 18;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(four_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
		else if(num==5)
		{
			for(p=1; p<3; p++)
			{
				writeCodeR(p|0xB8);
				uint8_t start_pos = 0x00 + 19;
				writeCodeR(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataR(five_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeR(0xB9);
			start_pos = 0x00 + 29;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(five_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
	}
	else
	{
		if(num==1)
		{
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 40;
				writeCodeL(start_pos);
				for(c=0; c<8; c++)
				{
					writeDataL(edenica_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			start_pos = 0x13 + 30;
			writeCodeL(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataL(edenica_2[c]);
			}
			HAL_Delay(100);
			clearLcdAllNoHider();
		}
		else if(num==2)
		{
			for(p=1; p<3; p++)
			{
				writeCodeL(p|0xB8);
				uint8_t start_pos = 0x13 + 56;
				writeCodeL(start_pos);
				for(c=0; c<5; c++)
				{
					writeDataL(two_3[p-1][c]);
				}
				writeCodeR(p|0xB8);
				start_pos = 0x00;
				writeCodeR(start_pos);
				for(c=5; c<9; c++)
				{
					writeDataR(two_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			start_pos = 0x13 + 58;
			writeCodeL(start_pos);
			for(c=0; c<3; c++)
			{
				writeDataL(two_2[c]);
			}
			writeCodeR(0xB9);
			start_pos = 0x00;
			writeCodeR(start_pos);
			for(c=3; c<5; c++)
			{
				writeDataR(two_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
		else if(num==3)
		{
			for(p=1; p<3; p++)
			{
				writeCodeR(p|0xB8);
				uint8_t start_pos = 0x00 + 19;
				writeCodeR(start_pos);
				for(c=0; c<9; c++)
				{
					writeDataR(three_3[p-1][c]);
				}
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			writeCodeR(0xB9);
			start_pos = 0x00 + 29;
			writeCodeR(start_pos);
			for(c=0; c<5; c++)
			{
				writeDataR(three_2[c]);
			}
			HAL_Delay(100);
			//clearLcd();
			clearLcdAllNoHider();
			//display_header_exept(0);
		}
	}
}

/*********************************************************************
 * Вывод цифр без анимации                                           *
 *********************************************************************/
void displaynum_non_animate(uint8_t num)
{
	uint8_t	p;
	uint8_t	c;
	//clearLcd();
	clearLcdAllNoHider();
	if (num==1)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(one[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(one[p-1][c]);
			}
		}
	}
	else if (num==2)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(two[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(two[p-1][c]);
			}
		}
	}
	else if (num==3)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
			writeDataL(three[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(three[p-1][c]);
			}
		}
	}
	else if (num==4)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(four[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(four[p-1][c]);
			}
		}
	}
	else if (num==5)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(five[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(five[p-1][c]);
			}
		}
	}
}

/*********************************************************************
 * Очистить хидер                                                    *
 *********************************************************************/
void clearLcdHider(void)
{
	writeCodeL(0xB8);
	writeCodeL(0x13);
	for(uint8_t j = 0; j < 61; j++)
	{
		writeDataL(0x00);
	}
	writeCodeR(0xB8);
	writeCodeR(0x00);
	for(uint8_t j = 61; j < 122; j++)
	{
		writeDataR(0x00);
	}
}

/*********************************************************************
 * Вывод анимации на LCD                                             *
 *********************************************************************/
void displaynum(uint8_t num, uint8_t last_num)
{
	//clearLcd();
	//getLcdHider();
	clearLcdAllNoHider();
	animate_back(last_num);
	getLcdHider();
	animate_forward(num);
	displaynum_non_animate(num);
}

/*********************************************************************
 * Вывод сообщения о ошибке и прозьба повторить попытку              *
 *********************************************************************/
static void display_try_again(void)
{
	uint8_t	c;
	writeCodeL(0xB9);
	writeCodeL(0x4F-14);
	for(c=0; c<15; c++)
	{
		writeDataL(error[c]);
	}
	writeCodeR(0xB9);
	writeCodeR(0x00);
	for(c=15; c<30; c++)
	{
		writeDataR(error[c]);
	}
	writeCodeL(0xBA);
	writeCodeL(0x4F-36);
	for(c=0; c<37; c++)
	{
		writeDataL(try_again[c]);
	}
	writeCodeR(0xBA);
	writeCodeR(0x00);
	for(c=37; c<74; c++)
	{
		writeDataR(try_again[c]);
	}
}

/*********************************************************************
 * Первый, начальны экран                                            *
 *********************************************************************/
void startScreen(void)
{
	/*writeCodeL(0xB8);
	writeCodeL(0x13 + 20);
	for(uint8_t i = 0; i < sizeof(one_small); i++)
	{
		writeDataL(one_small[i]);
	}
	writeCodeL(0xB8);
	writeCodeL(0x13 + 23);
	if(getStateCh_1() == CH_CLOSE)
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataL(lock_small[i]);
		}
	}
	else
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataL(0x00);
		}
	}

	writeCodeL(0xB8);
	writeCodeL(0x13 + 39);
	for(uint8_t i = 0; i < sizeof(two_small); i++)
	{
		writeDataL(two_small[i]);
	}
	writeCodeL(0xB8);
	writeCodeL(0x13 + 43);
	if(getStateCh_2() == CH_CLOSE)
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataL(lock_small[i]);
		}
	}
	else
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataL(0x00);
		}
	}

	writeCodeL(0xB8);
	writeCodeL(0x13 + 59);
	for(uint8_t i = 0; i < 2; i++)
	{
		writeDataL(three_small[i]);
	}
	writeCodeR(0xB8);
	writeCodeR(0x00);
	writeDataR(three_small[2]);
	writeCodeR(0xB8);
	writeCodeR(0x00 + 2);
	if(getStateCh_3() == CH_CLOSE)
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataR(lock_small[i]);
		}
	}
	else
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataR(0x00);
		}
	}

	writeCodeR(0xB8);
	writeCodeR(0x00 + 19);
	for(uint8_t i = 0; i < sizeof(four_small); i++)
	{
		writeDataR(four_small[i]);
	}
	writeCodeR(0xB8);
	writeCodeR(0x00 + 23);
	if(getStateCh_4() == CH_CLOSE)
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataR(lock_small[i]);
		}
	}
	else
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataR(0x00);
		}
	}

	writeCodeR(0xB8);
	writeCodeR(0x00 + 39);
	for(uint8_t i = 0; i < sizeof(five_small); i++)
	{
		writeDataR(five_small[i]);
	}
	writeCodeR(0xB8);
	writeCodeR(0x00 + 43);
	if(getStateCh_5() == CH_CLOSE)
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataR(lock_small[i]);
		}
	}
	else
	{
		for(uint8_t i = 0; i < sizeof(lock_small); i++)
		{
			writeDataR(0x00);
		}
	}*/
	getLcdHider();
	uint32_t keyboardValuie = getKeyboardCode();
	display_symb(1, keyboardValuie & 0xFF);
	display_symb(2, (keyboardValuie >> 8) & 0xFF);
	display_symb(3, (keyboardValuie >> 16) & 0xFF);
	display_symb(4, (keyboardValuie >> 24) & 0xFF);
}

/*********************************************************************
 * Экран принятия введенного общего пароля                           *
 *********************************************************************/
void genPasswordOkScreen(void)
{
	static uint8_t countRepiat = 0;
	switch(countEffects)
	{
		case 0:
		{
			countRepiat = 0;
			getLcdHider();
			uint32_t keyboardValuie = getKeyboardCode();
			display_symb(1, keyboardValuie & 0xFF);
			display_symb(2, (keyboardValuie >> 8) & 0xFF);
			display_symb(3, (keyboardValuie >> 16) & 0xFF);
			display_symb(4, (keyboardValuie >> 24) & 0xFF);
			startGTimer(TIMER_LCD_EFFECTS, 300);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				startGTimer(TIMER_LCD_EFFECTS, 500);
				clearLcdAllNoHider();
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				startGTimer(TIMER_LCD_EFFECTS, 500);
				uint32_t keyboardValuie = getKeyboardCode();
				display_symb(1, keyboardValuie & 0xFF);
				display_symb(2, (keyboardValuie >> 8) & 0xFF);
				display_symb(3, (keyboardValuie >> 16) & 0xFF);
				display_symb(4, (keyboardValuie >> 24) & 0xFF);
				countRepiat++;
				if(countRepiat < 1)
				{
					countEffects = 1;
				}
				else
				{
					restartGTimer(TIMER_LCD_EFFECTS, 500);
					countEffects++;
				}
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Вывод экрана выбора                                               *
 *********************************************************************/
void selectScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			//getLcdHider();
			displaynum(selectedCall, prevSelectedCall);
			//getLcdHider();
			countEffects++;
			break;
		}
		case 1:
		{
			flagEventOverLcd = TRUE;
			break;
		}
	}
}

/*********************************************************************
 * Вывод экрана подтверждения выбора                                 *
 *********************************************************************/
void selectedCellScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			displaynum_non_animate(getChChoiseValue());
			startGTimer(TIMER_LCD_EFFECTS, 300);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				clearLcdAllNoHider();
				startGTimer(TIMER_LCD_EFFECTS, 500);
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				displaynum_non_animate(getChChoiseValue());
				startGTimer(TIMER_LCD_EFFECTS, 500);
				countEffects++;
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Экран ввода пароля или получения ID карты                         *
 *********************************************************************/
void passwordCellScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			getLcdHider();
			display_header_inv(getChChoiseValue());
			countEffects++;
			break;
		}
		case 1:
		{
			uint32_t keyboardValuie = getKeyboardCode();
			display_symb(1, keyboardValuie & 0xFF);
			display_symb(2, (keyboardValuie >> 8) & 0xFF);
			display_symb(3, (keyboardValuie >> 16) & 0xFF);
			display_symb(4, (keyboardValuie >> 24) & 0xFF);
			break;
		}
	}

}

/*********************************************************************
 * Экран анимации счетывания ID карты                                *
 *********************************************************************/
void nfcReadScreen(void)
{
	//getLcdHider();
	//display_header_inv(getChChoiseValue());
	switch(countEffects)
	{
		case 0:
		{
			getLcdHider();
			display_header_inv(getChChoiseValue());
			display_nfc(0);
			startGTimer(TIMER_LCD_EFFECTS, 200);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(1);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(2);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(3);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 4:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(4);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 5:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(5);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 6:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Экран анимации счетывания ID карты                                *
 *********************************************************************/
void nfcReadServiceScreen(void)
{
	//getLcdHider();
	//display_header_inv(getChChoiseValue());
	switch(countEffects)
	{
		case 0:
		{
			display_nfc(0);
			startGTimer(TIMER_LCD_EFFECTS, 200);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(1);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(2);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(3);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 4:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(4);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 5:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_nfc(5);
				startGTimer(TIMER_LCD_EFFECTS, 200);
				countEffects++;
			}
			break;
		}
		case 6:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Экран подтверждени принятия пароля                                *
 *********************************************************************/
void passwordOkScreen(void)
{
	static uint8_t countRepiat = 0;
	switch(countEffects)
	{
		case 0:
		{
			countRepiat = 0;
			getLcdHider();
			display_header_inv(getChChoiseValue());
			uint32_t keyboardValuie = getKeyboardCode();
			display_symb(1, keyboardValuie & 0xFF);
			display_symb(2, (keyboardValuie >> 8) & 0xFF);
			display_symb(3, (keyboardValuie >> 16) & 0xFF);
			display_symb(4, (keyboardValuie >> 24) & 0xFF);
			startGTimer(TIMER_LCD_EFFECTS, 300);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				startGTimer(TIMER_LCD_EFFECTS, 500);
				clearLcdAllNoHider();
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				startGTimer(TIMER_LCD_EFFECTS, 500);
				uint32_t keyboardValuie = getKeyboardCode();
				display_symb(1, keyboardValuie & 0xFF);
				display_symb(2, (keyboardValuie >> 8) & 0xFF);
				display_symb(3, (keyboardValuie >> 16) & 0xFF);
				display_symb(4, (keyboardValuie >> 24) & 0xFF);
				countRepiat++;
				if(countRepiat < 1)
				{
					countEffects = 1;
				}
				else
				{
					restartGTimer(TIMER_LCD_EFFECTS, 500);
					countEffects++;
				}
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Вавод сообщения входа в сервисное меню                            *
 *********************************************************************/
void serviceMain(void)
{
	switch(countEffects)
	{
		case 0:
		{
			clearLcd();
			writeCodeL(0xB9);
			writeCodeL(0x4F-40);
			for(uint8_t i = 0; i < 41; i++)
			{
				writeDataL(service_mode[i]);
			}
			writeCodeR(0xB9);
			writeCodeR(0x00);
			for(uint8_t i = 41; i < sizeof(service_mode); i++)
			{
				writeDataR(service_mode[i]);
			}
			startGTimer(TIMER_LCD_EFFECTS, 2000);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Сервисный экранн ввода общего кода                                *
 *********************************************************************/
void serviceEnterGenPassvordScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			clearLcdHider();
			writeCodeL(0xB8);
			writeCodeL(0x35);
			for(uint8_t i = 0; i < 27; i++)
			{
				writeDataL(general_code[i]);
			}
			writeCodeR(0xB8);
			writeCodeR(0x00);
			for(uint8_t i = 27; i < sizeof(general_code); i++)
			{
				writeDataR(general_code[i]);
			}
			clearLcdAllNoHider();
			countEffects++;
			break;
		}
		case 1:
		{
			uint32_t keyboardValuie = getKeyboardCode();
			display_symb(1, keyboardValuie & 0xFF);
			display_symb(2, (keyboardValuie >> 8) & 0xFF);
			display_symb(3, (keyboardValuie >> 16) & 0xFF);
			display_symb(4, (keyboardValuie >> 24) & 0xFF);
			break;
		}
	}
}

/*********************************************************************
 * Вывод цифр от 1 до 9 и * в центре экрана                          *
 *********************************************************************/
void displaynumAndStar(uint8_t num)
{
	uint8_t	p;
	uint8_t	c;
	//clearLcd();
	//clearLcdAllNoHider();
	if (num==0)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(null[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(null[p-1][c]);
			}
		}
	}
	if (num==1)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(one[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(one[p-1][c]);
			}
		}
	}
	else if (num==2)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(two[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(two[p-1][c]);
			}
		}
	}
	else if (num==3)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
			writeDataL(three[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(three[p-1][c]);
			}
		}
	}
	else if (num==4)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(four[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(four[p-1][c]);
			}
		}
	}
	else if (num==5)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(five[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(five[p-1][c]);
			}
		}
	}
	else if (num==6)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(six[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(six[p-1][c]);
			}
		}
	}
	else if (num==7)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(seven[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(seven[p-1][c]);
			}
		}
	}
	else if (num==8)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(eight[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(eight[p-1][c]);
			}
		}
	}
	else if (num==9)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(nine[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(nine[p-1][c]);
			}
		}
	}
	else if (num==0xFF)
	{
		for(p=1; p<4; p++)
		{
			writeCodeL(p|0xB8);
			writeCodeL(0x49);
			for(c=0; c<7; c++)
			{
				writeDataL(zvezda[p-1][c]);
			}
			writeCodeR(p|0xB8);
			writeCodeR(0x00);
			for(c=7; c<14; c++)
			{
				writeDataR(zvezda[p-1][c]);
			}
		}
	}
}

/*********************************************************************
 * Вывод экрана установки времени заряда                             *
 *********************************************************************/
void serviceEnterHourChargeScreen(void)
{

	switch(countEffects)
	{
		case 0:
		{
			clearLcdHider();
			writeCodeL(0xB8);
			writeCodeL(0x29);
			for(uint8_t i = 0; i < 38; i++)
			{
				writeDataL(time_charge[i]);
			}
			writeCodeR(0xB8);
			writeCodeR(0x00);
			for(uint8_t i = 38; i < sizeof(time_charge); i++)
			{
				writeDataR(time_charge[i]);
			}
			clearLcdAllNoHider();
			countEffects++;
			break;
		}
		case 1:
		{
			displaynumAndStar(getKeyboardCode());
			//countEffects++;
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Вывод сообщения о сохранении                                      *
 *********************************************************************/
void savedScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			writeCodeL(0x4F-24);
			for(uint8_t i = 0; i < 25; i++)
			{
				writeDataL(saved[i]);
			}
			writeCodeR(0xB9);
			writeCodeR(0x00);
			for(uint8_t i = 25; i < sizeof(saved); i++)
			{
				writeDataR(saved[i]);
			}
			startGTimer(TIMER_LCD_EFFECTS, 2000);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Вывод эерана считывания мастер карты NFC                          *
 *********************************************************************/
void serviceEnterNfcMasterScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			clearLcdHider();
			writeCodeL(0xB8);
			writeCodeL(0x30);
			for(uint8_t i = 0; i < 31; i++)
			{
				writeDataL(master_key[i]);
			}
			writeCodeR(0xB8);
			writeCodeR(0x00);
			for(uint8_t i = 31; i < sizeof(master_key); i++)
			{
				writeDataR(master_key[i]);
			}
			clearLcdAllNoHider();
			writeCodeL(0xB9);
			writeCodeL(0x2F);
			for(uint8_t i = 0; i < 33; i++)
			{
				writeDataL(expect_key[i]);
			}
			writeCodeR(0xB9);
			writeCodeR(0x00);
			for(uint8_t i = 33; i < sizeof(expect_key); i++)
			{
				writeDataR(expect_key[i]);
			}
			countEffects++;
			break;
		}
		case 1:
		{
			break;
		}
	}
}

/*********************************************************************
 * Вывод сообщения о ошибки на LCD                                   *
 *********************************************************************/
void errorScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			getLcdHider();
			display_try_again();
			startGTimer(TIMER_LCD_EFFECTS, 1000);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				clearLcdAllNoHider();
				startGTimer(TIMER_LCD_EFFECTS, 500);
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_try_again();
				restartGTimer(TIMER_LCD_EFFECTS, 1000);
				countEffects++;
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Вывод сообщения о ошибке при неправильном коде или ID карты       *
 *********************************************************************/
void errorPassScreen(void)
{
	switch(countEffects)
	{
		case 0:
		{
			getLcdHider();
			display_header_inv(getChChoiseValue());
			display_try_again();
			startGTimer(TIMER_LCD_EFFECTS, 1000);
			countEffects++;
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				clearLcdAllNoHider();
				startGTimer(TIMER_LCD_EFFECTS, 500);
				countEffects++;
			}
			break;
		}
		case 2:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				display_try_again();
				restartGTimer(TIMER_LCD_EFFECTS, 1000);
				countEffects++;
			}
			break;
		}
		case 3:
		{
			if(getGTimer(TIMER_LCD_EFFECTS).stateFlag == fTrue)
			{
				flagEventOverLcd = TRUE;
			}
			break;
		}
	}
}

/*********************************************************************
 * Вывод данных на LCD                                               *
 *********************************************************************/
void lcdTask(void)
{
	switch(scrinNumberValue)
	{
		case START_SCREEN: // Начальный экран (Экаран ввода общего кода)
		{
			startScreen();
			break;
		}

		case GEN_PASSWORD_OK_SCREEN: // Экран подтверждения введенного кода
		{
			genPasswordOkScreen();
			break;
		}

		case SELECT_SCREEN:	// Экран выбора ячейки для открытия или закрытия
		{
			selectScreen();
			break;
		}

		case SELECT_CELL_SCREEN: // Экран подтверждения выбора ячейки
		{
			selectedCellScreen();
			break;
		}

		case PASSWORD_CELL_SCREEN: // Экран ввода кода и ожидания получения ID  карты
		{
			passwordCellScreen();
			break;
		}

		case NFC_READ_SCREEN:	// Экран анимации счетывания ID карты
		{
			nfcReadScreen();
			break;
		}

		case OPEN_SCREEN: // Экран анмации открытия
		{
			animate_lock(1);
			break;
		}

		case CLOSE_SCREEN: // Экран анмации закрытия
		{
			animate_lock(0);
			break;
		}

		case PASSWORD_OK_SCREEN:
		{
			passwordOkScreen();
			break;
		}

		case ERROR_SCREEN: // Вывод сообщения ошибки ввода кода
		{
			errorScreen();
			//displaynum(1, 2);
			break;
		}

		case SERVICE_MEIN:
		{
			serviceMain();
			break;
		}

		case SERVICE_ENTER_GEN_PASSWORD_SCREEN:
		{
			serviceEnterGenPassvordScreen();
			break;
		}

		case SERVICE_ENTER_HOUR_CHARGE_SCREEN:
		{
			serviceEnterHourChargeScreen();
			break;
		}

		case SERVICE_SAVED_SCREEN:
		{
			savedScreen();
			break;
		}

		case SERVICE_ENTER_NFC_MASTER_SCREEN:
		{
			serviceEnterNfcMasterScreen();
			break;
		}

		case SERVICE_NFC_SCREEN:
		{
			nfcReadServiceScreen();
			break;
		}

		case ERROR_PASS_SCREEN: // Экран ошибки ввола пароля открытия ячейки
		{
			errorPassScreen();
			break;
		}
	}
}
