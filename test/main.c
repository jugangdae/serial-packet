#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include"packet.h"
#include"packet_user.h"

void check_status(int n, Packet *pk, uint8_t *buf){
	/* Check status */
	printf("check status : %d\n", n);
	printf("---------------------------------------\n");
	printf("pk.header : 0x%x \n",  getPacketHeader(pk));
	printf("pk.seqnum : 0x%x \n", getPacketSeqnum(pk));
	printf("pk.lenght : 0x%x \n", getPacketLegnth(pk));
	printf("pk.command : 0x%x \n", getPacketCommnad(pk));
	if(getPacketCommnad(pk) == 0x1){
		printf("pk.data.name : %s \n", ((UserData*)pk->data)->name);
		printf("pk.data.text : %s \n", ((UserData*)pk->data)->text);
	}else if(getPacketCommnad(pk) == 0x2){
		printf("pk.data.h : %d \n", ((UserData2*)pk->data)->h);
		printf("pk.data.s : %d \n", ((UserData2*)pk->data)->m);
		printf("pk.data.m : %d \n", ((UserData2*)pk->data)->s);
	}
	printf("pk.endbyte : 0x%x \n", getPacketEndbyte(pk));
	printf("pk.crc : 0x%x \n", getPacketCrc(pk));
	printf("buf(hex) : \n");
	int i;
	int max = BUF_SIZE; 
	for(i=0; i< max; i++){
		if(i == sizeof(pk->header)+sizeof(pk->seqnum))
		max = *(buf+i);
		printf("%02x ", *(buf+i));
		if((i+1)%8 == 0)printf("\n");
		else if((i+1)%4 == 0)printf(" ");
		 
	}
	printf("\n");
	printf("---------------------------------------\n\n");
}

int main(){

	/* Declarate variables */
	uint8_t *buf;
	Packet *pk = createPacket();
	UserData userdata;
	UserData2 userdata2;

	/* Init userdata */
	printf("init userdata..\n");
	memset(&userdata, 0, sizeof(UserData));
	memcpy(userdata.name,"JU\0", 3);
	memcpy(userdata.text,"HELLO WORLD\0", 12);


	/* Init packet */
	printf("init packet..\n");
	setPacketHeader(pk, 0xA);
	setPacketSeqnum(pk, 0xB);
	setPacketCommnad(pk, 0x1);
	setPacketData(pk, &userdata);
	setPacketEndbyte(pk, 0xD);
	setPacketCrc(pk, 0xE);
	setPacketLegnth(pk, calcPacketSize(pk, sizeof(userdata)));

	/* Check status 1 */
	check_status(1, pk, buf);

	
	/* Packing */
	printf("packing..\n");
	pack(pk, buf);

	/* Check status 2 */
	check_status(2, pk, buf);

	/* Clear all */
	printf("clear packet..\n");
	memset(&userdata, 0, sizeof(userdata));
	memset(pk, 0, sizeof(pk));
	memset(pk, 0, sizeof(pk));
	setPacketData(pk, &userdata);

	/* Init buf*/

	/* Check status 3 */
	check_status(3, pk, buf);

	/* Unpacking */
	printf("unpacking..\n");
	unpack(buf, pk, map);

	/* Check status 3 */
	check_status(3, pk, buf);

	return 0;
}