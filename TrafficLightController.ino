// TRAFFIC LIGHT CONTROLLER USING TIMER INTERRUPTS

// Road 1
const byte R1 = 3;
const byte Y1 = 4;
const byte G1 = 5;

// Road 2
const byte R2 = 6;
const byte Y2 = 7;
const byte G2 = 8;

// Pedestrian button
const byte BUTTON = 2;

// Variables shared with interrupts
volatile byte elapsedSeconds = 0;
volatile bool pedestrianRequest = false;

// Traffic states
byte state = 0;
bool pedestrianMode = false;

// ------------------------------------------------
// TIMER1 INTERRUPT
// Runs once every second
// ------------------------------------------------
ISR(TIMER1_COMPA_vect) {
  elapsedSeconds++;
}

// ------------------------------------------------
// BUTTON INTERRUPT
// Triggered when button is pressed
// ------------------------------------------------
void buttonISR() {
  pedestrianRequest = true;
}

// ------------------------------------------------
// Turn every LED OFF
// ------------------------------------------------
void allOff() {
  digitalWrite(R1, LOW);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, LOW);

  digitalWrite(R2, LOW);
  digitalWrite(Y2, LOW);
  digitalWrite(G2, LOW);
}

// ------------------------------------------------
// Set traffic-light state
// ------------------------------------------------
void setTrafficLights(byte s) {

  allOff();

  switch (s) {

    // Road 1 RED, Road 2 GREEN
    case 0:
      digitalWrite(R1, HIGH);
      digitalWrite(G2, HIGH);
      break;

    // Road 1 YELLOW, Road 2 RED
    case 1:
      digitalWrite(Y1, HIGH);
      digitalWrite(R2, HIGH);
      break;

    // Road 1 GREEN, Road 2 RED
    case 2:
      digitalWrite(G1, HIGH);
      digitalWrite(R2, HIGH);
      break;

    // Road 1 RED, Road 2 YELLOW
    case 3:
      digitalWrite(R1, HIGH);
      digitalWrite(Y2, HIGH);
      break;
  }
}

// ------------------------------------------------
// Pedestrian crossing mode
// ------------------------------------------------
void startPedestrianMode() {

  pedestrianMode = true;

  // Both roads RED
  allOff();
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  elapsedSeconds = 0;
}

// ------------------------------------------------
// SETUP
// ------------------------------------------------
void setup() {

  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);

  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);

  // Button uses Arduino's internal pull-up resistor
  pinMode(BUTTON, INPUT_PULLUP);

  // External interrupt on D2
  attachInterrupt(
    digitalPinToInterrupt(BUTTON),
    buttonISR,
    FALLING
  );

  // ----------------------------------------------
  // TIMER1 SETUP
  // ----------------------------------------------

  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;

  // CTC mode
  TCCR1B |= (1 << WGM12);

  // 1 second interrupt
  // 16 MHz / 1024 / 15625 = 1 Hz
  OCR1A = 15624;

  // Prescaler = 1024
  TCCR1B |= (1 << CS12);
  TCCR1B |= (1 << CS10);

  // Enable Timer1 Compare Match interrupt
  TIMSK1 |= (1 << OCIE1A);

  interrupts();

  // Start normal traffic
  setTrafficLights(0);
}

// ------------------------------------------------
// MAIN LOOP
// ------------------------------------------------
void loop() {

  // Check whether pedestrian button was pressed
  if (pedestrianRequest && !pedestrianMode) {

    noInterrupts();
    pedestrianRequest = false;
    elapsedSeconds = 0;
    interrupts();

    startPedestrianMode();
  }

  // ----------------------------------------------
  // PEDESTRIAN MODE
  // ----------------------------------------------
  if (pedestrianMode) {

    if (elapsedSeconds >= 3) {

      noInterrupts();
      elapsedSeconds = 0;
      interrupts();

      pedestrianMode = false;

      // Resume normal traffic
      setTrafficLights(state);
    }

    return;
  }

  // ----------------------------------------------
  // NORMAL TRAFFIC MODE
  // ----------------------------------------------

  // State 0 = 3 sec
  // State 1 = 1 sec
  // State 2 = 3 sec
  // State 3 = 1 sec

  byte requiredTime;

  if (state == 0 || state == 2) {
    requiredTime = 3;
  } else {
    requiredTime = 1;
  }

  if (elapsedSeconds >= requiredTime) {

    noInterrupts();
    elapsedSeconds = 0;
    interrupts();

    state++;

    if (state > 3) {
      state = 0;
    }

    setTrafficLights(state);
  }
}
