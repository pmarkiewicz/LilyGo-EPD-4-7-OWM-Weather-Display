#include <Arduino.h>

#include "epd_driver.h"         // https://github.com/Xinyuan-LilyGO/LilyGo-EPD47
#include "esp_adc_cal.h"        // In-built

#include "moon.h"
#include "sunrise.h"
#include "sunset.h"
#include "open_sans.h"
#include "globals.h"
#include "config.h"
#include "uvi.h"
#include "lang.h"
#include "conversions.h"
#include "display.h"

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

void DisplayDisplayWindSection(int x, int y, float angle, float windspeed, int Cradius) {
  arrow(x, y, Cradius - 22, angle, 18, 33); // Show wind direction on outer circle of width and length
  setFont(OpenSans8B);
  int dxo, dyo, dxi, dyi;
  drawCircle(x, y, Cradius, Black);       // Draw compass circle
  drawCircle(x, y, Cradius + 1, Black);   // Draw compass circle
  drawCircle(x, y, Cradius * 0.7, Black); // Draw compass inner circle
  for (float a = 0; a < 360; a = a + 22.5) {
    dxo = Cradius * cos((a - 90) * PI / 180);
    dyo = Cradius * sin((a - 90) * PI / 180);
    if (a == 45)  drawString(dxo + x + 15, dyo + y - 18, TXT_NE, CENTER);
    if (a == 135) drawString(dxo + x + 20, dyo + y - 2,  TXT_SE, CENTER);
    if (a == 225) drawString(dxo + x - 20, dyo + y - 2,  TXT_SW, CENTER);
    if (a == 315) drawString(dxo + x - 15, dyo + y - 18, TXT_NW, CENTER);
    dxi = dxo * 0.9;
    dyi = dyo * 0.9;
    drawLine(dxo + x, dyo + y, dxi + x, dyi + y, Black);
    dxo = dxo * 0.7;
    dyo = dyo * 0.7;
    dxi = dxo * 0.9;
    dyi = dyo * 0.9;
    drawLine(dxo + x, dyo + y, dxi + x, dyi + y, Black);
  }
  drawString(x, y - Cradius - 20,     TXT_N, CENTER);
  drawString(x, y + Cradius + 10,     TXT_S, CENTER);
  drawString(x - Cradius - 15, y - 5, TXT_W, CENTER);
  drawString(x + Cradius + 10, y - 5, TXT_E, CENTER);
  drawString(x + 3, y + 50, String(angle, 0) + "°", CENTER);
  setFont(OpenSans12B);
  drawString(x, y - 50, WindDegToOrdinalDirection(angle), CENTER);
  setFont(OpenSans24B);
  drawString(x + 3, y - 18, String(windspeed, 1), CENTER);
  setFont(OpenSans12B);
  drawString(x, y + 25, (Units == "M" ? "m/s" : "mph"), CENTER);
}

void DrawMoon(int x, int y, int diameter, int dd, int mm, int yy, hemisphere hemisphere) {
  double Phase = NormalizedMoonPhase(dd, mm, yy);

  if (hemisphere == south) Phase = 1 - Phase;
  // Draw dark part of moon
  fillCircle(x + diameter - 1, y + diameter, diameter / 2 + 1, DarkGrey);
  const int number_of_lines = 90;
  for (double Ypos = 0; Ypos <= number_of_lines / 2; Ypos++) {
    double Xpos = sqrt(number_of_lines / 2 * number_of_lines / 2 - Ypos * Ypos);
    // Determine the edges of the lighted part of the moon
    double Rpos = 2 * Xpos;
    double Xpos1, Xpos2;
    if (Phase < 0.5) {
      Xpos1 = -Xpos;
      Xpos2 = Rpos - 2 * Phase * Rpos - Xpos;
    }
    else {
      Xpos1 = Xpos;
      Xpos2 = Xpos - 2 * Phase * Rpos + Rpos;
    }
    // Draw light part of moon
    double pW1x = (Xpos1 + number_of_lines) / number_of_lines * diameter + x;
    double pW1y = (number_of_lines - Ypos)  / number_of_lines * diameter + y;
    double pW2x = (Xpos2 + number_of_lines) / number_of_lines * diameter + x;
    double pW2y = (number_of_lines - Ypos)  / number_of_lines * diameter + y;
    double pW3x = (Xpos1 + number_of_lines) / number_of_lines * diameter + x;
    double pW3y = (Ypos + number_of_lines)  / number_of_lines * diameter + y;
    double pW4x = (Xpos2 + number_of_lines) / number_of_lines * diameter + x;
    double pW4y = (Ypos + number_of_lines)  / number_of_lines * diameter + y;
    drawLine(pW1x, pW1y, pW2x, pW2y, White);
    drawLine(pW3x, pW3y, pW4x, pW4y, White);
  }
  drawCircle(x + diameter - 1, y + diameter, diameter / 2, Black);
}

void DrawRSSI(int x, int y, int rssi) {
  int WIFIsignal = 0;
  int xpos = 1;
  for (int _rssi = -100; _rssi <= rssi; _rssi = _rssi + 20) {
    if (_rssi <= -20)  WIFIsignal = 30; //            <-20dbm displays 5-bars
    if (_rssi <= -40)  WIFIsignal = 24; //  -40dbm to  -21dbm displays 4-bars
    if (_rssi <= -60)  WIFIsignal = 18; //  -60dbm to  -41dbm displays 3-bars
    if (_rssi <= -80)  WIFIsignal = 12; //  -80dbm to  -61dbm displays 2-bars
    if (_rssi <= -100) WIFIsignal = 6;  // -100dbm to  -81dbm displays 1-bar
    fillRect(x + xpos * 8, y - WIFIsignal, 6, WIFIsignal, Black);
    xpos++;
  }
}

void Display_UVIndexLevel(int x, int y, float UVI) {
  String Level = "";
  if (UVI <= 2)              Level = " (L)";
  if (UVI >= 3 && UVI <= 5)  Level = " (M)";
  if (UVI >= 6 && UVI <= 7)  Level = " (H)";
  if (UVI >= 8 && UVI <= 10) Level = " (VH)";
  if (UVI >= 11)             Level = " (EX)";
  drawString(x + 20, y - 5, String(UVI, (UVI < 0 ? 1 : 0)) + Level, LEFT);
  DrawUVI(x - 10, y - 5);
}

void DisplayStatusSection(int x, int y, int rssi) {
  setFont(OpenSans8B);
  DrawRSSI(x + 305, y + 15, rssi);
  DrawBattery(x + 150, y);
}

void Nodata(int x, int y, bool IconSize, String IconName) {
  if (IconSize == LargeIcon) setFont(OpenSans24B); else setFont(OpenSans12B);
  drawString(x - 3, y - 10, "?", CENTER);
}

void DrawMoonImage(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = moon_width, .height =  moon_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) moon_data);
}

void DrawSunriseImage(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = sunrise_width, .height =  sunrise_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) sunrise_data);
}

void DrawSunsetImage(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = sunset_width, .height =  sunset_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) sunset_data);
}
