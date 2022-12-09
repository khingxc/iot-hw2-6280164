int melodiesPins[] = {2,3,4,5};
int pBuzzerPin = 8;
int pinsNum = 4;
int buttons_states[] = {0, 0, 0, 0};
const int melodies[] = {262, 294, 330, 392};
unsigned long prevMillis = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < pinsNum; i++) {
    pinMode(melodiesPins[i], INPUT_PULLUP);
  }
  pinMode(pBuzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //   put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  for (int i = 0; i < pinsNum; i++) {
    int buttonVal = digitalRead(melodiesPins[i]);
    bool falling_edge = buttons_states[i] == 0 && buttonVal == 1;
    if (falling_edge) {
      prevMillis = currentMillis;
      tone(pBuzzerPin, melodies[i], 0);
    } else if (currentMillis - prevMillis > 500) {
      noTone(pBuzzerPin);
    }
    buttons_states[i] = buttonVal;
  }
}
