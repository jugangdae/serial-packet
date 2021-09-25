#ifndef _CRC8_H_
#define _CRC8_H_
#include <stdint.h>
void init_crc8();

uint8_t crc8(uint8_t *data, uint32_t length);
#endif
