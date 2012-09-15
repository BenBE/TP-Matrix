#include "uTPlib.h"

#define pin_pwm_timer	3
#define int_pwm_timer	1
#define frq_pwm_select	-1

#ifdef X86

#include <GL/glut.h>

void *display_refresh(){
  while(1){
    usleep(2);
    if(time_vsynced == 0) {
      //pthread_cond_signal(&c_time_sync);
      time_vsynced = 1;
    }
  }
  pthread_exit(NULL);
}
#endif

void display_init()
{
  #ifndef X86
  // System stuff
  PORTB = 0x00;
  DDRB = 0x2E;
  #endif

  display_mode(0);

  #ifndef X86
  // more system stuff - must be at end (start display_refresh())
  pinMode(        pin_pwm_timer, OUTPUT);
  analogWrite(    pin_pwm_timer, 32);
  attachInterrupt(int_pwm_timer, display_interrupt, RISING);
  TCCR2B = (TCCR2B & 0b11111000) | (3 - frq_pwm_select); // -1=500Hz
  // TCCR2B = TCCR2B & 0b11111000 | (frq_pwm_select==0?3:(frq_pwm_select==1?2:1)); // 3906Hz/976Hz -
  // http://www.arduino.cc/playground/Min/TimerPWMCheatsheet
  #else 
  pthread_cond_init(&c_time_sync,NULL);
  pthread_mutex_init(&m_time_sync,NULL);

  pthread_create(&display_thread,NULL,display_refresh,NULL); 
  #endif
}
