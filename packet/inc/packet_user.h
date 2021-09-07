#ifndef __PACKET_USER_H__
#define __PACKET_USER_H__

#include <stdint.h>

#define BUF_SIZE 512
#define NUM_OF_CMD 3

#define USE_LENGTH
#define USE_SEQNUM
#define USE_COMMAND
#define USE_ENDBYTE
#define USE_CRC

#define HEADER_TYPE uint8_t
#define SEQNUM_TYPE uint8_t
#define LENGTH_TYPE uint8_t
#define COMMAND_TYPE uint8_t
#define ENDBYTE_TYPE uint8_t
#define CRC_TYPE uint8_t

#define PACKET_HEADER 0xAA
#define PACKET_ENDBYTE 0xED

typedef struct __SampleData1 {
    uint8_t name[3];
    uint8_t text[12];
} UserData1;

typedef struct __SampleData2 {
    uint8_t h;
    uint8_t m;
    uint8_t s;
} UserData2;

#endif