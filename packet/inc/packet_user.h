#ifndef __PACKET_USER_H__
#define __PACKET_USER_H__

#include<stdint.h>

#define BUF_SIZE 100

#define USE_LENGTH
#define USE_COMMAND
#define USE_CRC

#define USE_ENDBYTE
#define USE_SEQNUM

typedef uint8_t pk_hdr_t;
typedef uint8_t pk_seq_t;
typedef uint8_t pk_len_t;
typedef uint8_t pk_cmd_t;
typedef uint8_t pk_end_t;
typedef uint8_t pk_crc_t;

// typedef uint16_t pk_hdr_t;
// typedef uint16_t pk_seq_t;
// typedef uint16_t pk_len_t;
// typedef uint16_t pk_cmd_t;
// typedef uint16_t pk_end_t;
// typedef uint16_t pk_crc_t;

typedef struct __SampleData1{
	uint8_t name[3];
	uint8_t text[12];
}UserData;

typedef struct __SampleData2{
	uint8_t h;
	uint8_t m;
	uint8_t s;
}UserData2;



	// void setUserDataName(UserData *userdata, uint8_t* data);
	// void getUserName(Packet *userdata, uint8_t* data);
#endif