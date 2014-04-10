#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "sys.h"
#include "am27c.h"

static const unsigned char seq[] = {0xaa, 0x55, 0xaa};
static const unsigned char seq_len = sizeof(seq) / sizeof(seq[0]);

unsigned short get_short(void) {
    unsigned short result = 0x0000;
    unsigned char c;
    
    c = UARTCharGet(UART0_BASE);
    result |= ((unsigned short)c) << 8;
    c = UARTCharGet(UART0_BASE);
    result |= (unsigned short)c;
    
    return result;
}

void init_uart(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void wait_for_sequence(unsigned char* seq, unsigned char len) {
    unsigned char finished = 0;
    unsigned char i;
    unsigned char c;
    
    while(!finished) {
        for(i = 0; i < len; i++) {
            c = UARTCharGet(UART0_BASE);
            if(c == seq[i]) {
                if(i == len - 1) {
                    finished = 1;
                    break;
                }
            } else {
                break;
            }
        }
    }
    UARTCharPut(UART0_BASE, 'K');
}

int main(void) {
    unsigned char data = 0x00;
    unsigned short addr = 0x00;

    init_sys();
    init_uart();
    init_am27c();
    wait_for_sequence(seq, seq_len);

    for (;;) {
        addr = get_short();
        data = am27c_get_data(addr);
        UARTCharPut(UART0_BASE, data);
    }
}

