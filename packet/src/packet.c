#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"packet.h"
#include"packet_user.h"

Packet* createPacket(){
	Packet *pk = (Packet*)malloc(sizeof(Packet));
	memset(pk, 0, sizeof(Packet));
	return pk;
}
void deletePacket(Packet *pk){
	free(pk->data);
	free(pk);
}
void setPacketHeader(Packet *pk, uint8_t header){
	pk->header = header;
}
void setPacketLegnth(Packet *pk, uint8_t length){
	pk->length = length;
}
void setPacketCommnad(Packet *pk, uint8_t command){
	pk->command = command;
}
void setPacketData(Packet *pk, void *data){
	pk->data = data;
}
void setPacketCrc(Packet *pk, uint8_t crc){
	pk->crc = crc;
}
uint8_t getPacketHeader(Packet *pk){
	return pk->header;
}
uint8_t getPacketLegnth(Packet *pk){
	return pk->length;
}
uint8_t getPacketCommnad(Packet *pk){
	return pk->command;
}
void getPacketData(Packet *pk, uint8_t *data){
	data = pk->data;
}
uint8_t getPacketCrc(Packet *pk){
	return pk->crc;
}
size_t calcPacketSize(Packet *pk, size_t data_size){
	size_t len = sizeof(pk->header)
	+ sizeof(pk->length)
	+ sizeof(pk->command)
	+ data_size
	+ sizeof(pk->crc);
	return len;
}
void pack(Packet *pk, uint8_t *buf){
	//buf = (uint8_t*)malloc(sizeof(uint8_t*) * pk->length);
	*(buf++) = pk->header;
	*(buf++) = pk->length;
	*(buf++) = pk->command;
	memcpy(buf, pk->data, pk->length
		- sizeof(pk->length)
		- sizeof(pk->header) 
		- sizeof(pk->command)
		- sizeof(pk->crc));
	buf += pk->length
		- sizeof(pk->header) 
		- sizeof(pk->length)
		- sizeof(pk->command)
		- sizeof(pk->crc);
	*(buf++) = pk->crc;
	buf = buf - pk->length;
}
void unpack(uint8_t *buf, Packet *pk){
	pk->header = *(buf++);
	pk->length = *(buf++);
	pk->command = *(buf++);
	memcpy(pk->data, buf, pk->length
		- sizeof(pk->header) 
		- sizeof(pk->length)
		- sizeof(pk->command)
		- sizeof(pk->crc));
	buf += pk->length
		- sizeof(pk->length)
		- sizeof(pk->header) 
		- sizeof(pk->command)
		- sizeof(pk->crc);
	pk->crc = *(buf++);
	buf = buf - pk->length;
}