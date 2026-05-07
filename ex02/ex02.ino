const int ledPin = 4;
const unsigned long intervalMs = 500;  // 500ms toggle -> 1Hz blink

unsigned long previousMillis = 0;
bool ledState = false;

void setup() {
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

void loop() {
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= intervalMs) {
		previousMillis += intervalMs;
		ledState = !ledState;
		digitalWrite(ledPin, ledState ? HIGH : LOW);
	}
}
