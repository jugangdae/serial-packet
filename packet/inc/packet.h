#ifndef __PACKET_H__
#define __PACKET_H__

#include<stdint.h>
#include"packet_user.h"

#define USE_LENGTH
#define USE_COMMAND
//#define USE_ENDBYTE
#define USE_CRC

#define LENGTH_TYPE 8
#define CRC_TYPE 8

#define PACKET_HEAD_SIZE 2
#define PACKET_TAIL_SIZE 1
#define PACKET_CMD_SIZE 1

typedef struct __Packet{
	uint8_t header;
	//uint8_t sequenceNumber;
	uint8_t length;
	uint8_t command;
	uint8_t *data;
	//uint8_t endByte;
	uint8_t crc ;

}Packet;

/* Packet function*/
Packet* createPacket();
void deletePacket(Packet *pk);
void setPacketHeader(Packet *pk, uint8_t header);
void setPacketLegnth(Packet *pk, uint8_t length);
void setPacketCommnad(Packet *pk, uint8_t command);
void setPacketData(Packet *pk, void *data);
void setPacketCrc(Packet *pk, uint8_t crc);
uint8_t getPacketHeader(Packet *pk);
uint8_t getPacketLegnth(Packet *pk);
uint8_t getPacketCommnad(Packet *pk);
void getPacketData(Packet *pk, uint8_t *data);
uint8_t getPacketCrc(Packet *pk);
size_t calcPacketSize(Packet *pk, size_t data_len);

void pack(Packet *pk, uint8_t *buf);
void unpack(uint8_t *buf, Packet *pk);
void printPacket(Packet *pk);

#endif