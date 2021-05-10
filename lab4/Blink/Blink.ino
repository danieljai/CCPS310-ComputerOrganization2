

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  // pinMode(LED_BUILTIN, OUTPUT);
  asm("sbi 0x0A, 0");
  asm("rjmp start");
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  asm("start:");
  asm("sbi 0x0B,0");
  delay(200);                       // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  asm("cbi 0x0B,0");
  delay(200);                       // wait for a second
  asm("rjmp start");
}
