/*
 * lcd.h
 *
 * Created: 4.1.2020. 14:30:52
 * Author: Zoran
 */ 

#ifndef LCD_H_
#define LCD_H_

#include "../AVR VUB/avrvub.h"

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//--------------------------------------------------------------------------------
// korisnik mijenja samo konfiguraciju displeja pri korištenju ove biblioteke
// konfiguracija LCD displeja
#define LCD_D4_PORT		PORTC // port za 4 bitnu komunikaciju - D4 na LCD displeju
#define LCD_D5_PORT		PORTC // port za 4 bitnu komunikaciju - D5 na LCD displeju
#define LCD_D6_PORT		PORTD // port za 4 bitnu komunikaciju - D6 na LCD displeju
#define LCD_D7_PORT		PORTD // port za 4 bitnu komunikaciju - D7 na LCD displeju
#define LCD_D4_PIN		PC7   // pin  za 4 bitnu komunikaciju - D4 na LCD displeju
#define LCD_D5_PIN		PC6   // pin  za 4 bitnu komunikaciju - D5 na LCD displeju
#define LCD_D6_PIN		PD7	  // pin  za 4 bitnu komunikaciju - D6 na LCD displeju
#define LCD_D7_PIN		PD6   // pin  za 4 bitnu komunikaciju - D7 na LCD displeju

#define LCD_RS_PORT		PORTF // port za odabir registra - RS na LCD displeju
#define LCD_RS_PIN		PF0   // pin  za odabir registra - RS na LCD displeju
#define LCD_E_PORT      PORTF // port za odobrenje upisa - EN na LCD displeju
#define LCD_E_PIN       PF1   // pin  za odobrenje upisa - EN na LCD displeju

#define LCD_LINES		2	  // broj vidljivih linija na LCD displeju
#define LCD_DISP_LENGTH  16   // broj vidljivih znakova po liniji na LCD displeju
// kraj konfiguracije LCD displeja
//--------------------------------------------------------------------------------

// instrukcije LCD displeja

// osnovne instrukcije LCD displeja
#define LCD_CLEARDISPLAY   0x01  // obriši LCD displej 
#define LCD_RETURNHOME     0x02  // pozicioniraj ispis na po?etak LCD displeja

// 
#define LCD_ENTRYMODESET   0x04  
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT    0x10
#define LCD_FUNCTIONSET    0x20
#define LCD_SETCGRAMADDR   0x40
#define LCD_SETDDRAMADDR   0x80

// set entry mode: display shift on/off, dec/inc cursor move direction
#define LCD_ENTRY_DEC            0x04	// display shift off, dec cursor move dir
#define LCD_ENTRY_DEC_SHIFT      0x05   // display shift on,  dec cursor move dir
#define LCD_ENTRY_INC_           0x06   // display shift off, inc cursor move dir
#define LCD_ENTRY_INC_SHIFT      0x07   // display shift on,  inc cursor move dir

// display on/off, cursor on/off, blinking char at cursor position
#define LCD_DISP_OFF             0x08   // display off
#define LCD_DISP_ON              0x0C   // display on, cursor off
#define LCD_DISP_ON_BLINK        0x0D   // display on, cursor off, blink char
#define LCD_DISP_ON_CURSOR       0x0E   // display on, cursor on
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   // display on, cursor on, blink char

// move cursor/shift display
#define LCD_MOVE_CURSOR_LEFT     0x10   // move cursor left  (decrement)
#define LCD_MOVE_CURSOR_RIGHT    0x14   // move cursor right (increment)
#define LCD_MOVE_DISP_LEFT       0x18   // shift display left
#define LCD_MOVE_DISP_RIGHT      0x1C   // shift display right

// function set: set interface data length and number of display lines
#define LCD_FUNCTION_4BIT_1LINE  0x20   // 4-bit interface, single line, 5x7 dots
#define LCD_FUNCTION_4BIT_2LINES 0x28   // 4-bit interface, dual line,   5x7 dots
#define LCD_FUNCTION_8BIT_1LINE  0x30   // 8-bit interface, single line, 5x7 dots
#define LCD_FUNCTION_8BIT_2LINES 0x38   // 8-bit interface, dual line,   5x7 dots

#define LCD_START_LINE1  		 0x00   // DDRAM address of first char of line 1
#define LCD_START_LINE2  		 0x40   // DDRAM address of first char of line 2
#define LCD_START_LINE3  		 0x14   // DDRAM address of first char of line 3
#define LCD_START_LINE4  		 0x54   // DDRAM address of first char of line 4



// --- LCD Utils
// functional macros
#define lcd_e_delay()   _delay_us(1);
#define lcd_e_high()    LCD_E_PORT  |=  set_bit(LCD_E_PIN);
#define lcd_e_low()     LCD_E_PORT  &= reset_bit(LCD_E_PIN);
#define lcd_rs_high()   LCD_RS_PORT |=  set_bit(LCD_RS_PIN)
#define lcd_rs_low()    LCD_RS_PORT &= reset_bit(LCD_RS_PIN)
// address of data direction register of port x
#define LCD_DDR(x) 		(*(&x - 1))





//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_e_toggle
// PURPOSE: toggle enable pin
void lcd_e_toggle(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_write
// PURPOSE: send a character or an instruction to the LCD
void lcd_write(uint8_t data,uint8_t rs) ;

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_instr
// PURPOSE:  send an instruction to the LCD
void lcd_instr(uint8_t instr);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_char
// PURPOSE:  send a character to the LCD
void lcd_char(uint8_t data);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_init
// PURPOSE:  Initialize LCD to 4 bit I/O mode
void lcd_init();

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_setline
// PURPOSE:  Move cursor on specified line
void lcd_setline(uint8_t line);

extern int g_nCurrentLine;

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_print2
// PURPOSE:  send a null terminated string to the LCD eg. char x[10]="hello!";
void lcd_print2(char *text);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_print
// PURPOSE:  printf sintax 
void lcd_print(char *szFormat, ...);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_gotoxy
// PURPOSE:  Set cursor to specified position
//           Input:    x  row (0 -> first row)
//                     y  column (0 -> first column)
void lcd_gotoxy(uint8_t x, uint8_t y);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_clrscr
// PURPOSE:  Clear display and set cursor to home position
void lcd_clrscr(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_home
// PURPOSE:  Set cursor to home position
void lcd_home(void);
//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_define_char
// PURPOSE:  set additional characters in CGRAM
void lcd_define_char(void);

#endif /* LCD_H_ */