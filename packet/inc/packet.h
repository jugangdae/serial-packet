#ifndef __PACKET_H__
#define __PACKET_H__

#include <stddef.h>
#include <stdint.h>

#include "packet_user.h"

typedef uint64_t pointer_t;

typedef HEADER_TYPE pk_hdr_t;
typedef SEQNUM_TYPE pk_seq_t;
typedef LENGTH_TYPE pk_len_t;
typedef COMMAND_TYPE pk_cmd_t;
typedef ENDBYTE_TYPE pk_end_t;
typedef CRC_TYPE pk_crc_t;

#ifdef USE_COMMAND
pointer_t cmd_map[NUM_OF_CMD];
#endif

typedef struct __Packet {
    pk_hdr_t header;

#ifdef USE_SEQNUM
    pk_seq_t seqnum;
#endif

#ifdef USE_LENGTH
    pk_len_t length;
#endif

#ifdef USE_COMMAND
    pk_cmd_t command;
#endif

    uint8_t *data;

#ifdef USE_ENDBYTE
    pk_end_t endbtye;
#endif

#ifdef USE_CRC
    pk_crc_t crc;
#endif

} Packet;

/* Packet function*/
Packet *createPacket();
void deletePacket(Packet *pk);

void setPacketHeader(Packet *pk, pk_hdr_t header);
pk_hdr_t getPacketHeader(Packet *pk);

#ifdef USE_SEQNUM
void setPacketSeqnum(Packet *pk, pk_seq_t seqnum);
pk_seq_t getPacketSeqnum(Packet *pk);
#endif

#ifdef USE_LENGTH
void setPacketLegnth(Packet *pk, pk_len_t length);
pk_len_t getPacketLegnth(Packet *pk);
#endif

#ifdef USE_COMMAND
void setPacketCommnad(Packet *pk, pk_cmd_t command);
pk_cmd_t getPacketCommnad(Packet *pk);
#endif

void setPacketData(Packet *pk, void *data);
void getPacketData(Packet *pk, void *data);

#ifdef USE_ENDBYTE
void setPacketEndbyte(Packet *pk, pk_end_t endbtye);
pk_end_t getPacketEndbyte(Packet *pk);
#endif

#ifdef USE_CRC
void setPacketCrc(Packet *pk, pk_crc_t crc);
pk_crc_t getPacketCrc(Packet *pk);
#endif

size_t calcPacketSize(Packet *pk, size_t data_len);
void pack(Packet *pk, uint8_t *buf);
void unpack(uint8_t *buf, Packet *pk, pointer_t *map);
#endif