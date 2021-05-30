#include <Arduino.h>

#include "epd_driver.h"         // https://github.com/Xinyuan-LilyGO/LilyGo-EPD47
#include "esp_adc_cal.h"        // In-built

#include "open_sans.h"
#include "display.h"
#include "globals.h"
#include "config.h"
#include "uvi.h"

const uint16_t White     = 0xFF;
const uint16_t LightGrey = 0xBB;
const uint16_t Grey      = 0x88;
const uint16_t DarkGrey  = 0x44;
const uint16_t Black     = 0x00;

int vref = 1100;

GFXfont  currentFont;
uint8_t *framebuffer;

void setFont(GFXfont const & font) {
  currentFont = font;
}

void drawString(int x, int y, String text, alignment align) {
  char * data  = const_cast<char*>(text.c_str());
  int  x1, y1; //the bounds of x,y and w and h of the variable 'text' in pixels.
  int w, h;
  int xx = x, yy = y;
  get_text_bounds(&currentFont, data, &xx, &yy, &x1, &y1, &w, &h, NULL);
  if (align == RIGHT)  x = x - w;
  if (align == CENTER) x = x - w / 2;
  int cursor_y = y + h;
  write_string(&currentFont, data, &x, &cursor_y, framebuffer);
}

void arrow(int x, int y, int asize, float aangle, int pwidth, int plength) {
  float dx = (asize - 10) * cos((aangle - 90) * PI / 180) + x; // calculate X position
  float dy = (asize - 10) * sin((aangle - 90) * PI / 180) + y; // calculate Y position
  float x1 = 0;         float y1 = plength;
  float x2 = pwidth / 2;  float y2 = pwidth / 2;
  float x3 = -pwidth / 2; float y3 = pwidth / 2;
  float angle = aangle * PI / 180 - 135;
  float xx1 = x1 * cos(angle) - y1 * sin(angle) + dx;
  float yy1 = y1 * cos(angle) + x1 * sin(angle) + dy;
  float xx2 = x2 * cos(angle) - y2 * sin(angle) + dx;
  float yy2 = y2 * cos(angle) + x2 * sin(angle) + dy;
  float xx3 = x3 * cos(angle) - y3 * sin(angle) + dx;
  float yy3 = y3 * cos(angle) + x3 * sin(angle) + dy;
  fillTriangle(xx1, yy1, xx3, yy3, xx2, yy2, Black);
}

void DrawSegment(int x, int y, int o1, int o2, int o3, int o4, int o11, int o12, int o13, int o14) {
  drawLine(x + o1,  y + o2,  x + o3,  y + o4,  Black);
  drawLine(x + o11, y + o12, x + o13, y + o14, Black);
}

void DrawAngledLine(int x, int y, int x1, int y1, int size, int color) {
  int dx = (size / 2.0) * (x - x1) / sqrt(sq(x - x1) + sq(y - y1));
  int dy = (size / 2.0) * (y - y1) / sqrt(sq(x - x1) + sq(y - y1));
  fillTriangle(x + dx, y - dy, x - dx,  y + dy,  x1 + dx, y1 - dy, color);
  fillTriangle(x - dx, y + dy, x1 - dx, y1 + dy, x1 + dx, y1 - dy, color);
}

void DrawUVI(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = uvi_width, .height = uvi_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) uvi_data);
}

void DrawBattery(int x, int y) {
  uint8_t percentage = 100;
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
    vref = adc_chars.vref;
  }
  float voltage = analogRead(36) / 4096.0 * 6.566 * (vref / 1000.0);
  if (voltage > 1 ) { // Only display if there is a valid reading
    Serial.println("\nVoltage = " + String(voltage));
    percentage = 2836.9625 * pow(voltage, 4) - 43987.4889 * pow(voltage, 3) + 255233.8134 * pow(voltage, 2) - 656689.7123 * voltage + 632041.7303;
    if (voltage >= 4.20) percentage = 100;
    if (voltage <= 3.20) percentage = 0;  // orig 3.5
    drawRect(x + 25, y - 14, 40, 15, Black);
    fillRect(x + 65, y - 10, 4, 7, Black);
    fillRect(x + 27, y - 12, 36 * percentage / 100.0, 11, Black);
    drawString(x + 85, y - 14, String(percentage) + "%  " + String(voltage, 1) + "v", LEFT);
  }
}

void DisplayGeneralInfoSection() {
  setFont(OpenSans10B);
  drawString(5, 2, City, LEFT);
  setFont(OpenSans8B);
  drawString(500, 2, Date_str + "  @   " + Time_str, LEFT);
}

