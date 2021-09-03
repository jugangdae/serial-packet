#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

#define PACKET_HEAD 3
#define PACKET_TAIL 1

typedef struct __Coord{
	uint8_t x;
	uint8_t y;
	uint8_t z;
}Coord;

typedef struct __Message{
	uint8_t name[10];
	uint8_t text[30];
}Message;

typedef struct __Packet{
	uint8_t header;
	//uint8_t sequenceNumber;
	uint8_t length;
	uint8_t command;
	uint8_t *data;
	//uint8_t endByte;
	uint8_t crc ;
}Packet;

void main(){

	/* create variables */
	uint8_t *buf;
	Packet pk;
	Message data2;

	/* init userdata */
	memset(&data2, 0, sizeof(data2));
	strcpy(data2.name, "ABCDEF");
	strcpy(data2.text, "abcdef");

	/* init packet*/
	pk.header = 0xAA;
	pk.command = 0x01;
	pk.data = (uint8_t*)(&data2);
	pk.length =	sizeof(pk.header)
				+ sizeof(pk.length)
				+ sizeof(pk.command)
				+ sizeof(data2)
				+ sizeof(pk.crc);
	pk.crc = 0xFF;

	/* print packet */

	printf("pk.header :%x \n", pk.header);
	printf("pk.lenght :%u \n", pk.length);
	printf("pk.command :%x \n", pk.command);
	printf("pk.data.name :%s \n", ((Message*)(pk.data))->name);
	printf("pk.data.text :%s \n", ((Message*)(pk.data))->text);
	printf("pk.crc :%u \n", pk.crc);

	printf("pk size :%u \n\n", sizeof(pk));

	/* packing.. */
	int i;
	buf = (uint8_t*)malloc(sizeof(uint8_t*) * pk.length);
	*(buf++) = pk.header;
	*(buf++) = pk.length;
	*(buf++) = pk.command;
	memcpy(buf, pk.data, pk.length
		- sizeof(pk.length)
		- sizeof(pk.header) 
		- sizeof(pk.command)
		- sizeof(pk.crc));
	buf += pk.length
		- sizeof(pk.header) 
		- sizeof(pk.length)
		- sizeof(pk.command)
		- sizeof(pk.crc);
	*(buf++) = pk.crc;
	buf = buf - pk.length;

	/* print packet */
	printf("buf: ");
	for(i=0; i<pk.length; i++){
		printf("%x ", *(buf+i));
	}
	printf("\n\n");

	/* reset pk */
	printf("pk reset..\n");
	memset(&data2, 0, sizeof(data2));
	memset(&pk, 0, sizeof(pk));
	pk.data = (uint8_t*)(&data2);

	printf("pk.header :%x \n", pk.header);
	printf("pk.lenght :%u \n", pk.length);
	printf("pk.command :%x \n", pk.command);
	printf("pk.data.name :%s \n", ((Message*)(pk.data))->name);
	printf("pk.data.text :%s \n", ((Message*)(pk.data))->text);
	printf("pk.crc :%u \n", pk.crc);

	printf("pk size :%u \n\n", sizeof(pk));

	/* unpacking.. */
	pk.header = *(buf++);
	pk.length = *(buf++);
	pk.command = *(buf++);
	memcpy(pk.data, buf, pk.length
		- sizeof(pk.header) 
		- sizeof(pk.length)
		- sizeof(pk.command)
		- sizeof(pk.crc));
	buf += pk.length
		- sizeof(pk.length)
		- sizeof(pk.header) 
		- sizeof(pk.command)
		- sizeof(pk.crc);
	pk.crc = *(buf++);
	buf = buf - pk.length;

	printf("pk.header :%x \n", pk.header);
	printf("pk.lenght :%u \n", pk.length);
	printf("pk.command :%x \n", pk.command);
	printf("pk.data.name :%s \n", ((Message*)(pk.data))->name);
	printf("pk.data.text :%s \n", ((Message*)(pk.data))->text);
	printf("pk.crc :%u \n", pk.crc);

	printf("pk size :%u \n\n", sizeof(pk));
	/*
	int i;
	uint8_t *buf;

	Payload pl;
	Packet pk;

	Coord data1;
	Message data2;

	data1.x = 100;
	data1.y = 150;
	data1.z = 30;
	
	pk.header = 0xAA;
	pk.command = 0x01;
	pl.data = (uint8_t*)(&data1);
	pl.length = sizeof(data1) + 2;

    printf("data1.x :%u \n", data1.x);
	printf("data1.y :%u \n", data1.y);
	printf("data1.z :%u \n", data1.z);
	printf("data1 size :%u \n\n", sizeof(data1));
	
	printf("pl.data.x :%u \n", ((Coord*)(pl.data))->x);
	printf("pl.data.y :%u \n", ((Coord*)(pl.data))->y);
	printf("pl.data.z :%u \n", ((Coord*)(pl.data))->z);

	printf("pl.command :%x \n", pl.command);
	printf("pl.lenght :%u \n", pl.length);
	printf("pl size :%u \n\n", sizeof(pl));

	buf = (uint8_t*)(&pl);
	printf("buf: ");
	for(i=0; i<pl.length; i++){
		printf("%x ", *buf);
		buf++;
	}
	printf("\n\n");

	memset(&data2, 0, sizeof(Message));
	strcpy(data2.name,"AAA");
	strcpy(data2.text,"BBBBBBB");

	pl.command = 0xBB;
	pl.data = (uint8_t*)(&data2);
	pl.length = sizeof(data2) + 2;

    printf("data2.name :%s \n", data2.name);
	printf("data2.text :%s \n", data2.text);
	printf("data2 size :%u \n\n", sizeof(data2));
	
	printf("pl.data.name :%s \n", ((Message*)(pl.data))->name);
	printf("pl.data.text :%s \n", ((Message*)(pl.data))->text);

	printf("pl.command :%x \n", pl.command);
	printf("pl.lenght :%u \n", pl.length);
	printf("pl size :%u \n\n", sizeof(pl));

	buf = (uint8_t*)(&pl);
	printf("buf: ");
	for(i=0; i<pl.length; i++){
		printf("%x ", *buf);
		buf++;
	}
	printf("\n\n");

	 buf = (uint8_t*)malloc(sizeof(uint8_t*) * pl.length);
	*(buf++) = pl.length;
	*(buf++) = pl.command;
	for(i=0; i<pl.length-2; i++){
		uint8_t *tmp = (uint8_t*)pl.data;
		*(buf++) = *(tmp + i);
	}
	buf = buf - pl.length;
	for(i=0; i<pl.length; i++){
		printf("%x ", *buf);
		buf++;
	}
	printf("\n\n");
	*/
}