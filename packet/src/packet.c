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
void setPacketHeader(Packet *pk, pk_hdr_t header){
	pk->header = header;
}
pk_hdr_t getPacketHeader(Packet *pk){
	return pk->header;
}

#ifdef USE_SEQNUM
void setPacketSeqnum(Packet *pk, pk_seq_t seqnum){
	pk->seqnum = seqnum;
}
pk_seq_t getPacketSeqnum(Packet *pk){
	return pk->seqnum;
}
#endif

#ifdef USE_LENGTH
void setPacketLegnth(Packet *pk, pk_len_t length){
	pk->length = length;
}
pk_len_t getPacketLegnth(Packet *pk){
	return pk->length;
}
#endif

#ifdef USE_COMMAND	
void setPacketCommnad(Packet *pk, pk_cmd_t command){
	pk->command = command;
}
pk_cmd_t getPacketCommnad(Packet *pk){
	return pk->command;
}
#endif

void setPacketData(Packet *pk, void *data){
	pk->data = (uint8_t*)data;
}
void getPacketData(Packet *pk, void *data){
	data = pk->data;
}

#ifdef USE_ENDBYTE
void setPacketEndbyte(Packet *pk, pk_end_t endbtye){
	pk->endbtye = endbtye;
}
pk_end_t getPacketEndbyte(Packet *pk){
	return pk->endbtye;
}
#endif

#ifdef USE_CRC
void setPacketCrc(Packet *pk, pk_crc_t crc){
	pk->crc = crc;
}
pk_crc_t getPacketCrc(Packet *pk){
	return pk->crc;
}
#endif

size_t calcPacketSize(Packet *pk, size_t data_size){
	size_t len = sizeof(pk->header)
#ifdef USE_SEQNUM
    + sizeof(pk->seqnum)
#endif
#ifdef USE_LENGTH
    + sizeof(pk->length)
#endif
#ifdef USE_COMMAND
	+ sizeof(pk->command)
#endif
	+ data_size
#ifdef USE_ENDBYTE
    + sizeof(pk->endbtye)
#endif
#ifdef USE_CRC
	+ sizeof(pk->crc);
#endif
	return len;
}

void pack(Packet *pk, uint8_t *buf){
	//if(buf)
	//	free(buf);
	//buf = (uint8_t*)malloc(sizeof(uint8_t)*pk->length);
	memset(buf, 0, BUF_SIZE);
	memcpy(buf, &(pk->header), sizeof(pk->header));
	buf += sizeof(pk->header);

#ifdef USE_SEQNUM
	memcpy(buf, &(pk->seqnum), sizeof(pk->seqnum));
	buf += sizeof(pk->seqnum);
#endif

#ifdef USE_LENGTH
	memcpy(buf, &(pk->length), sizeof(pk->length));
	buf += sizeof(pk->length);
#endif

#ifdef USE_COMMAND
    memcpy(buf, &(pk->command), sizeof(pk->command));
	buf += sizeof(pk->command);
#endif

	memcpy(buf, pk->data, pk->length
        - sizeof(pk->header) 
#ifdef USE_SEQNUM
		- sizeof(pk->seqnum)
#endif
#ifdef USE_LENGTH
		- sizeof(pk->length)
#endif
#ifdef USE_COMMAND
		- sizeof(pk->command)
#endif
#ifdef USE_ENDBYTE
		- sizeof(pk->endbtye)
#endif
#ifdef USE_CRC
		- sizeof(pk->crc)
#endif
	);

	buf += pk->length
        - sizeof(pk->header) 
#ifdef USE_SEQNUM
		- sizeof(pk->seqnum)
#endif
#ifdef USE_LENGTH
		- sizeof(pk->length)
#endif
#ifdef USE_COMMAND
		- sizeof(pk->command)
#endif
#ifdef USE_ENDBYTE
		- sizeof(pk->endbtye)
#endif
#ifdef USE_CRC
		- sizeof(pk->crc)
#endif
	;

#ifdef USE_ENDBYTE
    memcpy(buf, &(pk->endbtye), sizeof(pk->endbtye));
	buf += sizeof(pk->endbtye);
#endif

#ifdef USE_CRC
    memcpy(buf, &(pk->crc), sizeof(pk->crc));
	buf += sizeof(pk->crc);
#endif
	buf = buf - pk->length;
}

void unpack(uint8_t *buf, Packet *pk, uint32_t *map[]){
    memcpy(&(pk->header), buf, sizeof(pk->header));
	buf += sizeof(pk->header);

#ifdef USE_SEQNUM
	memcpy(&(pk->seqnum), buf, sizeof(pk->seqnum));
	buf += sizeof(pk->seqnum);
#endif

#ifdef USE_LENGTH
	memcpy(&(pk->length), buf, sizeof(pk->length));
	buf += sizeof(pk->length);
#endif

#ifdef USE_COMMAND
    memcpy(&(pk->command), buf, sizeof(pk->command));
	buf += sizeof(pk->command);
#endif

	memcpy(pk->data, buf, pk->length
		- sizeof(pk->header) 
#ifdef USE_SEQNUM
		- sizeof(pk->seqnum)
#endif
#ifdef USE_LENGTH
		- sizeof(pk->length)
#endif
#ifdef USE_COMMAND
		- sizeof(pk->command)
#endif
#ifdef USE_ENDBYTE
		- sizeof(pk->endbtye)
#endif
#ifdef USE_CRC
		- sizeof(pk->crc)
#endif
	);

	buf += pk->length
        - sizeof(pk->header) 
#ifdef USE_SEQNUM
		- sizeof(pk->seqnum)
#endif
#ifdef USE_LENGTH
		- sizeof(pk->length)
#endif
#ifdef USE_COMMAND
		- sizeof(pk->command)
#endif
#ifdef USE_ENDBYTE
		- sizeof(pk->endbtye)
#endif
#ifdef USE_CRC
		- sizeof(pk->crc)
#endif
	;

#ifdef USE_ENDBYTE
    memcpy(&(pk->endbtye), buf, sizeof(pk->endbtye));
	buf += sizeof(pk->endbtye);
#endif

#ifdef USE_CRC
    memcpy(&(pk->crc), buf, sizeof(pk->crc));
	buf += sizeof(pk->crc);
#endif
	buf = buf - pk->length;
}