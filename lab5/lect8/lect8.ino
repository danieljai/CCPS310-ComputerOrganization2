void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x_axis = analogRead(A0);
  int y_axis = analogRead(A1);

  x_axis = map(x_axis, 0, 1023, 0, 255);
  y_axis = map(y_axis, 0, 1023, 0, 255);

  Serial.print(x_axis);
  Serial.print(", ");
  Serial.println(y_axis);
  delay(2);
}
