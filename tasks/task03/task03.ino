const int outputPins[] = {3, 5, 6, 9, 10};
const unsigned long toggleDelays[] = {10000, 1000, 500, 100, 50};
volatile bool pinStates[] = {LOW, LOW, LOW, LOW, LOW};

unsigned long lastToggleTime0;
unsigned long lastToggleTime1;
unsigned long lastToggleTime2;
unsigned long lastToggleTime3;
unsigned long lastToggleTime4;

void initializeOutputs() {
  for (int i = 0; i < 5; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  unsigned long currentMicros = micros();
  lastToggleTime0 = currentMicros;
  lastToggleTime1 = currentMicros;
  lastToggleTime2 = currentMicros;
  lastToggleTime3 = currentMicros;
  lastToggleTime4 = currentMicros;
}

void handleToggles() {
  unsigned long currentMicros = micros();

  if (currentMicros - lastToggleTime4 >= toggleDelays[4]) {
    PORTB ^= B00000100;
    lastToggleTime4 = currentMicros;
  }
  if (currentMicros - lastToggleTime3 >= toggleDelays[3]) {
    PORTB ^= B00000010;
    lastToggleTime3 = currentMicros;
  }
  if (currentMicros - lastToggleTime2 >= toggleDelays[2]) {
    PORTD ^= B01000000;
    lastToggleTime2 = currentMicros;
  }
  if (currentMicros - lastToggleTime1 >= toggleDelays[1]) {
    PORTD ^= B00100000;
    lastToggleTime1 = currentMicros;
  }
  if (currentMicros - lastToggleTime0 >= toggleDelays[0]) {
    PORTD ^= B00001000;
    lastToggleTime0 = currentMicros;
  }
}

void setup() {
  initializeOutputs();
}

void loop() {
  handleToggles();
}
