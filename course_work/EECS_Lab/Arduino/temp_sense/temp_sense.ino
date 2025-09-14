float temp;

void setup()
{
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  temp = analogRead(A0);
  temp = temp*0.48828125;
  Serial.print("TEMPERATURE: ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  if (temp > 27)
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
  }
  else
  {
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
  }
  delay(1000);
}