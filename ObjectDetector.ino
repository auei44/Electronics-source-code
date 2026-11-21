
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

unsigned long lastBeep = 0;
unsigned long beepStart = 0;
bool beeping = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000);

  float distance = -1;

  if (duration > 0) {
    distance = duration * 0.0343 / 2.0;
  }

  unsigned long interval;

  if (distance < 0 || distance > 45.72) {
    noTone(buzzerPin);
    beeping = false;
    delay(60);
    return;
  }
  else if (distance > 30.48) {
    interval = 1000; // 12 to 18 inches
  }
  else if (distance > 15.24) {
    interval = 500;  // 6 to 12 inches
  }
  else {
    interval = 150;  // Under 6 inches
  }

  unsigned long now = millis();

  if (!beeping && now - lastBeep >= interval) {
    tone(buzzerPin, 2000);
    beepStart = now;
    lastBeep = now;
    beeping = true;
  }

  if (beeping && now - beepStart >= 50) {
    noTone(buzzerPin);
    beeping = false;
  }

  delay(60);
}
