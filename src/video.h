#ifndef GB_VIDEO_H
#define GB_VIDEO_H

void video_init(void); 
void display_tile(int x, int y, uint8_t *tile_bytes);
void video_test(void);

/* Imported JavaScript functions */
void printpixel(int x, int y, int c);
void loghex(int num);

#endif
