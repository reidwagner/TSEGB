#include <stdint.h>
#include "video.h"

void display_tile(int x, int y, uint8_t *tile_bytes) {
    uint8_t bity = 0;
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t byte1 = tile_bytes[2*i];
        uint8_t byte2 = tile_bytes[2*i + 1];
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t bit1 = byte1 >> j & 1;
            uint8_t bit2 = byte2 >> j & 1;
            uint8_t col = (bit1 << 1) + bit2;
            printpixel(x + j, y + i, col);
        }
    }
}

void video_test(void) {
    uint8_t tile_bytes[] = {0x7C, 0x7C, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0xFE,
                 0xC6, 0xC6, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0x00};
    for (int i = 0; i < sizeof(tile_bytes); i++) {
        loghex(tile_bytes[i]);
    }
    display_tile(5, 5, tile_bytes);
}
