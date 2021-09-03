#include<stdio.h>
#define CRC8INIT    0x00
//#define CRC8POLY    0x18              //0X18 = X^8+X^5+X^4+X^0
#define CRC8POLY    0x7              //0X18 = X^8+X^5+X^4+X^0

char    crc8 ( char *data_in, int number_of_bytes_to_read )
{
    char     crc;
    int loop_count;
    char  bit_counter;
    char  data;
    char  feedback_bit;
    
    crc = CRC8INIT;
 
    for (loop_count = 0; loop_count != number_of_bytes_to_read; loop_count++)
    {
        data = data_in[loop_count];
        
        bit_counter = 8;
        do {
            feedback_bit = (crc ^ data) & 0x01;
    
            if ( feedback_bit == 0x01 ) {
                crc = crc ^ CRC8POLY;
            }
            crc = (crc >> 1) & 0x7F;
            if ( feedback_bit == 0x01 ) {
                crc = crc | 0x80;
            }
        
            data = data >> 1;
            bit_counter--;
        
        } while (bit_counter > 0);
    }
    
    return crc;
}

void main(){
    char buf = 0x5c;
    unsigned char res = crc8(&buf,1);
    printf("\nCRC: %x\n",res);
}