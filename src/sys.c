#include "driverlib/rom.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "sys.h"

void delay_ms(unsigned long ms) {
    ROM_SysCtlDelay(MILI_SEC * ms);
}

void delay_us(unsigned long us) {
    ROM_SysCtlDelay(MICRO_SEC * us);
}

void set_pin(unsigned long port, unsigned char pin, unsigned char val) {
    if(val & 0x01)
        ROM_GPIOPinWrite(port, pin, pin);
    else
        ROM_GPIOPinWrite(port, pin, 0);
}

void init_sys(void) {
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}

