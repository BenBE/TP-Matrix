#include "uTPlib.h"

//	SCK	0x20
//	DATA	0x08
//	LE	0x04
//	OE	0x02

void display_mode(char mode) // 0:normal 1:special
{
    PORTB &=~ 0x2d;
//  digitalWrite(pinData, LOW);
//  digitalWrite(pinLE, LOW);
//  digitalWrite(pinSCK, LOW);
//    delay_us(20);

    PORTB |=  0x02;
    delay_us(10);
    PORTB |=  0x20;
    delay_us(10);
//    delay_us(10);
    PORTB &=~ 0x20;
    delay_us(10);
//    delay_us(20);
//  digitalWrite(pinOE, HIGH); // OE 1
//  delay(1);
//  digitalWrite(pinSCK, HIGH);
//  delay(1);
//  digitalWrite(pinSCK, LOW);
//  delay(1);

    PORTB &=~ 0x02;
    delay_us(10);
    PORTB |=  0x20;
    delay_us(10);
    PORTB &=~ 0x20;
    delay_us(10);
//  digitalWrite(pinOE, LOW); // OE 0
//  delay(1);
//  digitalWrite(pinSCK, HIGH);
//  delay(1);
//  digitalWrite(pinSCK, LOW);
//  delay(1);

    PORTB |=  0x02;
    delay_us(10);
    PORTB |=  0x20;
    delay_us(10);
    PORTB &=~ 0x20;
    delay_us(10);
//  digitalWrite(pinOE, HIGH); // OE 1
//  delay(1);
//  digitalWrite(pinSCK, HIGH);
//  delay(1);
//  digitalWrite(pinSCK, LOW);
//  delay(1);

    if(mode) {
        PORTB |=  0x04;
        delay_us(10);
    }
    PORTB |=  0x02;
    delay_us(10);
    PORTB |=  0x20;
    delay_us(10);
    PORTB &=~ 0x20;
    delay_us(10);
//  if (special) digitalWrite(pinLE, HIGH);
//  digitalWrite(pinOE, HIGH); // OE 1
//  delay(1);
//  digitalWrite(pinSCK, HIGH);
//  delay(1);
//  digitalWrite(pinSCK, LOW);
//  delay(1);

    PORTB &=~ 0x04;
    delay_us(10);
    PORTB |=  0x02;
    delay_us(10);
    PORTB |=  0x20;
    delay_us(10);
    PORTB &=~ 0x20;
    delay_us(10);
//  digitalWrite(pinLE, LOW);
//  digitalWrite(pinOE, HIGH); // OE 1
//  delay(1);
//  digitalWrite(pinSCK, HIGH);
//  delay(1);
//  digitalWrite(pinSCK, LOW);
//  delay(1);
}

