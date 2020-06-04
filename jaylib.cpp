#include "jaylib.h"
#include "utils.h"

void Jaylib::drawBand(int x, int y, const uint8_t * sprite, uint8_t cols) {
    uint16_t s;
    int p = (y >> 3) * WIDTH + cols + x - 1;

    for(; cols --; p --) {
        s = pgm_read_byte(sprite + cols) << (y & 0x7);

        sBuffer[p] |= s & 0xFF;
        sBuffer[p + WIDTH] |= ((s >> 8) & 0xFF);
    }
}

void Jaylib::smallPrint(int x, int y, const uint8_t * str) {
    char c;
    for(;c = *str ++;) {
        c -= 32;
        drawBand(x, y, PRINTABLE_CHARS + 3 * c, 3);
        x += 4;
    }
}

void Jaylib::largePrint(int x, int y, const uint8_t * str, int kern) {
    char c;
    for(;c = *str ++;) {
        c &= 0x1F; // Lucky that SPACE % 32 == 0
        drawBand(x, y, PRINTABLE_CHARS_LARGE + 5 * c, 5);
        x += 5 + kern;
    }
}
