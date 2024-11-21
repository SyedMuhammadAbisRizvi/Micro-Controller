enum Status { green, yellow, red };
Status status = green;
int set;

void setup() {
  pinMode(6, OUTPUT); // Green LED
  pinMode(4, OUTPUT); // Yellow LED
  pinMode(2, OUTPUT); // Red LED
}

void loop() {
  static unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  switch (status) {
    case green:
      if (currentMillis - lastMillis >= 3000) {
        lastMillis = currentMillis;
        digitalWrite(6, LOW); // Turn off green light
        digitalWrite(4, HIGH); // Turn on yellow light
        status = yellow;
        set = 1;
      } else {
        digitalWrite(6, HIGH); // Keep green light on
      }
      break;

    case yellow:
      if (currentMillis - lastMillis >= 1000) {
        lastMillis = currentMillis;
        digitalWrite(4, LOW); // Turn off yellow light
        if (set == 1) {
          digitalWrite(2, HIGH); // Turn on red light
          status = red;
        } else {
          digitalWrite(6, HIGH); // Turn on green light
          status = green;
        }
      } else {
        digitalWrite(4, HIGH); // Keep yellow light on
      }
      break;

    case red:
      if (currentMillis - lastMillis >= 3000) {
        lastMillis = currentMillis;
        digitalWrite(2, LOW); // Turn off red light
        digitalWrite(4, HIGH); // Turn on yellow light
        status = yellow;
        set = 0;
      } else {
        digitalWrite(2, HIGH); // Keep red light on
      }
      break;
  }
}
