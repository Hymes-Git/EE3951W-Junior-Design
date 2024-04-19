/*
 * File:   LCDlib.h
 * Author: gahym
 *
 * Created on March 23, 2023, 11:12 AM
 */

#ifndef LCDLIB_H
#define LCDLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

    void init_lcd(void);
    void lcd_cmd(char Package);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_printStr(const char s[]);
    void delayms(unsigned int ms);

#ifdef __cplusplus
}
#endif

#endif /* LCDLIB_H */
