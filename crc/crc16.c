/*  
 * crc16.c
 * 
 * Computes a 16-bit CRC 
 * http://www.rajivchakravorty.com/source-code/uncertainty/multimedia-sim/html/crc16_8c-source.html
 */

#include <stdio.h>
#include <stdint.h>

#define GP 0x11021                      /* x^16 + x^12 + x^5 + 1 */
#define DI 0x1021

static uint16_t crc16_table[256];       /* 16-bit table */
static int made_table=0;

static void init_crc16()
{
    int i,j;
    uint16_t crc;
    
    if (!made_table) {
        for (i=0; i<256; i++) {
            crc = (i << 8);
            for (j=0; j<8; j++)
                crc = (crc << 1) ^ ((crc & 0x8000) ? DI : 0);
            crc16_table[i] = crc & 0xFFFF;
            /* printf("table[%d] = %d (0x%X)\n", i, crc, crc); */
        }
        made_table=1;
    }
}

void crc16(uint16_t *crc, unsigned char m)
     /*
      * For a byte array whose accumulated crc value is stored in *crc, computes
      * resultant crc obtained by appending m to the byte array
      */
{
    if (!made_table)
        init_crc16();
    *crc = crc16_table[(((*crc) >> 8) ^ m) & 0xFF] ^ ((*crc) << 8);
    *crc &= 0xFFFF;
}