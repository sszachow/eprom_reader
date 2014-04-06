#ifndef __AM27C_H__
#define __AM27C_H__

#define P_A13   GPIO_PORTF_BASE
#define P_A12   GPIO_PORTB_BASE
#define P_A11   GPIO_PORTB_BASE
#define P_A10   GPIO_PORTA_BASE
#define P_A9    GPIO_PORTB_BASE
#define P_A8    GPIO_PORTE_BASE
#define P_A7    GPIO_PORTB_BASE
#define P_A6    GPIO_PORTB_BASE
#define P_A5    GPIO_PORTE_BASE
#define P_A4    GPIO_PORTE_BASE
#define P_A3    GPIO_PORTB_BASE
#define P_A2    GPIO_PORTA_BASE
#define P_A1    GPIO_PORTA_BASE
#define P_A0    GPIO_PORTA_BASE

#define A13     GPIO_PIN_3
#define A12     GPIO_PIN_5
#define A11     GPIO_PIN_6
#define A10     GPIO_PIN_3
#define A9      GPIO_PIN_7
#define A8      GPIO_PIN_0
#define A7      GPIO_PIN_0
#define A6      GPIO_PIN_1
#define A5      GPIO_PIN_4
#define A4      GPIO_PIN_5
#define A3      GPIO_PIN_4
#define A2      GPIO_PIN_5
#define A1      GPIO_PIN_6
#define A0      GPIO_PIN_7

#define P_DQ7   GPIO_PORTF_BASE
#define P_DQ6   GPIO_PORTC_BASE
#define P_DQ5   GPIO_PORTD_BASE
#define P_DQ4   GPIO_PORTC_BASE
#define P_DQ3   GPIO_PORTC_BASE
#define P_DQ2   GPIO_PORTE_BASE
#define P_DQ1   GPIO_PORTE_BASE
#define P_DQ0   GPIO_PORTF_BASE

#define DQ7     GPIO_PIN_4
#define DQ6     GPIO_PIN_5
#define DQ5     GPIO_PIN_6
#define DQ4     GPIO_PIN_7
#define DQ3     GPIO_PIN_6
#define DQ2     GPIO_PIN_2
#define DQ1     GPIO_PIN_3
#define DQ0     GPIO_PIN_1

#define P_PGM   GPIO_PORTB_BASE
#define P_OE    GPIO_PORTA_BASE
#define P_CE    GPIO_PORTA_BASE

#define PGM     GPIO_PIN_2
#define OE      GPIO_PIN_4
#define CE      GPIO_PIN_2

void init_am27c_ports(void);
void am27c_set_addr(unsigned short addr);
void init_am27c(void);
unsigned char read_data(void);
unsigned char am27c_get_data(unsigned short addr);

#endif

