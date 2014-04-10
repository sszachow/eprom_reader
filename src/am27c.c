#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "am27c.h"
#include "sys.h"

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

static const unsigned long PERIPH[] = {SYSCTL_PERIPH_GPIOA, SYSCTL_PERIPH_GPIOB,
                                            SYSCTL_PERIPH_GPIOC, SYSCTL_PERIPH_GPIOD,
                                            SYSCTL_PERIPH_GPIOE, SYSCTL_PERIPH_GPIOF};

static const unsigned long A_PORTS[] = {P_A0, P_A1, P_A2, P_A3, P_A4, P_A5, P_A6,
                                        P_A7, P_A8, P_A9, P_A10, P_A11, P_A12, P_A13};

static const unsigned char A_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13};

static const unsigned long DQ_PORTS[] = {P_DQ0, P_DQ1, P_DQ2, P_DQ3, P_DQ4, P_DQ5, P_DQ6, P_DQ7};

static const unsigned char DQ_PINS[] = {DQ0, DQ1, DQ2, DQ3, DQ4, DQ5, DQ6, DQ7};

static const unsigned long CTL_PORTS[] = {P_PGM, P_OE, P_CE};

static const unsigned char CTL_PINS[] = {PGM, OE, CE};


void init_am27c_ports(void) {
    unsigned char i;
    
    for(i = 0; i < NELEMS(PERIPH); i++)
        ROM_SysCtlPeripheralEnable(PERIPH[i]);

    for(i = 0; i < NELEMS(A_PORTS); i++)
        ROM_GPIOPinTypeGPIOOutput(A_PORTS[i], A_PINS[i]);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    for(i = 0; i < NELEMS(DQ_PORTS); i++) {
        ROM_GPIOPinTypeGPIOInput(DQ_PORTS[i], DQ_PINS[i]);
        ROM_GPIOPadConfigSet(DQ_PORTS[i], DQ_PINS[i], GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    }

    for(i = 0; i < NELEMS(CTL_PORTS); i++)
        ROM_GPIOPinTypeGPIOOutput(CTL_PORTS[i], CTL_PINS[i]);
}

void am27c_set_addr(unsigned short addr) {
    unsigned char i;
    
    for(i = 0; i < NELEMS(A_PORTS); i++)
        set_pin(A_PORTS[i], A_PINS[i], addr>>i);
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
    delay_us(1);
    set_pin(P_OE, OE, 0);
    delay_us(1);
    data = read_data();
    set_pin(P_OE, OE, 1);
    
    return data;
}

