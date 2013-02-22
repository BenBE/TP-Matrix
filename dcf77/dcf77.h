#ifndef H_DCF77
#define H_DCF77

#include <stdint.h>

#include <avr/pgmspace.h>

#define DCF77_BLOCKSIZE 5

typedef union dcf77_message {
    uint8_t raw[DCF77_BLOCKSIZE];
    struct {
        unsigned int day: 4;
        unsigned int night: 4;
        unsigned int extremes: 4;
        unsigned int pop: 3;
        unsigned int anomaly: 1;
        unsigned int temperature: 6;
        unsigned int state: 2;
        unsigned int checksum: 16;
    } data;
    struct {
        unsigned int block1 : 12;
        unsigned int block2 : 14;
        unsigned int block3 : 14;
    } cipher;
    struct { //Use unsigned long to exceed 16 bit field width limitation
        unsigned long regL : 20;
        unsigned long regR : 20;
    } cipher_reg;
} dcf77_message_t;

typedef union dcf77_keydata {
    uint8_t raw[DCF77_BLOCKSIZE];
    struct {
        /*bcd*/ unsigned int minute : 8;
        /*bcd*/ unsigned int hour : 8;
        /*bcd*/ unsigned int day : 8;
        /*bcd*/ unsigned int month : 5;
        /*bcd*/ unsigned int dow : 3;
        /*bcd*/ unsigned int year : 8;
    } data;
} dcf77_keydata_t;

typedef enum dcf77_weather {
    DCF77_WEATHER_NONE = 0,

    DCF77_WEATHER_CLEAR = 1,
    DCF77_WEATHER_PARTIALLY_CLOUDY = 2,
    DCF77_WEATHER_MOSTLY_CLOUDY = 3,
    DCF77_WEATHER_CLOUDY = 4,
    DCF77_WEATHER_LOW_STRATUS = 5,
    DCF77_WEATHER_FOG = 6,
    DCF77_WEATHER_BRASH = 7,
    DCF77_WEATHER_SHOWERS = 8,
    DCF77_WEATHER_RAINSTORM = 9,
    DCF77_WEATHER_MULTICELL_CLUSTER_STORMS = 10,
    DCF77_WEATHER_HEAT_THUNDERSTORM = 11,
    DCF77_WEATHER_SLEET_SHOWER = 12,
    DCF77_WEATHER_SNOW_SHOWER = 13,
    DCF77_WEATHER_SLEET = 14,
    DCF77_WEATHER_SNOWFALL = 15
} dcf77_weather_t;

typedef enum dcf77_extremes {
    DCF77_EXTREMES_NONE = 0,

    DCF77_EXTREMES_HEAVY_WEATHERS_24 = 1,
    DCF77_EXTREMES_HEAVY_WEATHERS_DAY = 2,
    DCF77_EXTREMES_HEAVY_WEATHERS_NIGHT = 3,
    DCF77_EXTREMES_STORM_24 = 4,
    DCF77_EXTREMES_STORM_DAY = 5,
    DCF77_EXTREMES_STORM_NIGHT = 6,
    DCF77_EXTREMES_BLASTS_DAY = 7,
    DCF77_EXTREMES_BLASTS_NIGHT = 8,
    DCF77_EXTREMES_FREEZING_RAIN_MORNING = 9,
    DCF77_EXTREMES_FREEZING_RAIN_AFTERNOON = 10,
    DCF77_EXTREMES_FREEZING_RAIN_NIGHT = 11,
    DCF77_EXTREMES_FINE_PARTICLES = 12,
    DCF77_EXTREMES_OZONE = 13,
    DCF77_EXTREMES_RADIATION = 14,
    DCF77_EXTREMES_FLOOD = 15
} dcf77_extremes_t;

typedef struct dcf77_forecast {
    unsigned int morning_weather: 2;
    unsigned int sunshine_duration: 2;
} dcf77_forecast_t;

typedef enum dcf77_morning_weather {
    DCF77_MORNING_WEATHER_EQUAL = 0,
    DCF77_MORNING_WEATHER_STEP1 = 1,
    DCF77_MORNING_WEATHER_STEP2 = 2,
    DCF77_MORNING_WEATHER_STEP3 = 3
} dcf77_morning_weather_t;

typedef enum dcf77_sunshine {
    DCF77_SUNSHINE_0_1_2 = 0,
    DCF77_SUNSHINE_2_3_4 = 1,
    DCF77_SUNSHINE_5_6 = 2,
    DCF77_SUNSHINE_7_8 = 3
} dcf77_sunshine_t;

typedef union dcf77_cipherblock {
    uint8_t raw[2*DCF77_BLOCKSIZE];
    struct {
        dcf77_message_t message;
        dcf77_keydata_t keyinfo;
    } data;
} dcf77_cipherblock_t;

typedef union dcf77_amdata {
    uint8_t raw[8];
    struct {
        unsigned int reserved_start_of_minute : 1;
        unsigned int status_information : 14;

        unsigned int reserve_antenna : 1;
        unsigned int timezone_switch : 1;
        unsigned int timezone_offset : 2;
        unsigned int leap_second : 1;

        unsigned int reserved_start_of_timeinfo : 1;

        unsigned int time_min_0X : 4;
        unsigned int time_min_X0 : 3;
        unsigned int time_min_parity : 1;

        unsigned int time_hour_0X : 4;
        unsigned int time_hour_X0 : 2;
        unsigned int time_hour_parity : 1;

        unsigned int date_day_0X : 4;
        unsigned int date_day_X0 : 2;

        unsigned int date_dow : 3;

        unsigned int date_month_0X : 4;
        unsigned int date_month_X0 : 1;

        unsigned int date_year_0X : 4;
        unsigned int date_year_X0 : 4;

        unsigned int date_parity : 1;

        unsigned int resetved_leap_second : 1;
    } data;
} dcf77_amdata_t;

void dcf77_encode(dcf77_cipherblock_t *buf, dcf77_amdata_t *min1, dcf77_amdata_t *min2, dcf77_amdata_t *min3);
void dcf77_decode(dcf77_cipherblock_t *buf, dcf77_amdata_t *min1, dcf77_amdata_t *min2, dcf77_amdata_t *min3);

void dcf77_encrypt(dcf77_cipherblock_t *data);
void dcf77_decrypt(dcf77_cipherblock_t *data);

#endif
