#include <IRremote.h>
/* constant */
const int numAI = 4;

/* motor control scope */
int M1L = 12;
int M1R = 4;
int M2L = 8;
int M2R = 7;
//int M3L = 8;
//int M3R = 7;
//int M4L = 8;
//int M4R = 7;
int M1EN = 11;
int M2EN = 3;
//int M3EN = 6;
//int M4EN = 5;

uint8_t MSpeed[numAI];

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
//  pinMode(M3L,OUTPUT);
//  pinMode(M3R,OUTPUT);
//  pinMode(M4L,OUTPUT);
//  pinMode(M4R,OUTPUT);
  pinMode(M1EN,OUTPUT);
  pinMode(M2EN,OUTPUT);
//  pinMode(M3EN,OUTPUT);
//  pinMode(M4EN,OUTPUT);

  for(uint8_t i = 0; i < numAI; i++)
    MSpeed[i] = 0;
    
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
}

void loop() {
  // read motor speed settings
  //for(uint8_t i = 0; i < numAI; i++){
    int val = analogRead(0);
    MSpeed[0] = map(val, 0, 1023, 0, 255);
  //}
  
  // Receive Infrared remote code
  //if (irrecv.decode(&results)) {
  //  Serial.println(results.value, HEX);
  //  if (results.value == 0xFFFFFFFF) results.value = key_value;
    translateIR();
  //  key_value = results.value;
  //  irrecv.resume(); // Receive the next value
  //}
}

void translateIR(){
  ResetMotor();
//  switch(results.value) {
//    case 0xAB7AA7: // Motor 1 Left
      digitalWrite(M1R, LOW);
      analogWrite(M1EN, 255);
//      break;
//    case 0xAB7654: // Motor 1 Right
//      digitalWrite(M1R, LOW);
//      analogWrite(M1EN, MSpeed[0]);
//      break;
//    case 0xAB667A: // Motor 2 Left
      digitalWrite(M2R, LOW);
      analogWrite(M2EN, 255);
//      if (key_value != results.value)
//      break;
//    case 0xAB5AA5: // Motor 2 Right
//      digitalWrite(M2R, LOW);
//      analogWrite(M2EN, MSpeed[0]);
//      if (key_value != results.value)
//        Serial.print("M2 Right");
//      break;
//    case 0xAB777F: // Motor 3 Left
//      digitalWrite(M3L, LOW);
//      analogWrite(M3EN, MSpeed[0]);
//      break;
//    case 0xAB12B7: // Motor 3 Right
//      digitalWrite(M3R, LOW);
//      analogWrite(M3EN, MSpeed[0]);
//      break;
//    case 0xAB2406: // Motor 4 Left
//      digitalWrite(M4L, LOW);
//      analogWrite(M4EN, MSpeed[0]);
//      break;
//    case 0xAB8F7B: // Motor 4 Right
//      digitalWrite(M4R, LOW);
//      analogWrite(M4EN, MSpeed[0]);
//      break;
//  }
}

void ResetMotor(){
  digitalWrite(M1L, HIGH);
  digitalWrite(M1R, HIGH);
  digitalWrite(M2L, HIGH);
  digitalWrite(M2R, HIGH);
//  digitalWrite(M3L, HIGH);
//  digitalWrite(M3R, HIGH);
//  digitalWrite(M4L, HIGH);
//  digitalWrite(M4R, HIGH);
  //digitalWrite(M1EN, LOW);
  //digitalWrite(M2EN, LOW);
  //digitalWrite(M3EN, LOW);
  //digitalWrite(M4EN, LOW);
}
