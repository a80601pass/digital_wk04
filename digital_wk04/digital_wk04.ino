#include <Wire.h>
#include <SPI.h>
#include "SSD1306Wire.h"
#include "animation.h"
#define Logo_width 64
#define Logo_height 64

SSD1306Wire  display(0x3c, 22, 23);
int buttonpin = 12;
int pre_st = 0;
int cur_st = 0;
int walking = 0;
unsigned long pre_time = 0;
unsigned long cur_time = 0;
int walk_count = 0;
int idle_count = 0;
int walk_duration = 120;
int idle_duration = 250;
int curpos = 0;

void setup() {
  pinMode(buttonpin,INPUT);
  Serial.begin(9600);
  display.init();
  display.setContrast(255); 
  cur_time = millis();
  pre_time = cur_time;
  display.clear();
  display.drawXbm(0,0,Logo_width,Logo_height,idle[idle_count]);
  display.display();
}

void loop() { 
  cur_time = millis();
  cur_st = digitalRead(buttonpin);
  Serial.println(cur_st);
  delay(30);
  if(pre_st == 0 && cur_st == 1)
  {
    walking = 1;
    walk_count = 0;
    pre_time = cur_time;
    cur_time = cur_time + walk_duration;
  }
  if(pre_st == 1 && cur_st == 0)
  {
    walking = 0;
    pre_time = cur_time;
    cur_time = cur_time + idle_duration;
  }
  pre_st = cur_st;
  if(walking)
  {
    if((cur_time - pre_time) > walk_duration)
    {
      display.clear();
      curpos = curpos + 40*(cur_time - pre_time)/1000;
      if(curpos > (64+64))
      {
        curpos = -64;
      }
      display.drawXbm(curpos,0,Logo_width,Logo_height,walk[walk_count]);
      display.display();
      walk_count++;
      if(walk_count > 7)
      {
        walk_count = 0;
      }
      pre_time = cur_time;
    }
  }
  else{
    if((cur_time - pre_time) > idle_duration)
    {
      display.clear();
      display.drawXbm(curpos,0,Logo_width,Logo_height,idle[idle_count]);
      display.display();
      idle_count++;
      if(idle_count > 1)
      {
        idle_count = 0;
      }
      pre_time = cur_time;
    }
  }
}
