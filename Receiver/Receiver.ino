#include <IRremote.h>

/* motor control scope */
int M1L = 12;
int M1R = 11;
int M2L = 3;
int M2R = 2;
int M3L = 8;
int M3R = 7;
int M4L = 6;
int M4R = 5;
int M1EN = 13;
int M2EN = 4;
int M3EN = 10;
int M4EN = 9;

/* Motor Command Data */
uint8_t mCmdData = 0x0;

/* Motor Enable Data */
uint8_t mEnData[4];

uint8_t stateBtn;
uint8_t btnRepeat;
uint8_t foundBtn;

/* Infrared Receiver Scope */
int RECV_PIN = 14;
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

  for(uint8_t i = 0; i<4; i++)
    mEnData[i] = 0;
    
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
}

void loop() {
  ResetMotor();
  
  // Receive Infrared remote code
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    translateIR();
    irrecv.resume(); // Receive the next value
  }

  if(foundBtn==1){
    if(stateBtn != 0 && stateBtn != 255)
      /* update mCmdData */
      mCmdData = mCmdData | stateBtn;

      /* update mEnData */ // Edit motor speed here
      if(stateBtn == 1 || stateBtn == 2)
        ResetEnable();
        mEnData[0] = 255;
      if(stateBtn == 4 || stateBtn == 8)
        ResetEnable();
        mEnData[1] = 255;
      if(stateBtn == 16 || stateBtn == 32)
        ResetEnable();
        mEnData[2] = 255;
      if(stateBtn == 64 || stateBtn == 128)
        ResetEnable();
        mEnData[3] = 255;
  } else {
    ResetMotor();
    ResetEnable();
  }
  
  /* Send Command To Motor */
  digitalWrite(M1L, (mCmdData & (1 << 0)) >> 0);
  digitalWrite(M1R, (mCmdData & (1 << 1)) >> 1);
  digitalWrite(M2L, (mCmdData & (1 << 2)) >> 2);
  digitalWrite(M2R, (mCmdData & (1 << 3)) >> 3);
  digitalWrite(M3L, (mCmdData & (1 << 4)) >> 4);
  digitalWrite(M3R, (mCmdData & (1 << 5)) >> 5);
  digitalWrite(M4L, (mCmdData & (1 << 6)) >> 6);
  digitalWrite(M4R, (mCmdData & (1 << 7)) >> 7);

  /* Send Enable To Motor */
  analogWrite(M1EN, mEnData[0]);
  analogWrite(M2EN, mEnData[1]);
  analogWrite(M3EN, mEnData[2]);
  analogWrite(M4EN, mEnData[3]);

  foundBtn = 0;
  delay(180);
}

void translateIR(){
  uint8_t isRepeat = 0;
  uint8_t newBtn = 0;
  
  switch(results.value) {
    case 0xAB001CD: // Motor 1 Left
      //mCmdData = mCmdData | 0x01;
      //mEnData[0] = 255;
      newBtn = 1;
      break;
    case 0xAB002CD: // Motor 1 Right
      //mCmdData = mCmdData | 0x02;
      //mEnData[0] = 255;
      newBtn = 2;
      break;
    case 0xAB004CD: // Motor 2 Left
      //mCmdData = mCmdData | 0x04;
      //mEnData[1] = 255;
      newBtn = 4;
      break;
    case 0xAB008CD: // Motor 2 Right
      //mCmdData = mCmdData | 0x08;
      //mEnData[1] = 255;
      newBtn = 8;
      break;
    case 0xAB010CD: // Motor 3 Left
      //mCmdData = mCmdData | 0x10;
      //mEnData[2] = 255;
      newBtn = 16;
      break;
    case 0xAB020CD: // Motor 3 Right
      //mCmdData = mCmdData | 0x20;
      //mEnData[2] = 255;
      newBtn = 32;
      break;
    case 0xAB040CD: // Motor 4 Left
      //mCmdData = mCmdData | 0x40;
      //mEnData[3] = 255;
      newBtn = 64;
      break;
    case 0xAB080CD: // Motor 4 Right
      //mCmdData = mCmdData | 0x80;
      //mEnData[3] = 255;
      newBtn = 128;
      break;
    case 0xFFFFFFFF:
      isRepeat = 1;
      break;
    default:
      Serial.println("Unused Btn");
      newBtn = 255;
      break;
  }

  if(newBtn != 0){
    stateBtn = newBtn;
    btnRepeat = stateBtn;
  } else {
    if(isRepeat)
      stateBtn = btnRepeat;
  }

  if(stateBtn != 0)
    foundBtn = 1;
}

void ResetMotor(){
  mCmdData = 0x0;
}

void ResetEnable(){
  for(uint8_t i = 0; i<4; i++)
    mEnData[i] = 0;
}
