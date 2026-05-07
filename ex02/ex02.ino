const int ledPin = 4;
const unsigned long intervalMs = 500;  // 500ms toggle -> 1Hz blink

void setup() {
	pinMode(ledPin, OUTPUT);
}

void loop() {
	unsigned long currentMillis = millis();
	bool ledState = (currentMillis / intervalMs) % 2 == 0;
	digitalWrite(ledPin, ledState ? HIGH : LOW);
}
