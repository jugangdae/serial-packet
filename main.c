#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include"packet.h"
#include"packet_user.h"

int main(){
	uint8_t *buf;
	UserData userdata;
	memset(&userdata, 0, sizeof(UserData));
	Packet *pk = createPacket();
	
	setPacketHeader(pk, 0xAA);
	setPacketCommnad(pk, 0x01);
	setPacketData(pk, &userdata);
	setPacketCrc(pk, 0xff);
	setPacketLegnth(pk, calcPacketSize(pk, sizeof(userdata)));
	
	printf("size: %d\n",pk->length);
	
	buf = (uint8_t*)malloc(sizeof(uint8_t)*pk->length);
	pack(pk, buf);

	int i;
	for(i=0; i<pk->length; i++){
		printf("%x ", *(buf+i));
	}
	printf("\n\n");

	printf("pk reset..\n");
	memset(&userdata, 0, sizeof(userdata));
	memset(pk, 0, sizeof(pk));
	setPacketData(pk, &userdata);

	unpack(buf, pk);

	printf("pk.header :%x \n", pk->header);
	printf("pk.lenght :%u \n", getPacketLegnth(pk));
	printf("pk.command :%x \n", getPacketCommnad(pk));
	printf("pk.crc :%x \n", getPacketCrc(pk));

	return 0;
}