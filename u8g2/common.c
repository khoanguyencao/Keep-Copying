#include "../u8g2Headers/common.h"

// PIC32MX170F256B Configuration Bit Settings for ME218 operating at 40MHz from internal fast oscillator (8Mhz)

// 'C' source line config statements

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow multiple reconfigurations)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/2)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


void __delay_ms(uint32_t delay) {
    register uint32_t startCntms = _CP0_GET_COUNT();
    register uint32_t waitCntms = delay * (_XTAL_FREQ / 1000 / 2); //core timer runs at half of system clock

    while (_CP0_GET_COUNT() - startCntms < waitCntms);
}


static volatile uint32_t sysTick;

void __ISR(_TIMER_1_VECTOR, IPL7AUTO) TIM1_ISR(void) {
    sysTick++;    
    IFS0bits.T1IF = 0; //clear flag
}

uint32_t getSysTick(void)
{
    return sysTick;
}

void sysInit(void) {
        
   __builtin_disable_interrupts(); //disable interrupts
    
//    PRECONbits.PREFEN = 0x03; //prefetch anyaddress
//    PRECONbits.PFMWS = 0x02; //2 wait states   
    
//    PRISS = 0x76543210; //configure shadow register
    INTCONbits.MVEC = 1; //use multi vectored mode
    
    ANSELA = 0; //disable analog input
    ANSELB = 0;
 //   ANSELC = 0;
 //   ANSELD = 0;
 //   ANSELE = 0;
 //   ANSELF = 0;
 //   ANSELG = 0;
 //   ANSELH = 0;    
 //   ANSELJ = 0;      
    
 //   TRISHbits.TRISH2 = 0; //LED output
 //   TRISBbits.TRISB12 = 1; //button input
    
    sysTick = 0; //set 1ms systick timer    
    T1CONbits.ON = 0; //timer is disabled
    T1CONbits.TCS = 0; //internal PBCLK source
    T1CONbits.TCKPS = 1; //1:8 prescaler    
    TMR1 = 0; //clear timer1    
    PR1 = (_XTAL_FREQ / 2 / 8 / 1000) - 1; //PR1 = 12499, 1kHz Timer     
    IPC1bits.T1IP = 7; //priority 7
    IPC1bits.T1IS = 3; //sub-priority 3
    IFS0bits.T1IF = 0; //clear flag
    IEC0bits.T1IE = 1; //enable interrupt    
    T1CONbits.ON = 1; //timer is enabled
    
    __builtin_enable_interrupts();   // disable interrupts
}
