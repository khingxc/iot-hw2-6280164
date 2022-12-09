const int pBuzzerPin = 7;
const int resetButtonPin = 3;
int resetButtonStatus = 0;
int prevSensorValue = 0;
unsigned long prevMillis = 0;
int toAlarm = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pBuzzerPin, OUTPUT);
  pinMode(resetButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  int sensorValue = analogRead(A0);
  int buttonVal = digitalRead(resetButtonPin);
  bool falling_edge = resetButtonStatus == 0 && buttonVal == 1;
  if (prevSensorValue - sensorValue >= 10 && sensorValue <= 15) {
    Serial.println("DETECTED STH");
    if (prevMillis != 0 && currentMillis - prevMillis <= 2000) {
      toAlarm = 1;
    }
    prevMillis = currentMillis;
  }
  if (toAlarm) {
    Serial.println("!!!");
    tone(pBuzzerPin, 1568, 0);
  }
  if (falling_edge) {
    Serial.println("RESET CLICK");
    toAlarm = 0;
    noTone(pBuzzerPin);
  }
//  Serial.println(buttonVal);
//  Serial.println(falling_edge);
//  Serial.println(toAlarm);
//  Serial.println("***********");
  resetButtonStatus = buttonVal;
  prevSensorValue = sensorValue;
}
