#pragma once

/*CRC算法一，适用于程序空间苛刻但CRC计算速度要求不高的微控制系统
        算法概要说明：计算本位后的CRC 码等于上一位CRC 码乘以2 后除
    以多项式，所得的余数再加上本位值除以多项式所得的余数
*/

/*函数名称：crc_cal_by_bit;按位计算CRC
  函数参数：unsigned char* ptr;指向发送缓冲区的首字节
            unsigned char len;要发送的总字节数
  函数返回值：unsigned int
  多项式采用CRC-CCITT 0x1021
*/
unsigned int crc_cal_by_bit(unsigned char* ptr, unsigned char len);

/*CRC算法二，适用于程序空间较大且CRC计算速度要求较高的计算机或微控制系统
        算法概要说明：计算本字节后的CRC 码等于上一字节余式CRC码的低8位左移8位后，
    再加上上一字节CRC 右移8 位（也既取高8 位）和本字节之和后所求得的CRC码
*/
/*函数名称：crc_cal_by_byte;按字节计算CRC
  函数参数：unsigned char* ptr:指向发送缓冲区的首字节
            unsigned char len:要发送的总字节数
  函数返回值：unsigned int
  多项式采用CRC-CCITT 0x1021
*/
unsigned int crc_cal_by_byte(unsigned char* ptr, unsigned char len);

/*CRC算法三，适用于程序空间不太大且CRC计算速度又不可以太慢的微控制系统*/
/*函数名称：crc_cal_by_halfbyte:按半字节计算CRC
  函数参数：unsigned char* ptr:指向发送缓冲区的首字节
            unsigned char len:要发送的总字节数
  函数返回值：unsigned int
  多项式采用CRC-CCITT  0x1021
*/
unsigned int crc_cal_by_halfbyte(unsigned char* ptr, unsigned char len);
