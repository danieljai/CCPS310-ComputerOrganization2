void setup() {
  // put your setup code here, to run once:
  asm("sbi 0x04, 5");
  asm("cbi 0x0A, 7");
  asm("sbi 0x0B, 7");
}

void loop() {
  // put your main code here, to run repeatedly:
  asm("in r25, 0x09");      // load register from IO 0x09 to r25
  asm("andi r25, 0x80");    // masking bit 7
  asm("cpi r25, 0x80");     // compare with 0x80
  asm("brne len_on");       // if value is neg, that means its grounded and led goes on

  asm("cbi 0x05, 5");       // turn LED off
  asm("rjmp end");

  asm("len_on:");           // turn LED on
  asm("sbi 0x05, 5");

  asm("end:");
  delay(2);

}
