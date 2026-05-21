const int ledPin = 2;
const int touchPin = 4;

const unsigned long debounceMs = 80;
const unsigned long stepDelayMs[] = {18, 8, 3};
const uint8_t stepSize[] = {1, 3, 8};
const int speedCount = 3;

uint16_t touchBaseline = 0;
uint16_t touchThreshold = 0;

bool lastRawTouch = false;
bool stableTouch = false;
unsigned long lastDebounceTime = 0;

int speedLevel = 0;
int duty = 0;
bool increasing = true;
unsigned long lastStepTime = 0;

bool readTouchPressed() {
	return touchRead(touchPin) < touchThreshold;
}

void setup() {
	Serial.begin(115200);
	ledcAttach(ledPin, 5000, 8);
	ledcWrite(ledPin, 0);

	delay(200);

	uint32_t total = 0;
	for (int i = 0; i < 32; i++) {
		total += touchRead(touchPin);
		delay(5);
	}

	touchBaseline = total / 32;
	touchThreshold = touchBaseline * 3 / 4;
	if (touchThreshold < 10) {
		touchThreshold = 10;
	}

	lastRawTouch = readTouchPressed();
	stableTouch = lastRawTouch;

	Serial.printf("touch baseline=%u threshold=%u\n", touchBaseline, touchThreshold);
}

void loop() {
	unsigned long now = millis();
	bool rawTouch = readTouchPressed();

	if (rawTouch != lastRawTouch) {
		lastDebounceTime = now;
		lastRawTouch = rawTouch;
	}

	if ((now - lastDebounceTime) >= debounceMs && rawTouch != stableTouch) {
		stableTouch = rawTouch;

		if (stableTouch) {
			speedLevel = (speedLevel + 1) % speedCount;
			Serial.printf("speed level=%d\n", speedLevel + 1);
		}
	}

	if (now - lastStepTime < stepDelayMs[speedLevel]) {
		return;
	}
	lastStepTime = now;

	int step = stepSize[speedLevel];

	if (increasing) {
		duty += step;
		if (duty >= 255) {
			duty = 255;
			increasing = false;
		}
	} else {
		duty -= step;
		if (duty <= 0) {
			duty = 0;
			increasing = true;
		}
	}

	ledcWrite(ledPin, duty);
}