#ifndef MAIN_H
#define MAIN_H

#define GLUE(a, b)     a##b
/* single-bit macros, used for control bits */
#define SET_(what, p, m) GLUE(what, p) |= (1 << (m))
#define CLR_(what, p, m) GLUE(what, p) &= ~(1 << (m))
#define GET_(/* PIN, */ p, m) GLUE(PIN, p) & (1 << (m))
#define SET(what, x) SET_(what, x)
#define CLR(what, x) CLR_(what, x)
#define GET(/* PIN, */ x) GET_(x)

/* nibble macros, used for data path */
#define ASSIGN_(what, p, m, v) GLUE(what, p) = (GLUE(what, p) & \
            ~((1 << (m)) | (1 << ((m) + 1)) | \
              (1 << ((m) + 2)) | (1 << ((m) + 3)))) | \
                  ((v) << (m))
#define READ_(what, p, m) (GLUE(what, p) & ((1 << (m)) | (1 << ((m) + 1)) | \
              (1 << ((m) + 2)) | (1 << ((m) + 3)))) >> (m)
#define ASSIGN(what, x, v) ASSIGN_(what, x, v)
#define READ(what, x) READ_(what, x)

//#define F_CPU           20000000UL Already defined in Makefile

// UART baud rate
#define UART_BAUD_RATE                  115200
#define INITIAL_CUSTOM_CHARACTER        0x1EE // A filled diamond.
#define DEFAULT_CUSTOM_CHARACTER        0x1F8 // 100% filled.
#define NUM_ACTIVE_CUSTOM_CHARACTERS    8

uint16_t getBestFitForCustomCharacter(uint8_t *pixels); 
void handleControlCode(uint8_t character);

#endif