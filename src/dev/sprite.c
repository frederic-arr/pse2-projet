#include "sprite.h"
#include "lcd.h"

uint16_t darken(uint16_t color, float factor) {
    float r = (float)((color >> 11) & 0x1F);
    float g = (float)((color >> 5) & 0x3F);
    float b = (float)(color & 0x1F);

    r *= factor;
    g *= factor;
    b *= factor;
    return (((uint16_t)r) << 11) | (((uint16_t)g) << 5) | ((uint16_t)b);
}

void DRAW_SPRITE(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *sprite, bool is_dark) {
    CMD_NOP();
    ZONE_SET_REL(x, y, width, height);

    CMD_RAMWR();
    for (int i = 0; i < width * height; i++) {
        uint16_t color = (sprite[2 * i + 1] << 8) | (sprite[2 * i]);
        color = darken(color, is_dark ? 0.75 : 1.0);
        CMD_COLORDATA16(color);
    }
}