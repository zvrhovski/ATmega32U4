/*
 * lcd.cpp
 *
 * Created: 4.1.2020. 14:30:34
 *  Author: Zoran Vrhovski
 */ 

#include "lcd.h"
#include <stdio.h>


//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_e_toggle
// PURPOSE: toggle enable pin
void lcd_e_toggle(void){
	lcd_e_high();
	lcd_e_low();
	
	_delay_us(300);	
}


//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_write
// PURPOSE: send a character or an instruction to the LCD
void lcd_write(uint8_t data, uint8_t rs){
	//check write type
	if (rs)
	lcd_rs_high(); //write data
	else
	lcd_rs_low();  //write instruciton
	
	// output high nibble first
		
	LCD_D7_PORT &= reset_bit(LCD_D7_PIN);
	LCD_D6_PORT &= reset_bit(LCD_D6_PIN);
	LCD_D5_PORT &= reset_bit(LCD_D5_PIN);
	LCD_D4_PORT &= reset_bit(LCD_D4_PIN);
		
	if(data & 0x80) LCD_D7_PORT |= set_bit(LCD_D7_PIN);
	if(data & 0x40) LCD_D6_PORT |= set_bit(LCD_D6_PIN);
	if(data & 0x20) LCD_D5_PORT |= set_bit(LCD_D5_PIN);
	if(data & 0x10) LCD_D4_PORT |= set_bit(LCD_D4_PIN);
	lcd_e_toggle();
	
	// output low nibble
	
	LCD_D7_PORT &= reset_bit(LCD_D7_PIN);
	LCD_D6_PORT &= reset_bit(LCD_D6_PIN);
	LCD_D5_PORT &= reset_bit(LCD_D5_PIN);
	LCD_D4_PORT &= reset_bit(LCD_D4_PIN);
	
	if(data & 0x08) LCD_D7_PORT |= set_bit(LCD_D7_PIN);
	if(data & 0x04) LCD_D6_PORT |= set_bit(LCD_D6_PIN);
	if(data & 0x02) LCD_D5_PORT |= set_bit(LCD_D5_PIN);
	if(data & 0x01) LCD_D4_PORT |= set_bit(LCD_D4_PIN);
	lcd_e_toggle();
	
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_char
// PURPOSE:  send a character to the LCD
void lcd_char(uint8_t data){
	if (data =='\n'){
		if (g_nCurrentLine >= LCD_LINES - 1)
		lcd_setline(0);
		else
		lcd_setline(g_nCurrentLine+1);
	} else{
	lcd_write(data,1);
	}
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_instr
// PURPOSE:  send an instruction to the LCD
void lcd_instr(uint8_t instr)
{
	lcd_write(instr,0);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_init
// PURPOSE:  Initialize LCD to 4 bit I/O mode
void lcd_init(){
	
	// configure all port bits as output (LCD data and control lines on different ports
	LCD_DDR(LCD_RS_PORT) |= set_bit(LCD_RS_PIN);
	LCD_DDR(LCD_E_PORT)  |= set_bit(LCD_E_PIN);
	LCD_DDR(LCD_D4_PORT) |= set_bit(LCD_D4_PIN);
	LCD_DDR(LCD_D5_PORT) |= set_bit(LCD_D5_PIN);
	LCD_DDR(LCD_D6_PORT) |= set_bit(LCD_D6_PIN);
	LCD_DDR(LCD_D7_PORT) |= set_bit(LCD_D7_PIN);
	
	// wait for more than 40 ms after VCC rises to 2.7 V
	_delay_ms(50);
	
	// initial write to lcd is 8bit
	
	LCD_D5_PORT |= set_bit(LCD_D5_PIN); 
	LCD_D5_PORT |= set_bit(LCD_D4_PIN);
	lcd_e_toggle();
	_delay_us(4100); // delay, busy flag can't be checked here

	LCD_D5_PORT |= set_bit(LCD_D5_PIN);
	LCD_D5_PORT |= set_bit(LCD_D4_PIN);
	lcd_e_toggle();
	_delay_us(4100); // delay, busy flag can't be checked here

	LCD_D5_PORT |= set_bit(LCD_D5_PIN);
	LCD_D5_PORT |= set_bit(LCD_D4_PIN);
	lcd_e_toggle();
	_delay_us(4100); // delay, busy flag can't be checked here

	LCD_D5_PORT &= reset_bit(LCD_D4_PIN); //busy flag can be checked after the following instructions
	LCD_D5_PORT |= set_bit(LCD_D5_PIN);
	lcd_e_toggle();
	
	lcd_instr(LCD_FUNCTION_4BIT_2LINES); // 4-bit interface, dual line,   5x7 dots
	
	lcd_instr(LCD_DISP_OFF); // display off
	
	lcd_instr(LCD_CLEARDISPLAY);	//clear display
	_delay_ms(2);

	lcd_instr(LCD_RETURNHOME); // return to home position (0,0)
	_delay_ms(2);
	
	lcd_instr(LCD_DISP_ON); // display on
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_setline
// PURPOSE:  Move cursor on specified line
void lcd_setline(uint8_t line){
	uint8_t addressCounter = 0;
	switch(line){
		case 0: addressCounter = LCD_START_LINE1; break;
		case 1: addressCounter = LCD_START_LINE2; break;
		case 2: addressCounter = LCD_START_LINE3; break;
		case 3: addressCounter = LCD_START_LINE4; break;
		default:addressCounter = LCD_START_LINE1; break;
	}
	
	g_nCurrentLine = line;

	lcd_instr(LCD_SETDDRAMADDR + addressCounter);
}

int g_nCurrentLine = 0;

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_print2
// PURPOSE:  send a null terminated string to the LCD eg. char x[10]="hello!";
void lcd_print2(char *text){
	char c;
	while ( (c = *text++) )
	lcd_char(c);
}
//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_print
// PURPOSE:  printf sintax
void lcd_print(char *szFormat, ...){
	char szBuffer[80]; //in this buffer we form the message
	va_list pArgs;
	va_start(pArgs, szFormat);
	vsprintf(szBuffer, szFormat, pArgs);
	va_end(pArgs);
	
	lcd_print2(szBuffer);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_gotoxy
// PURPOSE:  Set cursor to specified position
//           Input:    x  row
//                     y  column

void lcd_gotoxy(uint8_t y, uint8_t x)
{
	#if LCD_LINES==1
	lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE1 + x);
	#elif LCD_LINES==2
	switch (y){
		case 0: lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE1 + x);break;
		case 1: lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE2 + x);break;
		default: break;
	}
	#elif LCD_LINES==4
	switch (y){
		case 0: lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE1 + x);break;
		case 1: lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE2 + x);break;
		case 2: lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE3 + x);break;
		case 3: lcd_instr(LCD_SETDDRAMADDR + LCD_START_LINE4 + x);break;
		default: break;
	}
	#endif
}


