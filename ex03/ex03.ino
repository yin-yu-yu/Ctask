const int ledPin = 4;

// 时间常数 (ms)
const unsigned long shortMs = 100;    // 短闪时长
const unsigned long longMs = 300;     // 长闪时长
const unsigned long gapMs = 100;      // 闪烁间隔
const unsigned long pauseMs = 1200;   // SOS完毕后停顿

// SOS信号序列：0=短闪，1=长闪
const int sosPattern[] = {0,0,0, 1,1,1, 0,0,0};
const int sosLength = 9;

unsigned long lastChangeTime = 0;
int patternIndex = 0;
bool ledOn = false;
unsigned long onDuration = 0;

void setup() {
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

void loop() {
	unsigned long currentMillis = millis();
	unsigned long elapsed = currentMillis - lastChangeTime;

	if (ledOn) {
		// LED亮着状态
		if (elapsed >= onDuration) {
			ledOn = false;
			lastChangeTime = currentMillis;
			digitalWrite(ledPin, LOW);
		}
	} else {
		// LED熄灭状态
		unsigned long waitTime;
		if (patternIndex >= sosLength) {
			// SOS完毕，需要较长停顿
			waitTime = pauseMs;
		} else {
			waitTime = gapMs;
		}

		if (elapsed >= waitTime) {
			if (patternIndex >= sosLength) {
				// 重新开始SOS
				patternIndex = 0;
			}

			// 点亮LED，根据当前模式决定时长
			ledOn = true;
			onDuration = (sosPattern[patternIndex] == 0) ? shortMs : longMs;
			lastChangeTime = currentMillis;
			digitalWrite(ledPin, HIGH);
			patternIndex++;
		}
	}
}
