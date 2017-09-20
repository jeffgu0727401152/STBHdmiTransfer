
#ifndef _DAMD_PORTING_E_UART_H
#define _DAMD_PORTING_E_UART_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct euart_settings
    {
        uint32_t      baud;                       /* baud rate */
        uint32_t      parity;                     /* parity type */
        uint32_t      stop;                       /* stop bit */
        uint32_t      word_bits;            /* number of bits per transfer */
    } eUART_Settings;

    typedef enum euart_baudrate {
        eUART_BAUDRATE_2400 = 48,
        eUART_BAUDRATE_3600 = 32,
        eUART_BAUDRATE_4800 = 24,
        eUART_BAUDRATE_7200 = 16,
        eUART_BAUDRATE_9600 = 12,
        eUART_BAUDRATE_19200 = 6,
        eUART_BAUDRATE_38400 = 3,
        eUART_BAUDRATE_56000 = 2,
    } eUART_BAUDRATE;

    typedef enum euart_parity {
        eUART_PARITY_NONE = -1,
        eUART_PARITY_ODD = 0,
        eUART_PARITY_EVEN,
    }eUART_PARITY;

    typedef void * eUART_HDR;

    void WSD_AL_eUART_GetDefaultSettings(eUART_Settings *pSettings);
    eUART_HDR WSD_AL_eUART_Open(unsigned int channel, const eUART_Settings *pSettings);
    int WSD_AL_eUART_putc(eUART_HDR handle, char c);
    char WSD_AL_eUART_getc(eUART_HDR handle, int *err);
    int WSD_AL_eUART_Close(eUART_HDR handle);

#ifdef __cplusplus
}
#endif

#endif

