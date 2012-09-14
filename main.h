#ifndef H_MAIN
#define H_MAIN

#define X86

#ifndef X86
  #include <Arduino.h>
  #include <avr/pgmspace.h>
#else 

  #include <stdint.h>
  typedef int8_t     prog_int8_t;
  typedef uint8_t    prog_uint8_t;
  typedef int16_t    prog_int16_t;
  typedef uint16_t   prog_uint16_t;
  typedef int32_t    prog_int32_t;
  typedef uint32_t   prog_uint32_t;
  typedef int64_t    prog_int64_t;
  typedef uint64_t   prog_uint64_t;

  typedef int8_t     byte;


  #define   PROGMEM 
  #define   PGM_P   const char *
  #define   PGM_VOID_P   const void *
  #define   PSTR(s)   ((const PROGMEM char *)(s))
  #define   pgm_read_byte_near(address_short)   ((uint16_t)(address_short))
  #define   pgm_read_word_near(address_short)  ((uint16_t)(address_short))
  #define   pgm_read_dword_near(address_short) ((uint16_t)(address_short))
  #define   pgm_read_float_near(address_short) ((uint16_t)(address_short))
  #define   pgm_read_byte_far(address_long)   ((uint32_t)(address_long))
  #define   pgm_read_word_far(address_long)   ((uint32_t)(address_long))
  #define   pgm_read_dword_far(address_long)  ((uint32_t)(address_long))
  #define   pgm_read_float_far(address_long)  ((uint32_t)(address_long))
  #define   pgm_read_byte(address_short)   pgm_read_byte_near(address_short)
  #define   pgm_read_word(address_short)   pgm_read_word_near(address_short)
  #define   pgm_read_dword(address_short)   pgm_read_dword_near(address_short)
  #define   pgm_read_float(address_short)   pgm_read_float_near(address_short)

  #define true 1;
#endif

#include <uTPlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void forest_fire(void);
void pacman(void);
void string_anim(char id);
void heart(void);

void leuchtturm(void);
void matrix_code(void);

void game_of_life(void);

void nyancat(void);

void progress(void);

void bonfire(void);

void PlayPong(void);

void drop(void);
void drop2(void);

#ifdef __cplusplus
}
#endif

#endif
