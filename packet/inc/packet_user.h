#ifndef __PACKET_USER_H__
#define __PACKET_USER_H__

#include<stdint.h>

typedef struct __SampleData{
	uint8_t name[10];
	uint8_t text[30];
}UserData;

#endif