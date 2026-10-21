// Arduino Radar - HC-SR04 + Servo
// Baglantilar (semaya gore):
//   HC-SR04 Trig -> D8
//   HC-SR04 Echo -> D9
//   Servo sinyal (sari) -> D11
//   VCC'ler -> 5V, GND'ler -> GND

#include <Servo.h>

const int trigPin  = 8;
const int echoPin  = 9;
const int servoPin = 11;

Servo radarServo;

int mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long sure = pulseIn(echoPin, HIGH, 30000); // en fazla ~5 m bekle
  if (sure == 0) return 0;                   // yansima yok
  return sure * 0.034 / 2;                   // santimetre
}

void olcVeGonder(int aci) {
  radarServo.write(aci);
  delay(30);                 // servonun yerine oturmasi icin
  int mesafe = mesafeOlc();

  // Format: aci,mesafe.   (Processing bu formati okur)
  Serial.print(aci);
  Serial.print(",");
  Serial.print(mesafe);
  Serial.print(".");
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  radarServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  for (int a = 15; a <= 165; a++) olcVeGonder(a);
  for (int a = 165; a >= 15; a--) olcVeGonder(a);
}