//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_clrscr
// PURPOSE:  Clear display and set cursor to home position
void lcd_clrscr(void){
	g_nCurrentLine = 0;
	lcd_instr(LCD_CLEARDISPLAY);
	_delay_us(2000);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_home
// PURPOSE:  Set cursor to home position
void lcd_home(void){
	g_nCurrentLine = 0;
	lcd_instr(LCD_RETURNHOME);
	_delay_us(2000);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcd_define_char
// PURPOSE:  set additional characters in CGRAM
void lcd_define_char(void) {
	
	//definiranje vlastitih simbola/karaktera

	const uint8_t symbol[8][8]  = {//definirajte 8 znakova

		/* 0x00 */	0x0A, 0x04, 0x0E, 0x11, 0x10, 0x11, 0x0E, 0x00, //?
		/* 0x01 */	0x02, 0x04, 0x0E, 0x11, 0x10, 0x11, 0x0E, 0x00, //?
		/* 0x02 */	0x0A, 0x04, 0x0E, 0x10, 0x0E, 0x01, 0x1E, 0x00, //š
		/* 0x03 */	0x02, 0x07, 0x02, 0x0E, 0x12, 0x12, 0x0E, 0x00, //?
		/* 0x04 */	0x0A, 0x04, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00, //ž
		/* 0x05 */	0x02, 0x05, 0x04, 0x04, 0x04, 0x14, 0x08, 0x00, //integral
		/* 0x06 */	0x15, 0x1B, 0x11, 0x0E, 0x0F, 0x0E, 0x11, 0x1F, //? negativ
		/* 0x07 */	0x15, 0x1B, 0x11, 0x0F, 0x11, 0x1E, 0x01, 0x1F, //š negativ
	};


	//
	for (uint8_t i = 0; i < 8; i++)	{
		_delay_us(200);
		lcd_instr(LCD_SETCGRAMADDR + (i << 3));
		for (uint8_t j = 0; j < 8; j++)
		{
			lcd_write(symbol[i][j],1);
		}
		
	}
}

