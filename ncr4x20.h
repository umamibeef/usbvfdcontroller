#ifndef NCR4X20_H
#define NCR4X20_H

#include "main.h"
 
// LCD pins
// Strobe and busy pins
#define NCRSTROBEPIN    D, 6
#define NCRBUSYPIN      D, 7
// Data pins
#define NCRDATA0PIN     C, 0
#define NCRDATA1PIN     C, 1
#define NCRDATA2PIN     C, 2
#define NCRDATA3PIN     C, 3
#define NCRDATA4PIN     C, 4
#define NCRDATA5PIN     C, 5
#define NCRDATA6PIN     B, 0
#define NCRDATA7PIN     B, 1

// Special control characters supported by the display.
#define CURSOR_ON_CHARACTER                     0x15
#define CURSOR_OFF_CHARACTER                    0x16
#define ALTERNATE_CURSOR_OFF_CHARACTER          0x17
#define CLEAR_SCREEN_CHARACTER                  0x0E
#define FORM_FEED_CHARACTER                     0x0C
// Moves cursor one space leftward.
#define CURSOR_BACKSPACE_CHARACTER              0x08
// Moves cursor one space rightward. 
#define CURSOR_TAB_CHARACTER                    0x09
// Moves cursor to beginning of row.
#define CARRIAGE_RETURN_CHARACTER               0x0D
// Moves cursor down one row.
#define LINE_FEED_CHARACTER                     0x0A
#define VERTICAL_SCROLL_OFF_CHARACTER           0x11
#define VERTICAL_SCROLL_ON_CHARACTER            0x12
#define CHARACTER_SET_INTERNATIONAL_CHARACTER   0x18
#define CHARACTER_SET_JAPANESE_CHARACTER        0x19
#define CHARACTER_SET_CODE_PAGE_850_CHARACTER   0x1A
// Some commands are prefixed with an escape character.
#define ESC_CHARACTER                           0x1B
#define MOVE_CURSOR_CHARACTER                   0x48
// Runs a diagnostic sequence. See data sheet.
#define DISPLAY_DIAGNOSTIC_SECOND_CHARACTER     0x04
// Turns display back on after off command has been sent.
#define DISPLAY_ON_SECOND_CHARACTER             0x05
// Turns display off. Current display state is retained.
#define DISPLAY_OFF_SECOND_CHARACTER            0x06
                      
#define KEY_UP_PRESS                            0x1
#define KEY_DOWN_PRESS                          0x2
#define KEY_LEFT_PRESS                          0x3
#define KEY_RIGHT_PRESS                         0x4
#define KEY_ENTER_PRESS                         0x5
#define KEY_EXIT_PRESS                          0x6
#define KEY_UP_RELEASE                          0x7
#define KEY_DOWN_RELEASE                        0x8
#define KEY_LEFT_RELEASE                        0x9
#define KEY_RIGHT_RELEASE                       0x10
#define KEY_ENTER_RELEASE                       0x11
#define KEY_EXIT_RELEASE                        0x12

#define DATA_SETUP_TIME_IN_MICROSECONDS         1.0
#define STROBE_HOLD_TIME_IN_MICROSECONDS        1.0

extern uint8_t _flagBeginHasBeenCalled;
extern uint8_t _lastCharacter;

void ncr4x20Init(void);
uint8_t ncr4x20WaitForNotBusy(void);
void ncr4x20Write(uint8_t character);
void ncr4x20Begin(void);
void ncr4x20HandleSimpleOneCharCommand(uint8_t character);
void ncr4x20HandleSimpleTwoCharCommand(uint8_t char0, uint8_t char1);
void ncr4x20Clear(void);
void ncr4x20Home(void);
void ncr4x20NoDisplay(void);
void ncr4x20Display(void);
void ncr4x20NoBlink(void);
void ncr4x20Blink(void);
void ncr4x20NoCursor(void);
void ncr4x20Cursor(void);
void ncr4x20SetCursor(uint8_t col, uint8_t row);
void ncr4x20SetDefaultCharacterSet(void);
void ncr4x20SetJapaneseCharacterSet(void);
void ncr4x20SetCodePage850CharacterSet(void);
void ncr4x20NoVerticalScroll(void);
void ncr4x20VerticalScroll(void);
void ncr4x20StartDiagnosticSequence(void);
void ncr4x20EndDiagnosticSequence(void);
void ncr4x20SendKeyReport(uint8_t key);

#endif