#include "uTPlib.h"

#include <WProgram.h>

#define pin_pwm_timer	3
#define int_pwm_timer	1
#define frq_pwm_select	-1

void display_init()
{
  // System stuff
  PORTB = 0x00;
  DDRB = 0x2E;

  display_mode(0);

  // more system stuff - must be at end (start display_refresh())
  pinMode(        pin_pwm_timer, OUTPUT);
  analogWrite(    pin_pwm_timer, 32);
  attachInterrupt(int_pwm_timer, display_interrupt, RISING);
  TCCR2B = (TCCR2B & 0b11111000) | (3 - frq_pwm_select); // -1=500Hz
  // TCCR2B = TCCR2B & 0b11111000 | (frq_pwm_select==0?3:(frq_pwm_select==1?2:1)); // 3906Hz/976Hz -
  // http://www.arduino.cc/playground/Min/TimerPWMCheatsheet
}
