#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "am27c.h"
#include "sys.h"

void init_am27c_ports(void) {
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    ROM_GPIOPinTypeGPIOOutput(P_A13, A13);
    ROM_GPIOPinTypeGPIOOutput(P_A12, A12);
    ROM_GPIOPinTypeGPIOOutput(P_A11, A11);
    ROM_GPIOPinTypeGPIOOutput(P_A10, A10);
    ROM_GPIOPinTypeGPIOOutput(P_A9, A9);
    ROM_GPIOPinTypeGPIOOutput(P_A8, A8);
    ROM_GPIOPinTypeGPIOOutput(P_A7, A7);
    ROM_GPIOPinTypeGPIOOutput(P_A6, A6);
    ROM_GPIOPinTypeGPIOOutput(P_A5, A5);
    ROM_GPIOPinTypeGPIOOutput(P_A4, A4);
    ROM_GPIOPinTypeGPIOOutput(P_A3, A3);
    ROM_GPIOPinTypeGPIOOutput(P_A2, A2);
    ROM_GPIOPinTypeGPIOOutput(P_A1, A1);
    ROM_GPIOPinTypeGPIOOutput(P_A0, A0);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    ROM_GPIOPinTypeGPIOInput(P_DQ7, DQ7);
    ROM_GPIOPinTypeGPIOInput(P_DQ6, DQ6);
    ROM_GPIOPinTypeGPIOInput(P_DQ5, DQ5);
    ROM_GPIOPinTypeGPIOInput(P_DQ4, DQ4);
    ROM_GPIOPinTypeGPIOInput(P_DQ3, DQ3);
    ROM_GPIOPinTypeGPIOInput(P_DQ2, DQ2);
    ROM_GPIOPinTypeGPIOInput(P_DQ1, DQ1);
    ROM_GPIOPinTypeGPIOInput(P_DQ0, DQ0);

    ROM_GPIOPadConfigSet(P_DQ7, DQ7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ6, DQ6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ5, DQ5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ4, DQ4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ3, DQ3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ2, DQ2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ1, DQ1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOPadConfigSet(P_DQ0, DQ0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    ROM_GPIOPinTypeGPIOOutput(P_PGM, PGM);
    ROM_GPIOPinTypeGPIOOutput(P_OE, OE);
    ROM_GPIOPinTypeGPIOOutput(P_CE, CE);
}

void am27c_set_addr(unsigned short addr) {
    set_pin(P_A13, A13, addr>>13);
    set_pin(P_A12, A12, addr>>12);
    set_pin(P_A11, A11, addr>>11);
    set_pin(P_A10, A10, addr>>10);
    set_pin(P_A9, A9, addr>>9);
    set_pin(P_A8, A8, addr>>8);
    set_pin(P_A7, A7, addr>>7);
    set_pin(P_A6, A6, addr>>6);
    set_pin(P_A5, A5, addr>>5);
    set_pin(P_A4, A4, addr>>4);
    set_pin(P_A3, A3, addr>>3);
    set_pin(P_A2, A2, addr>>2);
    set_pin(P_A1, A1, addr>>1);
    set_pin(P_A0, A0, addr);
}

void init_am27c(void) {
    init_am27c_ports();

    set_pin(P_PGM, PGM, 1);
    set_pin(P_CE, CE, 0);
    set_pin(P_OE, OE, 1);
    
    am27c_set_addr(0x0000);
}

unsigned char read_data(void) {
    unsigned char data = 0x00;
    
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ7, DQ7)<<3;
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ6, DQ6)<<1;
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ5, DQ5)>>1;
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ4, DQ4)>>3;
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ3, DQ3)>>3;
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ2, DQ2);
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ1, DQ1)>>2;
    data |= (unsigned char)ROM_GPIOPinRead(P_DQ0, DQ0)>>1;
    
    return data;
}

unsigned char am27c_get_data(unsigned short addr) {
    unsigned char data = 0x00;
    
    am27c_set_addr(addr);
    set_pin(P_OE, OE, 0);
    delay_us(1);
    data = read_data();
    set_pin(P_OE, OE, 1);
    
    return data;
}

