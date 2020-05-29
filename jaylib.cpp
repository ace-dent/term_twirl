#include "jaylib.h"
#include "utils.h"

void Jaylib::drawBand(int x, int y, const uint8_t * sprite, const uint16_t mask, uint8_t cols) {
    if(x + cols <= 0 || x >= WIDTH || y + 8 <= 0 || y >= HEIGHT) return;

    half_t s, m;
    int8_t i = x < 0 ? -x : 0;
    int p = (y >> 3) * WIDTH + i + x;
    uint8_t h = y & 7;

    if(cols + x >= WIDTH) cols = WIDTH - x;

    for(; i < cols; i ++, p ++) {
        s.v = pgm_read_byte(sprite + i) << h;
        m.v = mask << h;

        if(y >= 0 && y < HEIGHT)
            sBuffer[p] = sBuffer[p] & ~m.l | s.l & m.l;

        if(h && y > -8 && y < HEIGHT - 8)
            sBuffer[p + WIDTH] = sBuffer[p + WIDTH] & ~m.h | s.h & m.h;
    }
}

void Jaylib::smallPrint(const uint8_t * str) {
    char c;
    for(;c = *str; str ++) {
        c -= 32;
        drawBand(cursor_x, cursor_y, PRINTABLE_CHARS + 3 * c, 0x3F, 3);
        cursor_x += 4;
    }
}

void Jaylib::largePrint(const uint8_t * str, int kern) {
    char c;
    for(;c = *str; str ++) {
        c = (c == ' ') ? 0 : c - 'A' + 1; //TODO: support all ascii
        drawBand(cursor_x, cursor_y, PRINTABLE_CHARS_LARGE + 5 * c, 0xFF, 5);
        cursor_x += 5 + kern;
    }
}

void Jaylib::largePrint(const uint8_t * str) {
    largePrint(str, 1);
}

void Jaylib::setCursor(int x, int y) {
    cursor_x = x;
    cursor_y = y;
}
