#include <Arduino.h>

#include "lang.h"


#if defined(LANG_FR)

//Temperature - Humidity - Forecast
const String TXT_FORECAST_VALUES  = "Prévisions à 3 jours";
const String TXT_CONDITIONS       = "Conditions";
const String TXT_DAYS             = "(Jours)";
const String TXT_TEMPERATURES     = "Température";
const String TXT_TEMPERATURE_C    = "Température (°C)";
const String TXT_TEMPERATURE_F    = "Température (°F)";
const String TXT_HUMIDITY_PERCENT = "Humidité (%)";

// Pressure
const String TXT_PRESSURE         = "Pression";
const String TXT_PRESSURE_HPA     = "Pression (hPa)";
const String TXT_PRESSURE_IN      = "Pression (in)";
const String TXT_PRESSURE_STEADY  = "Stable";
const String TXT_PRESSURE_RISING  = "Hausse";
const String TXT_PRESSURE_FALLING = "Baisse";

//RainFall / SnowFall
const String TXT_RAINFALL_MM = "Pluie (mm)";
const String TXT_RAINFALL_IN = "Pluie (in)";
const String TXT_SNOWFALL_MM = "Neige (mm)";
const String TXT_SNOWFALL_IN = "Neige (in)";
const String TXT_PRECIPITATION_SOON = "Prec.";


//Sun
const String TXT_SUNRISE  = "Sol. Levé";
const String TXT_SUNSET   = "Sol. Couché";

//Moon
const String TXT_MOON_NEW             = "Nouvelle Lune";
const String TXT_MOON_WAXING_CRESCENT = "Premier Croissant";
const String TXT_MOON_FIRST_QUARTER   = "Premier Quartier";
const String TXT_MOON_WAXING_GIBBOUS  = "Gibbeuse Croissan.";
const String TXT_MOON_FULL            = "Pleine Lune";
const String TXT_MOON_WANING_GIBBOUS  = "Gibbeuse Décroiss.";
const String TXT_MOON_THIRD_QUARTER   = "Dernier Quartier";
const String TXT_MOON_WANING_CRESCENT = "Dernier Croissant";

//Power / WiFi
const String TXT_POWER  = "Puiss";
const String TXT_WIFI   = "WiFi";
const char* TXT_UPDATED = "M-à-J:";


//Wind
const String TXT_WIND_SPEED_DIRECTION = "Vent Vitesse/Direction";
const String TXT_N   = "N";
const String TXT_NNE = "NNE";
const String TXT_NE  = "NE";
const String TXT_ENE = "ENE";
const String TXT_E   = "E";
const String TXT_ESE = "ESE";
const String TXT_SE  = "SE";
const String TXT_SSE = "SSE";
const String TXT_S   = "S";
const String TXT_SSW = "SSO";
const String TXT_SW  = "SO";
const String TXT_WSW = "OSO";
const String TXT_W   = "O";
const String TXT_WNW = "ONO";
const String TXT_NW  = "NO";
const String TXT_NNW = "NNO";

//Day of the week
const char* weekday_D[] = { "Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam" };

//Month
const char* month_M[] = { "Jan", "Fév", "Mar", "Avr", "Mai", "Jun", "Jul", "Aou", "Sep", "Oct", "Nov", "Déc" };

#elif defined(LANG_PL)

//Temperature - Humidity - Forecast
const String TXT_FORECAST_VALUES  = "3-Day Forecast Values";
const String TXT_CONDITIONS       = "Conditions";
const String TXT_DAYS             = "(Days)";
const String TXT_TEMPERATURES     = "Temperature";
const String TXT_TEMPERATURE_C    = "Temperature (°C)";
const String TXT_TEMPERATURE_F    = "Temperature (°F)";
const String TXT_HUMIDITY_PERCENT = "Humidity (%)";

// Pressure
const String TXT_PRESSURE         = "Pressure";
const String TXT_PRESSURE_HPA     = "Pressure (hPa)";
const String TXT_PRESSURE_IN      = "Pressure (in)";
const String TXT_PRESSURE_STEADY  = "Steady";
const String TXT_PRESSURE_RISING  = "Rising";
const String TXT_PRESSURE_FALLING = "Falling";

//RainFall / SnowFall
const String TXT_RAINFALL_MM = "Rainfall (mm)";
const String TXT_RAINFALL_IN = "Rainfall (in)";
const String TXT_SNOWFALL_MM = "Snowfall (mm)";
const String TXT_SNOWFALL_IN = "Snowfall (in)";
const String TXT_PRECIPITATION_SOON = "Prec.";


//Sun
const String TXT_SUNRISE  = "Sunrise";
const String TXT_SUNSET   = "Sunset";

