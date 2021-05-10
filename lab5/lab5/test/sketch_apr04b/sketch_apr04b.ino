void analog_init()
{
  // Analog functions can be used as-is
  ADCSRA |= (1 << ADEN);
  ADMUX |= (1 << REFS0);
  ADMUX |= (1 << ADLAR); // Left justified output for 8bit mode
  ADCSRA |= (1 << ADSC); // start conversion
}

uint8_t analog8(uint8_t channel)
{
  // Analog functions can be used as-is
  ADMUX &= 0xF0;
  ADMUX |= channel;
  ADCSRA |= (1 << ADSC);
  while ( ADCSRA & ( 1 << ADSC ) );
  return ADCH;
}
void setup()
{
  Serial.begin(9600);
  analog_init();
  // Setup your pins and ports here.
  asm("sbi 0x0A, 6"); // Set bit 6 in PORTD for output
  asm("cbi 0x0A, 7"); // Clear bit 7 in PORTD for input
  asm("sbi 0x0B, 7"); // Set pullup resistor for pin 7 in PORTD
}
void loop()
{
  asm(" start: ");
  // Get analog values for X and Y
  // Load from ADCH (0x79) into r16/r17
  int x_axis = analog8(0);
  asm(" lds r16, 0x79 ");
  int y_axis = analog8(1);
  asm(" lds r17, 0x79 ");
  // EVERYTHING BELOW THIS LINE SHOULD BE ASSEMBLY
  // Click button logic here. Should the button LED be on or off?
  asm(" in r25, 0x09 "); // Load PIND into r25
  asm(" andi r25, 0x80 "); // Bit-mask the 7th bit
  asm(" cpi r25, 0x80 "); // Compare with 0x80
  asm(" brne click_on "); // If not zero, branch to click_on
  asm(" cbi 0x0B, 6 "); // Turn off LED
  asm(" rjmp end ");
  asm(" click_on: ");
  asm(" sbi 0x0B, 6 "); // Turn on LED
  asm(" end: ");
  // Up direction logic here. Should the Up LED be on or off?
  // y_axis logic
  asm("cpi r17, 127");
  asm("breq y_axis_origin"); // if equal, y is at origin, jump to pre_x_axis_logic to clear y bits
  
  asm("cpi r17, 127");
  asm("brlo y_axis_up");

  asm(" y_axis_down:");
  Serial.println(" y_axis down");
  asm(" cbi 0x0B, 5 "); // Turn off LED
  asm(" sbi 0x0B, 3 "); // Turn on LED
  asm(" rjmp x_axis_logic ");

  asm(" y_axis_up:");
  Serial.println(" y_axis up");
  asm(" cbi 0x0B, 3 "); // Turn off LED
  asm(" sbi 0x0B, 5 "); // Turn on LED
  asm(" rjmp x_axis_logic");

  asm(" y_axis_origin:");
  Serial.println(" y_axis equal");
  asm(" cbi 0x0B, 3 "); // Turn off LED
  asm(" cbi 0x0B, 5 "); // Turn off LED

  // Y Axis handlling
//  asm(" cpi r17, 127 ");   // <------ CHANGE 128 based on your joystick y-axis baseline ----->
//  asm(" breq Y_Not_Moving ");
//
//  asm(" cpi r17, 127 ");   // <------ CHANGE 128 based on your joystick y-axis baseline ----->
//  asm(" brlo Y_Moving_Up ");
//
//  asm(" cpi r17, 128 ");   // <------ CHANGE 129 based on your joystick y-axis baseline + 1 ----->
//  asm(" brge Y_Moving_Down ");
//  
//  asm(" Y_Moving_Up: ");
//  asm(" sbi 0x0B, 3 ");
//  asm(" cbi 0x0B, 5 ");
//  asm(" rjmp y_axis_handled ");
//
//  asm(" Y_Not_Moving: ");
//  asm(" cbi 0x0B, 3 ");
//  asm(" cbi 0x0B, 5 ");
//  asm(" rjmp y_axis_handled ");
//
//
//  asm(" Y_Moving_Down: ");
//  asm(" cbi 0x0B, 3 ");
//  asm(" sbi 0x0B, 5 ");
//  asm(" rjmp y_axis_handled ");
   
 
  asm(" y_axis_handled: ");

  // x_axis logic
  asm(" x_axis_logic:");
  //asm("cpi r17, 125");
  //asm("breq x_axis_at_origin"); // if equal, x is at origin, jump to x_axis_at_origin

  // Down direction logic.
  // Left direction logic here.

  // Right direction logic.
  // asm(" x_axis_at_origin:");


  // EVERYTHING ABOVE THIS LINE SHOULD BE ASSEMBLY
  // You can use this serial code for handy debugging.
  // It will let you observe the values coming out of your ADC.
  Serial.print("< ");
  Serial.print(x_axis);
  Serial.print(", ");
  Serial.print(y_axis);
  Serial.println(" >");
  delay(250);
  asm(" rjmp start ");
}
