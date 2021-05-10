/*

CCPS 310 - Winter 2020 - Lab 4
Group Members
- Andy Lee      , Student #500163559
- Aaron Eliahoo , Student #500640345
- Sohrab Soltani, Srudent #500801172

  Dear Alexander,

  Our joystick was outputting <126, 128> as its baseline so we have hardcoded that as the baseline.

  If you need to test it with your joystick, please search for and update the following lines in the
  code with your joystick baseline:

   1 - asm(" cpi r17, 128 ");  <------
       asm(" breq Y_Not_Moving ");

   2 - asm(" cpi r17, 128 ");  <------
       asm(" brlo Y_Moving_Up ");

   3 - asm(" cpi r17, 129 ");  <------
       asm(" brge Y_Moving_Down ");

   4 - asm(" cpi r16, 126 ");  <------
       asm(" breq X_Not_Moving ");
       
   5 - asm(" cpi r16, 128 ");  <------
       asm(" brlo X_Moving_Left ");

   6 - asm(" cpi r16, 129 ");  <------
       asm(" brge X_Moving_Right ");

   Thank you,
   Regards,
   The Team

*/

void analog_init()
{
  ADCSRA |= (1 << ADEN);  // enable ADC
  ADMUX  |= (1 << REFS0); // Vref AVcc page 255
  ADMUX  |= (1 << ADLAR); // Left justified output for 8bit mode
  ADCSRA |= (1 << ADSC);  // start conversion 1st time will take 25 cycles
}

uint8_t analog8(uint8_t channel)
{
  ADMUX  &= 0xF0;     //Clearing the last 4 bits of ADMUX
  ADMUX  |= channel;  //Selecting channel
  ADCSRA |= (1 << ADSC);
  while ( ADCSRA & ( 1 << ADSC ) );
  return ADCH;
}

void setup() {
    Serial.begin(9600);
    analog_init();

    asm("sbi 0x0A, 2"); // Set bit 2 in PORTD for PD2 output
    asm("sbi 0x0A, 3"); // Set bit 3 in PORTD for PD3 output
    asm("sbi 0x0A, 4"); // Set bit 4 in PORTD for PD4 output
    asm("sbi 0x0A, 5"); // Set bit 5 in PORTD for PD5 output
    asm("sbi 0x0A, 6"); // Set bit 6 in PORTD for PD6 output
    
    asm("cbi 0x0A, 7"); // Clear bit 7 in PORTD for PD7 input
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
  asm(" in r18, 0x09 "); // Load PIND into r18
  asm(" andi r18, 0x80 "); // Bit-mask the 7th bit
  asm(" cpi r18, 0x80 "); // Compare with 0x80
  asm(" brne click_on "); // If not zero, branch to click_on

  asm(" cbi 0x0B, 6 "); // Turn off Click LED
  asm(" rjmp click_handled ");
  
  asm(" click_on: ");
  asm(" sbi 0x0B, 6 "); // Turn on LED

  asm(" click_handled: ");




  // Y Axis handlling
  asm(" cpi r17, 128 ");   // <------ CHANGE 128 based on your joystick y-axis baseline ----->
  asm(" breq Y_Not_Moving ");

  asm(" cpi r17, 128 ");   // <------ CHANGE 128 based on your joystick y-axis baseline ----->
  asm(" brlo Y_Moving_Up ");

  asm(" cpi r17, 129 ");   // <------ CHANGE 129 based on your joystick y-axis baseline + 1 ----->
  asm(" brge Y_Moving_Down ");
  
  asm(" Y_Moving_Up: ");
  asm(" sbi 0x0B, 3 ");
  asm(" cbi 0x0B, 5 ");
  asm(" rjmp y_axis_handled ");

  asm(" Y_Not_Moving: ");
  asm(" cbi 0x0B, 3 ");
  asm(" cbi 0x0B, 5 ");
  asm(" rjmp y_axis_handled ");


  asm(" Y_Moving_Down: ");
  asm(" cbi 0x0B, 3 ");
  asm(" sbi 0x0B, 5 ");
  asm(" rjmp y_axis_handled ");
   
 
  asm(" y_axis_handled: ");




  //X Axis handling
  asm(" cpi r16, 126 ");  // <------ CHANGE 126 based on your joystick x-axis baseline ----->
  asm(" breq X_Not_Moving ");

  asm(" cpi r16, 126 ");  // <------ CHANGE 126 based on your joystick x-axis baseline ----->
  asm(" brlo X_Moving_Left ");

  asm(" cpi r16, 128 ");  // <------ CHANGE 128 based on your joystick x-axis baseline -----> 
  asm(" brge X_Moving_Right ");

  asm(" rjmp x_axis_handled ");
  
  asm(" X_Moving_Left: ");
  asm(" sbi 0x0B, 2 ");
  asm(" cbi 0x0B, 4 ");
  asm(" rjmp x_axis_handled ");

  asm(" X_Not_Moving: ");
  asm(" cbi 0x0B, 2 ");
  asm(" cbi 0x0B, 4 ");
  asm(" rjmp x_axis_handled ");


  asm(" X_Moving_Right: ");
  asm(" cbi 0x0B, 2 ");
  asm(" sbi 0x0B, 4 ");
  asm(" rjmp x_axis_handled ");
    
  asm(" x_axis_handled: ");

 
  // EVERYTHING ABOVE THIS LINE SHOULD BE ASSEMBLY
  
  // You can use this serial code for handy debugging.
    // It will let you observe the values coming out of your ADC.
  Serial.print("< ");
  Serial.print(x_axis);
  Serial.print(", ");
  Serial.print(y_axis);
  Serial.println(" >");
  delay(2);
  asm(" end: ");
  asm(" rjmp start ");
}
   