//Moon
const String TXT_MOON_NEW             = "New";
const String TXT_MOON_WAXING_CRESCENT = "Waxing Crescent";
const String TXT_MOON_FIRST_QUARTER   = "First Quarter";
const String TXT_MOON_WAXING_GIBBOUS  = "Waxing Gibbous";
const String TXT_MOON_FULL            = "Full";
const String TXT_MOON_WANING_GIBBOUS  = "Waning Gibbous";
const String TXT_MOON_THIRD_QUARTER   = "Third Quarter";
const String TXT_MOON_WANING_CRESCENT = "Waning Crescent";

//Power / WiFi
const String TXT_POWER  = "Zasilanie";
const String TXT_WIFI   = "WiFi";
const char* TXT_UPDATED = "Aktualizacja:";


//Wind
const String TXT_WIND_SPEED_DIRECTION = "Wind Speed/Direction";
const String TXT_N   = "N";
const String TXT_NNE = "NNE";
const String TXT_NE  = "NE";
const String TXT_ENE = "ENE";
const String TXT_E   = "E";
const String TXT_ESE = "ESE";
const String TXT_SE  = "SE";
const String TXT_SSE = "SSE";
const String TXT_S   = "S";
const String TXT_SSW = "SSW";
const String TXT_SW  = "SW";
const String TXT_WSW = "WSW";
const String TXT_W   = "W";
const String TXT_WNW = "WNW";
const String TXT_NW  = "NW";
const String TXT_NNW = "NNW";

//Day of the week
const char* weekday_D[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

//Month
const char* month_M[] = { "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Spe", "Wrz", "Paz", "Lis", "Gru" };

#else

//Temperature - Humidity - Forecast
const String TXT_FORECAST_VALUES  = "3-Day Forecast Values";
const String TXT_CONDITIONS       = "Conditions";
const String TXT_DAYS             = "(Days)";
const String TXT_TEMPERATURES     = "Temperature";
const String TXT_TEMPERATURE_C    = "Temperature (°C)";
const String TXT_TEMPERATURE_F    = "Temperature (°F)";
const String TXT_HUMIDITY_PERCENT = "Humidity (%)";

// Pressure
const String TXT_PRESSURE         = "Pressure";
const String TXT_PRESSURE_HPA     = "Pressure (hPa)";
const String TXT_PRESSURE_IN      = "Pressure (in)";
const String TXT_PRESSURE_STEADY  = "Steady";
const String TXT_PRESSURE_RISING  = "Rising";
const String TXT_PRESSURE_FALLING = "Falling";

//RainFall / SnowFall
const String TXT_RAINFALL_MM = "Rainfall (mm)";
const String TXT_RAINFALL_IN = "Rainfall (in)";
const String TXT_SNOWFALL_MM = "Snowfall (mm)";
const String TXT_SNOWFALL_IN = "Snowfall (in)";
const String TXT_PRECIPITATION_SOON = "Prec.";


//Sun
const String TXT_SUNRISE  = "Sunrise";
const String TXT_SUNSET   = "Sunset";

//Moon
const String TXT_MOON_NEW             = "New";
const String TXT_MOON_WAXING_CRESCENT = "Waxing Crescent";
const String TXT_MOON_FIRST_QUARTER   = "First Quarter";
const String TXT_MOON_WAXING_GIBBOUS  = "Waxing Gibbous";
const String TXT_MOON_FULL            = "Full";
const String TXT_MOON_WANING_GIBBOUS  = "Waning Gibbous";
const String TXT_MOON_THIRD_QUARTER   = "Third Quarter";
const String TXT_MOON_WANING_CRESCENT = "Waning Crescent";

//Power / WiFi
const String TXT_POWER  = "Power";
const String TXT_WIFI   = "WiFi";
const char* TXT_UPDATED = "Updated:";


//Wind
const String TXT_WIND_SPEED_DIRECTION = "Wind Speed/Direction";
const String TXT_N   = "N";
const String TXT_NNE = "NNE";
const String TXT_NE  = "NE";
const String TXT_ENE = "ENE";
const String TXT_E   = "E";
const String TXT_ESE = "ESE";
const String TXT_SE  = "SE";
const String TXT_SSE = "SSE";
const String TXT_S   = "S";
const String TXT_SSW = "SSW";
const String TXT_SW  = "SW";
const String TXT_WSW = "WSW";
const String TXT_W   = "W";
const String TXT_WNW = "WNW";
const String TXT_NW  = "NW";
const String TXT_NNW = "NNW";

//Day of the week
const char* weekday_D[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

//Month
const char* month_M[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

#endif