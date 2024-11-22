// Define the state of the traffic light
enum Status { green, yellow, red };
Status status = green;

const int T20 = 20;  // Each "time event" is 20 milliseconds

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int timeEvent = 0; // This will count the number of T20 events

void setup() {
  pinMode(6, OUTPUT);  // Green LED
  pinMode(4, OUTPUT);  // Yellow LED
  pinMode(2, OUTPUT);  // Red LED
}

void loop() {
  currentMillis = millis();  // Get the current time

  // Count the number of T20 events
  if (currentMillis - previousMillis >= T20) {
    previousMillis = currentMillis;
    timeEvent++;
  }

  switch (status) {
    case green:
      // Green light should stay on for 3 seconds (150 T20 events)
      if (timeEvent >= 150) {
        digitalWrite(6, LOW);  // Turn off green light
        digitalWrite(4, HIGH); // Turn on yellow light
        status = yellow; // Transition to yellow
        timeEvent = 0;  // Reset time event counter
      } else {
        digitalWrite(6, HIGH); // Keep green light on
      }
      break;

    case yellow:
      // Yellow light should stay on for 1 second (50 T20 events)
      if (timeEvent >= 50) {
        digitalWrite(4, LOW); // Turn off yellow light
        digitalWrite(2, HIGH); // Turn on red light
        status = red; // Transition to red
        timeEvent = 0;  // Reset time event counter
      } else {
        digitalWrite(4, HIGH); // Keep yellow light on
      }
      break;

    case red:
      // Red light should stay on for 3 seconds (150 T20 events)
      if (timeEvent >= 150) {
        digitalWrite(2, LOW); // Turn off red light
        digitalWrite(4, HIGH); // Turn on yellow light
        status = yellow; // Transition to yellow
        timeEvent = 0;  // Reset time event counter
      } else {
        digitalWrite(2, HIGH); // Keep red light on
      }
      break;
  }
}
