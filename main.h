#ifndef H_MAIN
#define H_MAIN

#define X86

#ifndef X86
  #include <Arduino.h>
  #include <avr/pgmspace.h>
#else 
  #include "x86.h"
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

void cacert(void);

#ifdef __cplusplus
}
#endif

#endif
