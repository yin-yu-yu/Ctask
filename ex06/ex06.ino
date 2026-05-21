const int ledA = 18;
const int ledB = 19;

const unsigned long stepDelayMs = 10;

void setup() {
	ledcAttach(ledA, 5000, 8);
	ledcAttach(ledB, 5000, 8);

	ledcWrite(ledA, 0);
	ledcWrite(ledB, 255);
}

void loop() {
	for (int duty = 0; duty <= 255; duty++) {
		ledcWrite(ledA, duty);
		ledcWrite(ledB, 255 - duty);
		delay(stepDelayMs);
	}

	for (int duty = 255; duty >= 0; duty--) {
		ledcWrite(ledA, duty);
		ledcWrite(ledB, 255 - duty);
		delay(stepDelayMs);
	}
}