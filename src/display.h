#pragma once

enum alignment {LEFT, RIGHT, CENTER};

extern uint8_t *framebuffer;

extern const uint16_t White;
extern const uint16_t LightGrey;
extern const uint16_t Grey;
extern const uint16_t DarkGrey;
extern const uint16_t Black;

void setFont(GFXfont const & font);
void drawString(int x, int y, String text, alignment align);
void arrow(int x, int y, int asize, float aangle, int pwidth, int plength);

inline void fillCircle(int x, int y, int r, uint8_t color) {
  epd_fill_circle(x, y, r, color, framebuffer);
}

inline void drawFastHLine(int16_t x0, int16_t y0, int length, uint16_t color) {
  epd_draw_hline(x0, y0, length, color, framebuffer);
}

inline void drawFastVLine(int16_t x0, int16_t y0, int length, uint16_t color) {
  epd_draw_vline(x0, y0, length, color, framebuffer);
}

inline void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  epd_write_line(x0, y0, x1, y1, color, framebuffer);
}

inline void drawCircle(int x0, int y0, int r, uint8_t color) {
  epd_draw_circle(x0, y0, r, color, framebuffer);
}

inline void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  epd_draw_rect(x, y, w, h, color, framebuffer);
}

inline void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  epd_fill_rect(x, y, w, h, color, framebuffer);
}

inline void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                  int16_t x2, int16_t y2, uint16_t color) {
  epd_fill_triangle(x0, y0, x1, y1, x2, y2, color, framebuffer);
}

inline void drawPixel(int x, int y, uint8_t color) {
  epd_draw_pixel(x, y, color, framebuffer);
}

inline void edp_update() {
  epd_draw_grayscale_image(epd_full_screen(), framebuffer); // Update the screen
}


void DrawSegment(int x, int y, int o1, int o2, int o3, int o4, int o11, int o12, int o13, int o14);
void DrawAngledLine(int x, int y, int x1, int y1, int size, int color);

void DrawUVI(int x, int y);
void DrawBattery(int x, int y);
void DisplayGeneralInfoSection();


