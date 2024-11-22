enum State { green, yellow, red, pedestrianGreen, pedestrianRed }; // Traffic and pedestrian states
State _currentState = green;        // Initial traffic light state
State _targetState = pedestrianRed; // Initial pedestrian light state
bool pedestrianRequest = false;     // Flag for pedestrian button press
unsigned long lastMillis = 0;       // Tracks last state update for traffic lights
unsigned long pedestrianMillis = 0; // Tracks last state update for pedestrian lights
unsigned long interval = 10000;     // Default traffic green light duration (10 seconds)
unsigned long yellowInterval = 5000; // Yellow light duration (5 seconds)
unsigned long redInterval = 5000;   // Red light duration (5 seconds)
unsigned long pedestrianInterval = 5000; // Pedestrian green light duration
unsigned long pedestrianRedInterval = 2000; // Pedestrian red light duration

void setup() {
  Serial.begin(9600); // For debugging purposes
  // Traffic light pins
  pinMode(12, OUTPUT); // Pedestrian red light
  pinMode(11, OUTPUT); // Pedestrian green light
  pinMode(2, INPUT_PULLUP); // Pedestrian button (active LOW with internal pull-up)
  pinMode(6, OUTPUT); // Traffic red light
  pinMode(4, OUTPUT); // Traffic yellow light
  pinMode(3, OUTPUT); // Traffic green light

  // Attach interrupt for pedestrian button
  attachInterrupt(digitalPinToInterrupt(2), buttonPressed, FALLING);
}

void loop() {
  unsigned long currentMillis = millis();

  if (pedestrianRequest) {
    handlePedestrianLights(currentMillis); // Process pedestrian light sequence
  } else {
    handleTrafficLights(currentMillis); // Process traffic light sequence
  }
}

void handleTrafficLights(unsigned long currentMillis) {
  switch (_currentState) {
    case green:
      digitalWrite(3, HIGH);  // Traffic green light ON
      digitalWrite(12, HIGH); // Pedestrian red light ON
      if (currentMillis - lastMillis >= interval) {
        digitalWrite(3, LOW); // Traffic green light OFF
        _currentState = yellow; // Transition to yellow state
        lastMillis = currentMillis;
        interval = yellowInterval; // Yellow light duration (5 seconds)
      }
      break;

    case yellow:
      digitalWrite(4, HIGH); // Traffic yellow light ON
      if (currentMillis - lastMillis >= interval) {
        digitalWrite(4, LOW); // Traffic yellow light OFF
        _currentState = red; // Transition to red state
        lastMillis = currentMillis;
        interval = redInterval; // Red light duration (5 seconds)
      }
      break;

    case red:
      digitalWrite(6, HIGH); // Traffic red light ON
      if (currentMillis - lastMillis >= interval) {
        digitalWrite(6, LOW); // Traffic red light OFF
        _currentState = green; // Return to green state
        lastMillis = currentMillis;
        interval = 10000; // Green light duration (10 seconds)
      }
      break;
  }
}

void handlePedestrianLights(unsigned long currentMillis) {
  switch (_targetState) {
    case pedestrianGreen:
      digitalWrite(6, HIGH);  // Traffic red light ON
      digitalWrite(12, LOW);  // Pedestrian red light OFF
      digitalWrite(11, HIGH); // Pedestrian green light ON
      if (currentMillis - pedestrianMillis >= pedestrianInterval) {
        digitalWrite(11, LOW); // Pedestrian green light OFF
        _targetState = pedestrianRed; // Transition to pedestrian red
        pedestrianMillis = currentMillis;
        pedestrianInterval = pedestrianRedInterval; // Pedestrian red delay
      }
      break;

    case pedestrianRed:
      digitalWrite(12, HIGH); // Pedestrian red light ON
      pedestrianRequest = false; // Reset pedestrian request
      _currentState = red; // Resume traffic light at red
      pedestrianMillis = currentMillis;
      break;
  }
}

void buttonPressed() {
  // Debugging: Check if the button is pressed
  Serial.println("Button Pressed");

  // Only accept requests during red light
  if (_currentState == red && !pedestrianRequest) {
    pedestrianRequest = true; // Set pedestrian request
    _targetState = pedestrianGreen; // Switch to pedestrian green light
    pedestrianMillis = millis(); // Reset pedestrian timing
    pedestrianInterval = 5000; // Pedestrian green duration
    Serial.println("Pedestrian Green Requested");
  }
}
