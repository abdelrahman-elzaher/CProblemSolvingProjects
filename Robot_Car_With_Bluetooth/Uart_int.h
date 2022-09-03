/*
 * Uart_init.h
 *
 *  
 *      Author: Abdelrahman Hesham
 */

#ifndef UART_INT_H_
#define UART_INT_H_

void Uart_vidInit(void);
u8 Uart_vidSendByte(u8 Byte);
u8 Uart_u8RecieveByte(void);

#endif /* UART_INT_H_ */
