#include <IRremote.h>

/* motor control scope */
int M1L = 0;
int M1R = 4;
int M2L = 5;
int M2R = 7;
int M3L = 8;
int M3R = 12;
int M4L = 3;
int M4R = 13;
int M1EN = 6;
int M2EN = 9;
int M3EN = 10;
int M4EN = 11;

/* Infrared Receiver Scope */
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup() {
  Serial.begin(9600);

  pinMode(M1L,OUTPUT);
  pinMode(M1R,OUTPUT);
  pinMode(M2L,OUTPUT);
  pinMode(M2R,OUTPUT);
  pinMode(M3L,OUTPUT);
  pinMode(M3R,OUTPUT);
  pinMode(M4L,OUTPUT);
  pinMode(M4R,OUTPUT);
  pinMode(M1EN,OUTPUT);
  pinMode(M2EN,OUTPUT);
  pinMode(M3EN,OUTPUT);
  pinMode(M4EN,OUTPUT);

  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
}

void loop() {
  // Receive Infrared remote code
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    translateIR();
    irrecv.resume(); // Receive the next value
  }
}

void translateIR(){
  ResetMotor();
  switch(results.value) {
    case 0xAB001CD: // Motor 1 Left
      digitalWrite(M1R, LOW);
      analogWrite(M1EN, 255);
      break;
    case 0xAB002CD: // Motor 1 Right
      digitalWrite(M1R, LOW);
      analogWrite(M1EN, 255);
      break;
    case 0xAB004CD: // Motor 2 Left
      digitalWrite(M2R, LOW);
      analogWrite(M2EN, 255);
      break;
    case 0xAB008CD: // Motor 2 Right
      digitalWrite(M2R, LOW);
      analogWrite(M2EN, 255);
      break;
    case 0xAB010CD: // Motor 3 Left
      digitalWrite(M3L, LOW);
      analogWrite(M3EN, 255);
      break;
    case 0xAB020CD: // Motor 3 Right
      digitalWrite(M3R, LOW);
      analogWrite(M3EN, 255);
      break;
    case 0xAB040CD: // Motor 4 Left
      digitalWrite(M4L, LOW);
      analogWrite(M4EN, 255);
      break;
    case 0xAB080CD: // Motor 4 Right
      digitalWrite(M4R, LOW);
      analogWrite(M4EN, 255);
      break;
  }
}

void ResetMotor(){
  digitalWrite(M1L, HIGH);
  digitalWrite(M1R, HIGH);
  digitalWrite(M2L, HIGH);
  digitalWrite(M2R, HIGH);
  digitalWrite(M3L, HIGH);
  digitalWrite(M3R, HIGH);
  digitalWrite(M4L, HIGH);
  digitalWrite(M4R, HIGH);
  digitalWrite(M1EN, LOW);
  digitalWrite(M2EN, LOW);
  digitalWrite(M3EN, LOW);
  digitalWrite(M4EN, LOW);
}
