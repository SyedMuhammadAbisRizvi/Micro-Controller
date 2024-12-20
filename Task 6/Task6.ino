enum State {
  d1d2Green_d3Red,
  d1d2Yellow_d3Red,
  d1d2Red_d3Green,
  d1d2Red_d3Yellow,
  pedestrianGreen,
  pedestrianRed
};

State _currentState = d1d2Green_d3Red;
unsigned long previousMillis = 0;

void loop() {
  unsigned long currentMillis = millis();
  
  if (redState == 1) {
    pedestrian(currentMillis);
  } else {
    trafficLight(currentMillis);
  }
}

void trafficLight(unsigned long currentMillis) {
  switch (_currentState) {
    case d1d2Green_d3Red:
      // d1, d2 Green; d3 Red
      digitalWrite(11, HIGH); // d1/d2 Green
      digitalWrite(9, LOW);  // d1/d2 Red
      digitalWrite(10, LOW); // d1/d2 Yellow
      digitalWrite(12, HIGH); // d3 Red
      if (currentMillis - previousMillis >= time) {
        previousMillis = currentMillis;
        _currentState = d1d2Yellow_d3Red;
      }
      break;

    case d1d2Yellow_d3Red:
      // d1, d2 Yellow; d3 Red
      digitalWrite(10, HIGH); // d1/d2 Yellow
      digitalWrite(11, LOW);  // d1/d2 Green
      digitalWrite(12, HIGH); // d3 Red
      if (currentMillis - previousMillis >= time / 2) {
        previousMillis = currentMillis;
        _currentState = d1d2Red_d3Green;
      }
      break;

    case d1d2Red_d3Green:
      // d1, d2 Red; d3 Green
      digitalWrite(9, HIGH);  // d1/d2 Red
      digitalWrite(11, LOW); // d1/d2 Green
      digitalWrite(12, LOW); // d3 Red
      digitalWrite(13, HIGH); // d3 Green
      if (currentMillis - previousMillis >= time) {
        previousMillis = currentMillis;
        _currentState = d1d2Red_d3Yellow;
      }
      break;

    case d1d2Red_d3Yellow:
      // d1, d2 Red; d3 Yellow
      digitalWrite(9, HIGH);  // d1/d2 Red
      digitalWrite(13, LOW); // d3 Green
      digitalWrite(14, HIGH); // d3 Yellow
      if (currentMillis - previousMillis >= time / 2) {
        previousMillis = currentMillis;
        _currentState = d1d2Green_d3Red;
      }
      break;
  }
}

void pedestrian(unsigned long currentMillis) {
  // Pedestrian light logic remains the same as before
}
