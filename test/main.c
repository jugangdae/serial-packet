#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packet.h"
#include "packet_user.h"
#include "crc8.h"

Packet *pk;
uint8_t buf[BUF_SIZE];
UserData1 userdata_1;
UserData2 userdata_2;
uint8_t sample_1[] = {
    0x0a, 0x00,
    0x15, 0x00, 0x4a, 0x55, 0x00, 0x48,
    0x45, 0x4c, 0x4c, 0x4f, 0x20, 0x57, 0x4f, 0x52,
    0x4c, 0x44, 0x00, 0x0b, 0x0c};
uint8_t sample_2[] = {
    0x0a, 0x01,
    0x09, 0x01, 0x05, 0x06, 0x07, 0x0b,
    0x0c};

void check_status(int n, Packet *pk, uint8_t *buf) {
    /* Check status */
    printf("check status : %d\n", n);
    printf("--------------------\n");
    if (getPacketHeader(pk) == PACKET_HEADER) {
        printf("pk.header : 0x%x \n", getPacketHeader(pk));
        //printf("pk.seqnum : 0x%x \n", getPacketSeqnum(pk));
        printf("pk.lenght : 0x%x \n", getPacketLegnth(pk));
        printf("pk.command : 0x%x \n", getPacketCommnad(pk));
        if (getPacketCommnad(pk) == 0x0) {
            printf("pk.data.name : %s \n", ((UserData1 *)pk->data)->name);
            printf("pk.data.text : %s \n", ((UserData1 *)pk->data)->text);
        } else if (getPacketCommnad(pk) == 0x1) {
            printf("pk.data.h : %d \n", ((UserData2 *)pk->data)->h);
            printf("pk.data.s : %d \n", ((UserData2 *)pk->data)->m);
            printf("pk.data.m : %d \n", ((UserData2 *)pk->data)->s);
        }
        //printf("pk.endbyte : 0x%x \n", getPacketEndbyte(pk));
        printf("pk.crc : 0x%x \n", getPacketCrc(pk));

    } else {
        printf("No packet\n");
    }
    printf("buf(hex) : \n");
    int i;
    int max = BUF_SIZE;
    for (i = 0; i < max; i++) {
        if (i == sizeof(pk->header))  // + sizeof(pk->seqnum))
            max = *(buf + i);
        printf("%02x ", *(buf + i));
        if ((i + 1) % 8 == 0)
            printf("\n");
        else if ((i + 1) % 4 == 0)
            printf(" ");
    }
    printf("\n");
    printf("--------------------\n\n");
}
void unpack_test(uint8_t *sample, int len) {
    memset(pk, 0, sizeof(Packet));
    memset(buf, 0, sizeof(BUF_SIZE));
    memset(&userdata_1, 0, sizeof(UserData1));
    memset(&userdata_2, 0, sizeof(UserData2));
    printf("set sample_buf..\n");
    memcpy(buf, sample, len);

    check_status(1, pk, buf);
    printf("unpacking..\n");
    unpack(buf, pk, cmd_map);

    check_status(2, pk, buf);
}
void pack_test(pk_cmd_t cmd) {
    memset(pk, 0, sizeof(Packet));
    memset(buf, 0, sizeof(BUF_SIZE));
    memset(&userdata_1, 0, sizeof(UserData1));
    memset(&userdata_2, 0, sizeof(UserData2));

    printf("init userdata and packet..\n");

    if (cmd == 0x0) {
        memcpy(userdata_1.name, "JU\0", 3);
        memcpy(userdata_1.text, "HELLO WORLD\0", 12);
        setPacketHeader(pk, PACKET_HEADER);
        setPacketLegnth(pk, calcPacketSize(pk, sizeof(userdata_1)));
        //setPacketSeqnum(pk, 0x0);
        setPacketCommnad(pk, cmd);
        setPacketData(pk, &userdata_1);
        //setPacketEndbyte(pk, PACKET_ENDBYTE);
        setPacketCrc(pk, 0x0);

    } else if (cmd == 0x1) {
        userdata_2.h = 5;
        userdata_2.m = 6;
        userdata_2.s = 7;
        setPacketHeader(pk, PACKET_HEADER);
        //setPacketSeqnum(pk, 0x0);
        setPacketLegnth(pk, calcPacketSize(pk, sizeof(userdata_2)));
        setPacketCommnad(pk, cmd);
        setPacketData(pk, &userdata_2);
        //setPacketEndbyte(pk, PACKET_ENDBYTE);
        setPacketCrc(pk, 0x0);
    }
    
    
    check_status(1, pk, buf);

    printf("packing..\n");
    pack(pk, buf);

    int len = getPacketLegnth(pk);
    int crc = crc8(buf, len-1);
    buf[len-1] = crc;
    setPacketCrc(pk, crc);

    check_status(2, pk, buf);
}
int main() {
    /* ----- Init ----- */
    printf("init userdata..\n");
    memset(&userdata_1, 0, sizeof(UserData1));
    memset(&userdata_2, 0, sizeof(UserData2));
    init_crc8();

    printf("init command..\n");
    cmd_map[0x0] = (pointer_t)&userdata_1;
    cmd_map[0x1] = (pointer_t)&userdata_2;

    printf("init packet..\n");
    pk = createPacket();
    memset(pk, 0, sizeof(Packet));
    printf("\n");

    /* ----- Test code ----- */
    pack_test(0x0);
    //pack_test(0x1);
    //unpack_test(sample_1, sizeof(sample_1));
    //unpack_test(sample_2, sizeof(sample_2));

    return 0;
}
