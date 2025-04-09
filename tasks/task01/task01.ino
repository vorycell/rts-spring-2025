struct Signal {
  uint8_t channel;
  uint32_t delayTime;
  volatile uint32_t lastUpdate;
  bool status;
};

Signal signals[] = {
  {3,  10000, 0, LOW},
  {5,   1000, 0, LOW},
  {6,    500, 0, LOW},
  {9,    100, 0, LOW},
  {10,    50, 0, LOW}
};
constexpr uint8_t totalSignals = sizeof(signals) / sizeof(Signal);

void setup() {
  for (uint8_t idx = 0; idx < totalSignals; idx++) {
    pinMode(signals[idx].channel, OUTPUT);
  }
}

void loop() {
  uint32_t timeNow = micros();

  for (uint8_t idx = 0; idx < totalSignals; idx++) {
    if (timeNow - signals[idx].lastUpdate >= signals[idx].delayTime) {
      signals[idx].lastUpdate = timeNow;
      signals[idx].status = !signals[idx].status;
      digitalWrite(signals[idx].channel, signals[idx].status);
    }
  }
}