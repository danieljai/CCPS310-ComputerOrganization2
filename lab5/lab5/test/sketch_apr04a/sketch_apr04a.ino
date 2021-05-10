void setup() {
  asm("sbi 0x0A, 6"); // Set bit 6 in PORTD for output
  asm("cbi 0x0A, 7"); // Clear bit 7 in PORTD for input
  asm("sbi 0x0B, 7"); // Set pullup resistor for pin 7 in PORTD

  
  Serial.begin(9600);
  ADCSRA |= (1 << ADEN); // enable ADC
  ADMUX |= (1 << REFS0); // Vref AVcc page 255
  ADMUX |= (1 << ADLAR); // Left justified output for 8bit mode
  ADCSRA |= (1 << ADSC); // start conversion
}

uint8_t analog8( uint8_t channel ) {
  ADMUX &= 0xF0; //Clearing the last 4 bits of ADMUX
  ADMUX |= channel; //Selecting channel
  ADCSRA |= (1 << ADSC);
  while ( ADCSRA & ( 1 << ADSC ) );
  return ADCH;
}

void loop() {
  int x_axis = analog8(0);
  asm(" lds r16, 0x79 ");
  int y_axis = analog8(1);
  asm(" lds r17, 0x79 ");
  Serial.print("< \t");
  Serial.print(x_axis);
  Serial.print(", \t");
  Serial.print(y_axis);
  Serial.println(" >");

  // Button pressing
  asm(" in r25, 0x09 "); // Load PIND into r25
  asm(" andi r25, 0x80 "); // Bit-mask the 7th bit
  asm(" cpi r25, 0x80 "); // Compare with 0x80
  asm(" brne click_on "); // If not zero, branch to click_on
  asm(" cbi 0x0B, 6 "); // Turn off LED
  asm(" rjmp end ");
  asm(" click_on: ");
  asm(" sbi 0x0B, 6 "); // Turn on LED
  asm(" end: ");
  
  delay(2);
}
