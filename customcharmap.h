// Translation table for common custom characters.
#define CUSTOM_CHAR_MAP_LEN 38

const uint16_t customCharMapChars[CUSTOM_CHAR_MAP_LEN] =
{
    0x120, // 0 - all blank (match).
    0x1F8, // 1 - all filled (match).
    0x1F0, // 2 - one pixel bar, left (match).
    0x1F1, // 3 - two pixel bar, left (match).
    0x1F2, // 4 - three pixel bar, left (match).
    0x1F3, // 5 - 4 pixel bar, left (match).
    0x1F4, // 6 - 1 pixel bar, right (match).
    0x1F5, // 7 - 2 pixel bar, right (match).
    0x1F6, // 8 - 3 pixel bar, right (match).
    0x1F7, // 9 - 4 pixel bar, right (match).
    0x25F, // 10 - 1 pixel bar, bottom (match).
    0x25F, // 11 - 2 pixel bar, bottom.
    0x2DC, // 12 - 3 pixel bar, bottom.
    0x2DC, // 13 - 4 pixel bar, bottom (match).
    0x2DC, // 14 - 5 pixel bar, bottom.
    0x2DB, // 15 - 6 pixel bar, bottom.
    0x0AF, // 16 - 1 pixel bar, top (match).
    0x0AF, // 17 - 2 pixel bar, top.
    0x2DF, // 18 - 3 pixel bar, top (match).
    0x2DF, // 19 - 4 pixel bar, top.
    0x2DB, // 20 - 5 pixel bar, top.
    0x2DB, // 21 - 6 pixel bar, top.
    0x1F0, // 22 - 1 pixel bar, left + full low horizontal bar.
    0x1F1, // 23 - 2 pixel bar, left + full low horizontal bar.
    0x1F2, // 24 - 3 pixel bar, left + full low horizontal bar.
    0x1F3, // 25 - 4 pixel bar, left + full low horizontal bar.
    0x1F4, // 26 - 1 pixel bar, right + full low horizontal bar.
    0x1F5, // 27 - 2 pixel bar, right + full low horizontal bar.
    0x1F6, // 28 - 3 pixel bar, right + full low horizontal bar.
    0x1F7, // 29 - 4 pixel bar, right + full low horizontal bar.
    0x1FC, // 30 - Filled upward arrow -> unfilled arrow.
    0x1EC, // 31 - Filled heart -> filled circle.
    0x1ED, // 32 - Unfilled heart -> unfilled circle.
    0x1DB, // 33 - Open checkbox -> box.
    0x1E0, // 34 - Checked checkbox -> box with horz line across.
    0x09F, // 35 - Grayed checkbox -> 100% dither.  
    0x19B, // 36 - Left filled triangle.
    0x199, // 37 - Right filled triangle.
};

const uint8_t customCharMapPixels[CUSTOM_CHAR_MAP_LEN * 7] =
{
    // 0 - all blank.
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 1 - all filled.
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,

    // 2 - one pixel bar, left.
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,

    // 3 - two pixel bar, left.
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,

    // 4 - three pixel bar, left.
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,

    // 5 - 4 pixel bar, left.
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,

    // 6 - 1 pixel bar, right.
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,

    // 7 - 2 pixel bar, right.
    0b00011,
    0b00011,
    0b00011,
    0b00011,
    0b00011,
    0b00011,
    0b00011,

    // 8 - 3 pixel bar, right.
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,

    // 9 - 4 pixel bar, right.
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b01111,

    // 10 - 1 pixel bar, bottom.
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b11111,

    // 11 - 2 pixel bar, bottom.
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b11111,
    0b11111,

    // 12 - 3 pixel bar, bottom.
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b11111,
    0b11111,
    0b11111,

    // 13 - 4 pixel bar, bottom.
    0b00000,  
    0b00000,  
    0b00000,  
    0b11111,
    0b11111,
    0b11111,
    0b11111,

    // 14 - 5 pixel bar, bottom.
    0b00000,  
    0b00000,  
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,

    // 15 - 6 pixel bar, bottom.
    0b00000,  
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,

    // 16 - 1 pixel bar, top.
    0b11111,
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  

    // 17 - 2 pixel bar, top.
    0b11111,
    0b11111,
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  

    // 18 - 3 pixel bar, top.
    0b11111,
    0b11111,
    0b11111,
    0b00000,  
    0b00000,  
    0b00000,  
    0b00000,  

    // 19 - 4 pixel bar, top.
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,  
    0b00000,  
    0b00000,  

    // 20 - 5 pixel bar, top.
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,  
    0b00000,  

    // 21 - 6 pixel bar, top.
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,

    // 22 - one pixel bar, left + full low horizontal bar.
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b11111,

    // 23 - two pixel bar, left + full low horizontal bar.
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11111,

    // 24 - three pixel bar, left + full low horizontal bar.
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11111,

    // 25 - 4 pixel bar, left + full low horizontal bar.
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11111,

    // 26 - 1 pixel bar, right + full low horizontal bar.
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b11111,

    // 27 - 2 pixel bar, right + full low horizontal bar.
    0b00011,
    0b00011,
    0b00011,
    0b00011,
    0b00011,
    0b00011,
    0b11111,

    // 28 - 3 pixel bar, right + full low horizontal bar.
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b11111,

    // 29 - 4 pixel bar, right + full low horizontal bar.
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b01111,
    0b11111,

    // 30 - Filled upward arrow.
    0b00100,
    0b00100,
    0b01110,
    0b01110,
    0b11111,
    0b11111,
    0b00100,

    // 31 - Filled heart.
    0b11111,
    0b10101,
    0b00000,
    0b00000,
    0b00000,
    0b10001,
    0b11011,

    // 32 - Unfilled heart.
    0b11111,
    0b10101,
    0b01010,
    0b01110,
    0b01110,
    0b10101,
    0b11011,

    // 33 - Open checkbox.
    0b00000,
    0b00000,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b11111,

    // 34 - Checked checkbox.
    0b00100,
    0b00100,
    0b11101,
    0b10110,
    0b10101,
    0b10001,
    0b11111,

    // 35 - Grayed checkbox.
    0b00000,
    0b00000,
    0b11111,
    0b10101,
    0b11011,
    0b10101,
    0b11111,

    // 36 - Left filled triangle.
    0b01000,
    0b01100,
    0b01110,
    0b01111,
    0b01110,
    0b01100,
    0b01000,

    // 37 - Left filled triangle.
    0b01000,
    0b01100,
    0b01110,
    0b01111,
    0b01110,
    0b01100,
    0b01000,
};

