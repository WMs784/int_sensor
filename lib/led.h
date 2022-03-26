#ifndef _LED
#define _LED

void set_led();

#endif

#define WHITE A3

void set_led(){
  pinMode(WHITE, OUTPUT);
}