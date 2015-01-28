//AVR includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//local includes
#include "uart.h"
#include "main.h"
#include "customcharmap.h"
#include "ncr4x20.h"

//bind putc to iostream
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

uint16_t currentCustomCharacters[NUM_ACTIVE_CUSTOM_CHARACTERS] = 
{
  // Inital character is a filled diamond. 
  // We should not usually see these unless
  // there is an error with custom characters.
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER,
  INITIAL_CUSTOM_CHARACTER
};

// See CustomCharMap.h for more detais on what this function
// does.
uint16_t getBestFitForCustomCharacter(uint8_t *pixels) {

    const uint8_t *currentCharMapPixels = customCharMapPixels;

    uint8_t characterIndex, i;

    for (characterIndex = 0; characterIndex < CUSTOM_CHAR_MAP_LEN; characterIndex++){
        uint8_t match = 1;

        for (i=0; i<7; i++){
            if (*currentCharMapPixels != pixels[i]) match = 0;
            currentCharMapPixels++;
        }

        if (match){
            return customCharMapChars[characterIndex];
        }
    }

    // Return all-filled.
    return DEFAULT_CUSTOM_CHARACTER;    
}

void handleControlCode(uint8_t character) {
    uint16_t t0, t1;
    switch (character){
        case 1:
            // Cursor home
            ncr4x20Home();
            break;
        case 2:
            // Hide display
            ncr4x20NoDisplay();
            break;
        case 3:
            // Restore display.
            ncr4x20Display();
            break;
        case 4:
            // Turn off cursor.
            ncr4x20NoCursor();
            break;
        case 12:
            // Clear screen.
            ncr4x20Clear();
            break;
        case 14: // Set brightness.
        case 15: // Set contrast, range 0-100.
            uart_getc(); // Not implemented: read and discard byte.
            break;
        case 17:
            // Set position.
            // wait for byte first
            do
            {
                t0 = uart_getc();
            }while(t0 == UART_NO_DATA);
            do
            {
                t1 = uart_getc();
            }while(t1 == UART_NO_DATA);
            ncr4x20SetCursor(t0, t1);
            break;
        case 19:
            // Turn on scroll.
            ncr4x20VerticalScroll();
            break;
        case 20:
            // Turn off scroll.
            ncr4x20NoVerticalScroll();
            break;
        case 22:
        case 23: // Wrap on.
        case 24: // Wrap off.
                 // Ignore, display always wraps.
        case 25:
            break;
        case 26:
            // Init display.
            ncr4x20Begin();
            break;
        // Pass standard ASCII control codes straight through.
        case 8:
        case 9:
        case 10:
        case 13:
            ncr4x20Write(character);
            break;
        default:
            // Unknown code, ignore it.
            break;    
    }
}


int main(void)
{ 
    uint8_t character;
    uint16_t translated;
    uint8_t characterSet;
    // Keep track of the current VFD character set being used.
    uint8_t currentCharacterSet = 0;

    stdout = &mystdout;

    // Initialize UART
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
    
    // Enable interrupts
    sei();
    
    // Initialize VFD
    ncr4x20Init();
    ncr4x20Begin();

    while(1)
    {
        character = uart_getc();
        if (character & UART_NO_DATA){
            // No data received. do nada
        }else{
            // mirror to terminal for debug
            //uart_putc(character);
            if (character < 32){
                handleControlCode(character);
            }else{
                // Translate character to character set/character pair.
                translated = (uint16_t)character;
                
                if (character>=128 && character<(128+8))
                    translated = currentCustomCharacters[character - 128];
                
                // Remap selected extended characters.
                switch (character){
                    //vertical bar
                    case 0xFE:
                        translated = 0x2B3;
                        break;
                    //underscore
                    case 0xC4:
                        translated = 0x05F;
                        break;
                    case 0xDE:
                        // Up arrow.
                        translated = 0x1FC;
                        break;
                    case 0xE0:
                        // Down arrow.
                        translated = 0x1FA;
                        break;
                    case 0xE1:
                        // Left arrow.
                        translated = 0x1FD;
                        break;
                    case 0xDF:
                        // Right arrow.
                        translated = 0x1FB;
                        break;
                    case 0xFF:
                        // Filled block.
                        translated = 0x1F8;
                        break;
                    //degrees symbol
                    case 0x80:
                        translated = 0x1DF;
                        break;
                    default:
                        // Leave unchanged.
                        break;   
                }
                
                // Switch character set if has changed.
                characterSet = (uint8_t)(translated >> 8);
                if ( (characterSet != currentCharacterSet) && (characterSet < 3) ){
                    // Send character set command directly.
                    ncr4x20Write(CHARACTER_SET_INTERNATIONAL_CHARACTER + characterSet);
                    currentCharacterSet = characterSet;
                }
                
                // Write the character now that the character set has been selected.
                ncr4x20Write((uint8_t)translated);
            }  
        }
    }
    
    return 0;
}