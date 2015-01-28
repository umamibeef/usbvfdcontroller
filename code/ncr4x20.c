// AVR includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "main.h"
#include "ncr4x20.h"
  
uint8_t _flagBeginHasBeenCalled;
uint8_t _lastCharacter;

static const uint8_t cursorPos[4][20] =
{
    {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,},
    {0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,},
    {0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,},
    {0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,},
};

void ncr4x20Init(void){
    _flagBeginHasBeenCalled = 0;
    
    // Initalize pin settings.
    // Strobe and busy
    // Strobe is active high
    SET(PORT, NCRSTROBEPIN);
    SET(DDR, NCRSTROBEPIN);
    CLR(DDR, NCRBUSYPIN);
    // Data - port is bidirectional, so set as inputs for now
    CLR(DDR, NCRDATA0PIN);
    CLR(DDR, NCRDATA1PIN);
    CLR(DDR, NCRDATA2PIN);
    CLR(DDR, NCRDATA3PIN);
    CLR(DDR, NCRDATA4PIN);
    CLR(DDR, NCRDATA5PIN);
    CLR(DDR, NCRDATA6PIN);
    CLR(DDR, NCRDATA7PIN);
    
    _lastCharacter = 0;

    // Wait for display to initialize
    while(GET(NCRBUSYPIN)); 
}
  
uint8_t ncr4x20WaitForNotBusy()
{
    uint8_t result = 1;
    
    while(GET(NCRBUSYPIN));
    
    return result;
}

void ncr4x20Write(uint8_t character)
{    
    // Don't do anything until begin has been called. This is to enforce calling
    // of the begin() method in case we need to put something critical in there
    // later.
    if (_flagBeginHasBeenCalled){
        
        ncr4x20WaitForNotBusy();
        
        uint8_t tmpCharacter = character;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA0PIN);
        else
            CLR(PORT, NCRDATA0PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA1PIN);
        else
            CLR(PORT, NCRDATA1PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA2PIN);
        else
            CLR(PORT, NCRDATA2PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA3PIN);
        else
            CLR(PORT, NCRDATA3PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA4PIN);
        else
            CLR(PORT, NCRDATA4PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA5PIN);
        else
            CLR(PORT, NCRDATA5PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA6PIN);
        else
            CLR(PORT, NCRDATA6PIN);
        
        tmpCharacter >>= 1;
        
        if (tmpCharacter & 1)
            SET(PORT, NCRDATA7PIN);
        else
            CLR(PORT, NCRDATA7PIN);
        
        // Enable output
        SET(DDR, NCRDATA0PIN);
        SET(DDR, NCRDATA1PIN);
        SET(DDR, NCRDATA2PIN);
        SET(DDR, NCRDATA3PIN);
        SET(DDR, NCRDATA4PIN);
        SET(DDR, NCRDATA5PIN);
        SET(DDR, NCRDATA6PIN);
        SET(DDR, NCRDATA7PIN);
        
        _delay_us(DATA_SETUP_TIME_IN_MICROSECONDS);
        // Write data to display. Strobe is active low.      
        CLR(PORT, NCRSTROBEPIN);
        _delay_us(STROBE_HOLD_TIME_IN_MICROSECONDS);
        // Restore strobe line.      
        SET(PORT, NCRSTROBEPIN);;
        
        // Disable output
        CLR(DDR, NCRDATA0PIN);
        CLR(DDR, NCRDATA1PIN);
        CLR(DDR, NCRDATA2PIN);
        CLR(DDR, NCRDATA3PIN);
        CLR(DDR, NCRDATA4PIN);
        CLR(DDR, NCRDATA5PIN);
        CLR(DDR, NCRDATA6PIN);
        CLR(DDR, NCRDATA7PIN);
        
        _lastCharacter = character;
    }
}

void ncr4x20Begin()
{
    _flagBeginHasBeenCalled = 1;
    
    ncr4x20Write(ESC_CHARACTER);
    ncr4x20Write(DISPLAY_ON_SECOND_CHARACTER);
    ncr4x20Write(FORM_FEED_CHARACTER);
    ncr4x20Write(CLEAR_SCREEN_CHARACTER);
    ncr4x20Write(CHARACTER_SET_INTERNATIONAL_CHARACTER);
    ncr4x20Write(VERTICAL_SCROLL_OFF_CHARACTER);
}

// Sends a simple one byte command code with proper enter/leave.
void ncr4x20HandleSimpleOneCharCommand(uint8_t character)
{
    ncr4x20Write(character);
}

void ncr4x20HandleSimpleTwoCharCommand(uint8_t char0, uint8_t char1)
{
    ncr4x20Write(char0);
    ncr4x20Write(char1);
}

void ncr4x20Clear()
{
    ncr4x20HandleSimpleTwoCharCommand(CLEAR_SCREEN_CHARACTER,FORM_FEED_CHARACTER);
}

void ncr4x20Home()
{
    ncr4x20Write(FORM_FEED_CHARACTER);
}
  
void ncr4x20NoDisplay()
{
    ncr4x20HandleSimpleTwoCharCommand(ESC_CHARACTER, DISPLAY_OFF_SECOND_CHARACTER);
}

void ncr4x20Display()
{
    ncr4x20HandleSimpleTwoCharCommand(ESC_CHARACTER, DISPLAY_ON_SECOND_CHARACTER);
}

void ncr4x20NoBlink()
{
    ncr4x20HandleSimpleOneCharCommand(CURSOR_OFF_CHARACTER);
}

void ncr4x20Blink()
{
    ncr4x20HandleSimpleOneCharCommand(CURSOR_ON_CHARACTER);
}

void ncr4x20NoCursor()
{
    // Identical to noBlink.
    ncr4x20HandleSimpleOneCharCommand(CURSOR_OFF_CHARACTER);
}

void ncr4x20Cursor()
{
    // Identical to blink.
    ncr4x20HandleSimpleOneCharCommand(CURSOR_ON_CHARACTER);
}
  
void ncr4x20SetCursor(uint8_t col, uint8_t row)
{
    ncr4x20Write(ESC_CHARACTER);
    ncr4x20Write(MOVE_CURSOR_CHARACTER);
    ncr4x20Write(cursorPos[row][col]);
}

void ncr4x20SetDefaultCharacterSet()
{
    ncr4x20HandleSimpleOneCharCommand(CHARACTER_SET_INTERNATIONAL_CHARACTER);
}

void ncr4x20SetJapaneseCharacterSet()
{
    ncr4x20HandleSimpleOneCharCommand(CHARACTER_SET_JAPANESE_CHARACTER);
}

void ncr4x20SetCodePage850CharacterSet()
{
    ncr4x20HandleSimpleOneCharCommand(CHARACTER_SET_CODE_PAGE_850_CHARACTER);
}

void ncr4x20NoVerticalScroll()
{
    ncr4x20HandleSimpleOneCharCommand(VERTICAL_SCROLL_OFF_CHARACTER);
}

void ncr4x20VerticalScroll()
{
    ncr4x20HandleSimpleOneCharCommand(VERTICAL_SCROLL_ON_CHARACTER);
}

void ncr4x20StartDiagnosticSequence()
{
    ncr4x20HandleSimpleTwoCharCommand(ESC_CHARACTER, DISPLAY_DIAGNOSTIC_SECOND_CHARACTER);
}

void ncr4x20EndDiagnosticSequence()
{
    // The "enable display" command brings the display out of the diagnostic sequence.
    ncr4x20Display();
}

void ncr4x20SendKeyReport(uint8_t key)
{
    //uart_putc(0x80);
    //uart_putc(key);
}