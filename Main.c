/*
 * File:   Main.c
 * Author: gahym
 *
 * Created on January 26, 2024, 2:06 PM
 */


#include "xc.h"
#include "LCDlib.h"

void setup(void);
int main(void);

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void)
{
    // execute once code goes here
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0xffff;            //sets all pins to digital I/O
}

int main(void) {
    
    int period = 300;
    
    setup();
    init_lcd();
    // lcd_printChar('a');
    
    while(1){
      lcd_setCursor(0,0);  
      lcd_printStr("Bello Wo");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("ello Wor");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("llo Worl");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("lo World"); 
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("o World!");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr(" World! ");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("World! B");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("orld! Be");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("rld! Bel");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("ld! Bell");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("d! Bello");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr("! Bello ");
      delayms(period);
      lcd_setCursor(0,0);  
      lcd_printStr(" Bello W");
      delayms(period);
      
    }
    
    lcd_setCursor(0,0);
    
    lcd_printStr("Bello");
    
    lcd_setCursor(0,1);
    
    lcd_printStr("World!");
    
    while(1);
    return;
    
}