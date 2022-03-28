#ifndef _LED
#define _LED

void set_led();

#endif

#define WHITE 12
#define BLUE 11

void set_led(){
  pinMode(WHITE, OUTPUT);
  pinMode(BLUE, OUTPUT);
}