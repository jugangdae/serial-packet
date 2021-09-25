#include <crc8.h>

/*
 * CRC-8:
 *
 * Width:   8
 * Poly:    0x07
 * Init:    0x00
 * RefIn:   False
 * RefOut:  False
 * XOROur:  0x00
 * Check:   0xF4
 */
#define true 1
#define false 0

static const uint8_t CRC8_POLY = 0x07;
static uint8_t crc8_initialized = false;

static uint8_t crc8_table[256];


void init_crc8()
{
    uint8_t msb = 1 << 7;
    uint8_t bit;
    uint8_t rem;
    uint32_t byte = 0;

    if (crc8_initialized)
        return;

    while (byte < 256) {
        rem = byte;
        for (bit = 0; bit < 8; bit++) {
            if (rem & msb)
                rem = (rem << 1) ^ CRC8_POLY;
            else
                rem <<= 1;
        }

        crc8_table[byte++] = rem;
    }

    crc8_initialized = true;
}

uint8_t crc8(uint8_t *data, uint32_t length)
{
    uint8_t crc = 0x00;
    uint32_t msg_idx = 0;

    if (length == 0xFFFFFFFF)
        return 0;

    init_crc8();

    while (msg_idx < length) {
        crc = crc8_table[crc ^ data[msg_idx++]];
    }

    return crc;
}
