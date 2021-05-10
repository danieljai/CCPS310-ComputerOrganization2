// Lab 4
// Andy Lee - 500163559

void setup() {
  // initialize 7-segment.

  asm("sbi 0x0A, 0");
  asm("sbi 0x0A, 1");
  asm("sbi 0x0A, 2");
  asm("sbi 0x0A, 3");
  asm("sbi 0x0A, 4");
  asm("sbi 0x0A, 5");
  asm("sbi 0x0A, 6");
  asm("rjmp start");
}

// the loop function runs over and over again forever
void loop() {
  asm("start:");
  // ONE
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  delay(1000);
  asm("call clearnum");

  // TWO
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,4");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");

  // THREE
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");
  
  // FOUR
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,5");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");
  
  // FIVE
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,5");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");

  
  // SIX
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,4");
  asm("sbi 0x0B,5");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");
  
  // SEVEN
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  delay(1000);
  asm("call clearnum");
  
  // EIGHT
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,4");
  asm("sbi 0x0B,5");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");
  
  // NINE
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,5");
  asm("sbi 0x0B,6");
  delay(1000);
  asm("call clearnum");

  // ZERO
  asm("sbi 0x0B,0");
  asm("sbi 0x0B,1");
  asm("sbi 0x0B,2");
  asm("sbi 0x0B,3");
  asm("sbi 0x0B,4");
  asm("sbi 0x0B,5");
  delay(1000);
  asm("call clearnum");
  
  asm("rjmp start");

  // clearing subroutine.
  asm("clearnum:");
  asm("cbi 0x0B,0");
  asm("cbi 0x0B,1");
  asm("cbi 0x0B,2");
  asm("cbi 0x0B,3");
  asm("cbi 0x0B,4");
  asm("cbi 0x0B,5");
  asm("cbi 0x0B,6");
  delay(1000);
  asm("ret");
}
