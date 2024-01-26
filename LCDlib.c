#include "xc.h"
#include "LCDlib.h"
#include <stdlib.h>

void lcd_cmd(char package) {
    
    _MI2C2IF = 0;
    
    // Send START
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1); 
    _MI2C2IF = 0;
  
    // Send Address and Write Command   
             ///76543210
    I2C2TRN = 0b01111100;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
            
    // Send high byte (always 0x00)
             ///76543210
    I2C2TRN = 0b00000000;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    // Send Package
    I2C2TRN = package;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    // Send Stop
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
}


void init_lcd(void) {
    I2C2BRG = 0x9D; // set to a clock frequency of 100 kHz
    IFS3bits.MI2C2IF = 0; // Clear Interrupt Flag
    I2C2CONbits.I2CEN = 1; // Enable I2C mode
    
    delayms(40);
    
    lcd_cmd(0b00111000); // function set
    lcd_cmd(0b00111001); // function set, advance instruction mode}
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000); // contrast low
    lcd_cmd(0b01010110);
    lcd_cmd(0b01101100); // follower control
    
    delayms(200);
    
    lcd_cmd(0b00111000); // function set
    lcd_cmd(0b00001100); // Dispaly On
    lcd_cmd(0b00000001); // Clear Display
    
    delayms(1);    
}

void lcd_setCursor(char x, char y) {
    // given appropriate x and y values the cursor on the screen is set
    lcd_cmd((0x40*y + x) + 0b10000000);
}

void lcd_printChar(char myChar){
    _MI2C2IF = 0;
    
    // Send START
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1); 
    _MI2C2IF = 0;
    
    // Send Address and Write Command   
             ///76543210
    I2C2TRN = 0b01111100;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    // Send high byte (always 0x00)
             ///76543210
    I2C2TRN = 0b01000000;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    // Send myChar
    I2C2TRN = myChar;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    // Send Stop
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
    
    
}

void lcd_printStr(const char s[]) {
    int pointer = 0;
    _MI2C2IF = 0;
    
    // Send START
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1); 
    _MI2C2IF = 0;
    
    // Send Address and Write Command   
             // 76543210
    I2C2TRN = 0b01111100;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    while(s[pointer+1] != NULL) {
        // Send Repeat Control Byte
                 // 76543210
        I2C2TRN = 0b11000000;
        while(_MI2C2IF == 0);
        _MI2C2IF = 0;
        
        // Send Data
        I2C2TRN = s[pointer];
        while(_MI2C2IF == 0);
        _MI2C2IF = 0;

        pointer++;
    }
    
    // Send Final Control Byte
             // 76543210
    I2C2TRN = 0b01000000;
    while(_MI2C2IF == 0);
    _MI2C2IF = 0;
    
    // Send Data
    I2C2TRN = s[pointer];
    while(_MI2C2IF == 0);
    _MI2C2IF = 0; 
    
    // Send Stop
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
    
}

void delayms(unsigned int ms) {
    int i;
    for (i = 0; i < ms; i++) {
        asm("repeat #15993");
        asm("nop");
    }
}
