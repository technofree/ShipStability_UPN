#include <IRremote.h>
#include <Keypad.h>

/* constant */
const uint8_t ROWS = 4;
const uint8_t COLS = 3;

/* infrared scope */
IRsend irsend;

/* keypad scope */
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

uint8_t rowPins[ROWS] = {24, 34, 32, 28};
uint8_t colPins[COLS] = {26, 22, 30};
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

uint16_t keyState = 0;

void setup() {
  Serial.begin(9600);
  kpd.addEventListener(keypadEvent);
}

void loop() {
  readKeypad();
}

void readKeypad(){
  char key = kpd.getKey();

  if(key) {
    Serial.println(key);
  }
  
  if(keyState == 1) Serial.println(179306957, HEX);
  if(keyState == 2) Serial.println(179307213, HEX);
  if(keyState == 4) Serial.println(179307725, HEX);
  if(keyState == 8) Serial.println(179308749, HEX);
  if(keyState == 16) Serial.println(179310797, HEX);
  if(keyState == 32) Serial.println(179314893, HEX);
  if(keyState == 64) Serial.println(179323085, HEX);
  if(keyState == 128) Serial.println(179339469, HEX);
  if(keyState == 256) Serial.println(179372237, HEX);
  if(keyState == 512) Serial.println(179437773, HEX);
  if(keyState == 1024) Serial.println(179568845, HEX);
  if(keyState == 2048) Serial.println(179830989, HEX);
}

void keypadEvent(KeypadEvent key){
  switch(kpd.getState()){
    case PRESSED:
    case HOLD:
        if(key == '1') keyState = 1;
        if(key == '2') keyState = 2;
        if(key == '3') keyState = 4;
        if(key == '4') keyState = 8;
        if(key == '5') keyState = 16;
        if(key == '6') keyState = 32;
        if(key == '7') keyState = 64;
        if(key == '8') keyState = 128;
        if(key == '9') keyState = 256;
        if(key == '*') keyState = 512;
        if(key == '0') keyState = 1024;
        if(key == '#') keyState = 2048;
        break;
        
    case RELEASED:
        keyState = 0;
        break;
  }
}
