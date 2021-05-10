// Andy Lee
// 500163559

#include "pitches.h"
#define BUZZER_CLOCK 16000000/8

void initTimer(void) 
{
  TCCR1A = (1 << COM1A1) | (1 << WGM11); 
  TCCR1B = (1 << WGM13)  | (1 << WGM12)  | (1 << CS11);
}

void tone(uint16_t freq) 
{
  asm("sbi 0x04, 1");
  ICR1 = BUZZER_CLOCK/freq;
  OCR1A = ICR1*3/4;
}

void mute(void) 
{
  asm(" cbi 0x04, 1 ");
  asm(" cbi 0x05, 1 ");
}


void setup() 
{ 
  initTimer();
}

void loop() 
{
  uint16_t melody[] = { 
    NOTE_G3, NOTE_E3, NOTE_C3, 
    NOTE_G2, NOTE_G3, NOTE_E3, NOTE_C3, 
    NOTE_E3, 0, NOTE_C3, 0,
    NOTE_E3, 0,
    NOTE_D3, NOTE_C3, NOTE_C3, NOTE_D3, NOTE_C3, NOTE_A2, NOTE_C3, 0,
    NOTE_A2, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_E3, NOTE_F3, NOTE_G3, 0
    };
  uint8_t noteDurations[] = { 
    2, 4, 4, 
    4, 4, 4, 4, 
    4, 4, 4, 4,  
    2, 4,
    4, 4, 8, 8, 4, 4, 4, 2,
    4, 4, 8, 8, 4, 4, 4, 2,
    };

  for (int noteID = 0; noteID < 29; noteID++) 
  {
    int freq = melody[noteID];
    if (freq == 0) mute();
    else tone(freq);
    uint16_t noteDuration = 1000/noteDurations[noteID];
    delay(noteDuration);
    mute();
    uint16_t muteDuration = noteDuration * 3/10;
    delay(muteDuration);
  }
  delay(500);
}
