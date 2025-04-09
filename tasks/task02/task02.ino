volatile uint32_t sumIntervals = 0;
volatile uint32_t sumSquaredIntervals = 0;
volatile uint32_t lastTimestamp = 0;
volatile unsigned int measurementCount = 0;
const unsigned int maxSamples = 42;

void setup() {
  Serial.begin(115200);
  pinMode(21, INPUT);
  attachInterrupt(digitalPinToInterrupt(21), onPinChange, CHANGE);
}

void onPinChange() {
  unsigned long currentTime = micros();

  if (lastTimestamp) {
    unsigned long delta = currentTime - lastTimestamp;

    sumIntervals += delta;
    sumSquaredIntervals += delta * delta;
    measurementCount++;
  }

  lastTimestamp = currentTime;
}

void loop() {
  if (measurementCount >= maxSamples) {
    noInterrupts();
    uint32_t intervalSumSnapshot = sumIntervals;
    uint32_t squaredIntervalSumSnapshot = sumSquaredIntervals;
    unsigned int sampleSnapshot = measurementCount;
    sumIntervals = 0;
    sumSquaredIntervals = 0;
    measurementCount = 0;
    interrupts();

    uint32_t avgInterval = intervalSumSnapshot / sampleSnapshot;
    uint32_t variance = (squaredIntervalSumSnapshot / sampleSnapshot) - (avgInterval * avgInterval);
    uint32_t stdDeviation = sqrt(variance);

    Serial.print("Mean (us): ");
    Serial.print(avgInterval);
    Serial.print(", Accumulated Squared Interval (us): ");
    Serial.print(squaredIntervalSumSnapshot);
    Serial.print(", Sample Count: ");
    Serial.print(sampleSnapshot);
    Serial.print(", Mean^2 (us): ");
    Serial.print(avgInterval * avgInterval);
    Serial.print(", Variance (us): ");
    Serial.print(variance);
    Serial.print(", Standard Deviation (us): ");
    Serial.print(stdDeviation);
    Serial.println("");
  }
}
