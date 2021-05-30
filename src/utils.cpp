#include <Arduino.h>
#include "utils.h"

float SumOfPrecip(float DataArray[], int readings) {
  float sum = 0;
  
  for (int i = 0; i <= readings; i++) {
    sum += DataArray[i];
  }

  return sum;
}

String TitleCase(String text) {
  if (text.length() > 0) {
    String temp_text = text.substring(0, 1);
    temp_text.toUpperCase();
    return temp_text + text.substring(1); // Title-case the string
  }
  else return text;
}

