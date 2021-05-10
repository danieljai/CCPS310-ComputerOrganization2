#define BUZZER_CLOCK 16000000/8

uint8_t analog8(uint8_t ch) {
  ADMUX  &= 0xF0;     
  ADMUX  |= ch;  
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  return ADCH;
}

void analog_init() {
   ADCSRA |= (1 << ADEN);   
   ADMUX  |= (1 << REFS0); 
   ADMUX  |= (1 << ADLAR);  
   ADCSRA |= (1 << ADSC);  
}

void timer_init(void) {
   asm(" sbi 0x04, 1 "); // Use PWM pin 9
   TCCR1A = (1 << COM1A1) | (1 << WGM11); 
   TCCR1B = (1 << WGM13)  | (1 << WGM12)  | (1 << CS11);
}

void tone(uint16_t freq) {
   ICR1 = BUZZER_CLOCK/freq;
   OCR1A = ICR1*3/4;
}

void setup() { 
  analog_init();
  timer_init();
}

void loop() {
  int pot = analog8(0);
  int freq = 200 + pot*7;
  tone(freq);    
  //delay(2);
}
