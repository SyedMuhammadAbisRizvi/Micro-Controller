enum Status { green, yellow, red, pgreen, pred };  // Traffic light states
Status status = green;  // Initial state is green
int set = 0;  // Flag to control state transition
unsigned long lastMillis = 0;  // Variable to store the last time an event was triggered
unsigned long greenInterval = 10000;  // Green light duration (10 seconds)
unsigned long yellowInterval = 3000; // Yellow light duration (3 seconds)
unsigned long redInterval = 10000;   // Red light duration (10 seconds)
unsigned long additionalTime = 3200; // Additional time for the button press scenario
unsigned long buttonPressTime = 0;   // Timer for button press scenario
bool buttonPressed = false;          // Flag to check if the button was pressed

void setup() {
  pinMode(12, OUTPUT);  // Green light
  pinMode(11, OUTPUT);  // Yellow light
  pinMode(10, INPUT);   // Input for button/sensor
  pinMode(6, OUTPUT);   // Red light
  pinMode(4, OUTPUT);   // Yellow warning light
  pinMode(2, OUTPUT);   // Additional light for green
}

void loop() {
  int change = digitalRead(10);  // Read the button/sensor input
  unsigned long currentMillis = millis();  // Get the current time

  if (change == HIGH) {
    if (!buttonPressed) {  // Ensure the button press is only handled once
      buttonPressed = true;  // Set the flag to indicate button press
      buttonPressTime = currentMillis;  // Store the time of button press
      // Start the red-yellow transition after 3200ms delay
    }

    if (buttonPressed && (currentMillis - buttonPressTime >= additionalTime)) {
      // After 3200ms, switch to red and yellow lights
      digitalWrite(6, HIGH);  // Turn on the red light
      digitalWrite(12, LOW);  // Turn off green
      digitalWrite(11, HIGH); // Turn on yellow
      if (currentMillis - lastMillis >= 10000) {
        // Keep yellow light on for 10 seconds, then switch to green
        lastMillis = currentMillis;
        digitalWrite(11, LOW);  // Turn off yellow
        digitalWrite(12, HIGH); // Turn on green
        buttonPressed = false;  // Reset the button press flag
      }
    }
  } else if (change == LOW) {
    switch (status) {
      case green:
        digitalWrite(12, HIGH);  // Green light on
        digitalWrite(2, HIGH);   // Additional light for green on
        if (currentMillis - lastMillis >= greenInterval) {
          lastMillis = currentMillis;  // Store the time of the event
          digitalWrite(2, LOW);  // Turn off additional green light
          status = yellow;
          set = 1;  // Flag for transitioning to red
        }
        break;

      case yellow:
        digitalWrite(12, HIGH);  // Keep green on
        digitalWrite(4, HIGH);   // Turn on yellow warning light
        if (currentMillis - lastMillis >= yellowInterval) {
          lastMillis = currentMillis;  // Store the time of the event
          digitalWrite(4, LOW);    // Turn off yellow warning light
          if (set == 1) {
            status = red;
          } 
          if (set == 0) {
            status = green;
          }
        }
        break;

      case red:
        digitalWrite(12, HIGH);  // Keep green on
        digitalWrite(6, HIGH);   // Turn on red light
        if (currentMillis - lastMillis >= redInterval) {
          lastMillis = currentMillis;  // Store the time of the event
          digitalWrite(6, LOW);    // Turn off red light
          status = yellow;
          set = 0;  // Reset flag for next cycle
        }
        break;
    }
  }
}
