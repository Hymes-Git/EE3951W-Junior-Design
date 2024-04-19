/*
 * File:   Main.c
 * Author: gahym
 *
 * Created on January 26, 2024, 2:06 PM
 */

#include "xc.h"
#include "LCDlib.h"
#include "Bufflib.h"

void setup(void);
int main(void);
void init_adc(void);

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1   // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF   // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF    // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI  // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF  // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON  // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
                              // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void)
{
    // execute once code goes here
    CLKDIVbits.RCDIV = 0; // Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0xffff;     // sets all pins to digital I/O
}

// int main(void) {
//
//     int period = 300;
//
//     setup();
//     init_lcd();
//     // lcd_printChar('a');
//
//     while(1){
//       lcd_setCursor(0,0);
//       lcd_printStr("Bello Wo");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("ello Wor");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("llo Worl");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("lo World");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("o World!");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr(" World! ");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("World! B");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("orld! Be");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("rld! Bel");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("ld! Bell");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("d! Bello");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr("! Bello ");
//       delayms(period);
//       lcd_setCursor(0,0);
//       lcd_printStr(" Bello W");
//       delayms(period);
//
//     }
//
//     lcd_setCursor(0,0);
//
//     lcd_printStr("Bello");
//
//     lcd_setCursor(0,1);
//
//     lcd_printStr("World!");
//
//     while(1);
//     return;
//
// }

int main(void)
{
    setup();
    init_lcd();

    init_adc();
    init_timer1();
    initBuffer();

    lcd_setCursor(0, 0);
    char string[20];
    unsigned long int adValue;
    double rawVoltage;
    double compVoltage;
    double temp;

    while (1)
    {

        // every 2 ms the data on the display is updated with the average reading
        while (_T1IF == 0)
            ;
        _T1IF = 0;
        adValue = getAvg();
        rawVoltage = ((0.576 / 1024) * adValue) + 1.024;
        compVoltage = (rawVoltage * 1000 - 1024 - 0.00125) / 122.4;
        temp = -0.122 * (compVoltage * compVoltage) + 24.9 * compVoltage - 0.11;

        // changes the avg data into a string
        sprintf(string, "%6.2f C", temp);
        // sprintf(string , "%6.4f V", rawVoltage);

        lcd_printStr(string);
        lcd_setCursor(0, 0);
    }

    return 0;
}

void init_adc(void)
{
    TRISBbits.TRISB15 = 1; // set A0 to input

    AD1PCFGbits.PCFG9 = 0; // setup I/O

    AD1CHSbits.CH0SA = 9;

    // AD1CON2bits.VCFG = 0b000; // Use AVDD (3.3V) and AVSS (0V) as max/min

    AD1CON2bits.VCFG = 0b011; // Use Vref+ and Vref-

    AD1CON3bits.ADCS = 0b00000001; // you want TAD >= 75ms (Tcy = 62.5ns)
    AD1CON1bits.SSRC = 0b010;      // sample on timer3 events
    AD1CON3bits.SAMC = 0b00001;    // you want at least 1 auto sample time bit
    AD1CON1bits.FORM = 0b00;       // data output form -- recommended unsigned int
                                   // unsigned 0V = 0b0000000000, 3.3V = 0b1111111111
                                   // signed: 0V = 0b1000000000, 3.3V = 0b0111111111
    AD1CON1bits.ASAM = 0b1;        // read the reference manual to see what this does
    AD1CON2bits.SMPI = 0b0;        // read the reference manual to see what this does
    AD1CON1bits.ADON = 1;          // turn on the ADC

    _AD1IF = 0; // Clear interrupt flag
    _AD1IE = 1; // enable interrupts

    TMR3 = 0; // setup timer 3
    T3CON = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 15624;
    T3CONbits.TON = 1;
}

void init_timer1(void)
{
    T1CON = 0;
    TMR1 = 0;
    T1CONbits.TCKPS = 0b10;
    PR1 = 49999;
    _T1IF = 0;
    T1CONbits.TON = 1;
}

// adds data to the buffer every time new data is available
void __attribute__((interrupt, auto_psv)) _ADC1Interrupt()
{
    _AD1IF = 0;
    int num = ADC1BUF0;
    putVal(num); // adds data to the buffer
}
