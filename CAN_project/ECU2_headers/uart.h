#ifndef SCI_H
#define SCI_H

#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch_uart(unsigned char byte);
int puts_uart(const char *s);
unsigned char getch_uart(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

#endif
