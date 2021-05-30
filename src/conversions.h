#pragma once

inline float mm_to_inches(float value_mm) {
  return 0.0393701 * value_mm;
}

inline float hPa_to_inHg(float value_hPa) {
  return 0.02953 * value_hPa;
}

String ConvertUnixTimeToTime(int unix_time);
String ConvertUnixTimeToDateTime(int unix_time);
int JulianDate(int d, int m, int y);
double NormalizedMoonPhase(int d, int m, int y);
String MoonPhase(int d, int m, int y, hemisphere hemisphere);
String WindDegToOrdinalDirection(float winddirection);
