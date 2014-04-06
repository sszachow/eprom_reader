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

int main(void) 
{
    unsigned char data = 0x00;
    unsigned short addr = 0x00;

    init_sys();
    init_uart();
    init_am27c();

    for (;;) {
        addr = get_short();
        data = am27c_get_data(addr);
        UARTCharPut(UART0_BASE, data);
    }
}

