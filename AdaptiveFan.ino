
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

#define ENA 5
#define IN1 18
#define IN2 19

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  Serial.println("Fan Start");
}

void loop() {
  float temp = dht.readTemperature(true);

  if (isnan(temp)) {
    Serial.println("Sensor reading failed");
    analogWrite(ENA, 0);
    delay(2000);
    return;
  }

  int speed = 0;

  if (temp < 70) {
    speed = 0;
  } else if (temp < 80) {
    speed = 180;
  } else if (temp < 85) {
    speed = 220;
  } else {
    speed = 255;
  }

  analogWrite(ENA, speed);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" F | Fan speed: ");
  Serial.println(speed);

  delay(2000);
}
