#ifndef __SYS_H__
#define __SYS_H__

#define FREQ 50000000
#define MILI_SEC ((unsigned long)(FREQ / (1000 * 3)))
#define MICRO_SEC ((unsigned long)(FREQ / (1000000 * 3)))

void delay_ms(unsigned long ms);
void delay_us(unsigned long us);
void set_pin(unsigned long port, unsigned char pin, unsigned char val);
void init_sys(void);

#endif

