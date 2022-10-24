#include <SPI.h>
 #include <MFRC522.h> 
 #include <EEPROM.h>
 #define SS_PIN 10
 #define RST_PIN 9
 MFRC522 mfrc522(SS_PIN, RST_PIN);
 int numcard = 0;
 unsigned long uidDec = 0;
 unsigned long uidDecTemp; 
 int addr = 0;
 unsigned int value;
 int count = 0;
 int bottom = 0;
 int red = 1;
 int blue = 0;
 int green = 1;
 unsigned long waiting = 0;
 int admin = 29638;
void setup() {
Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  SPI.begin(); 
  mfrc522.PCD_Init();
  digitalWrite(4,1);
  digitalWrite(5,blue);
  digitalWrite(6,green);
  digitalWrite(7,red);
  EEPROM.put(500, numcard);
}

void loop() {
card_detecting();
bottom = digitalRead(8);
if (uidDec != 0){
  if (uidDec == admin){
    if (bottom == 1){
    uidDec = 0;
    delay(1000);
    addcard();
    }
    if (uidDec != 0){
    opening();
    }
     }
  else {
    scan();
  }
}
Serial.println(uidDec);
uidDec = 0;
  digitalWrite(5,blue);
  digitalWrite(6,green);
  digitalWrite(7,red);
}

void addcard(){
  Serial.println("Addcard");
  red = 0;
  green = 0;
  blue = 1;
  digitalWrite(5,blue);
  digitalWrite(6,green);
  digitalWrite(7,red);
  waiting = millis;
  while (millis - waiting <= 10000){
    card_detecting();
    if (uidDec != 0){
      if(uidDec == admin){
        red = 1;
        green = 1;
        blue = 0;
        uidDec = 0;
        delay(1000);
        return;
      }
      for(int addr = 0; addr <= 40; addr = addr + 2){
    EEPROM.get(addr, value);
    if (uidDec == value){
      red = 1;
      green = 1;
      blue = 0;
      uidDec = 0;
      delay(1000);
      return;
    }
    }
    EEPROM.put(numcard, uidDec);
    numcard = numcard + 2;
    EEPROM.put(500, numcard);
    uidDec = 0;
  red = 0;
  green = 1;
  blue = 0;
  digitalWrite(5,blue);
  digitalWrite(6,green);
  digitalWrite(7,red);
  delay(1000);
  red = 1;
  green = 1;
  blue = 0;
    return;
    }
  }
}
void sound(){
  Serial.println("Sound");
  for (int i=0; i <= 33; i++){
  digitalWrite(6,1);
  digitalWrite(7,0);
  digitalWrite(5,1);
  delay(200);
  digitalWrite(7,1);
  delay(100); 
}
}
void scan(){ 
  Serial.println("Scan");
  
  for(int addr = 0; addr <= 40; addr = addr + 2){
    EEPROM.get(addr, value);
    if (uidDec == value){
      opening();
      return;
    }
    }
    count = count + 1;
  digitalWrite(6,1);
  digitalWrite(7,0);
  digitalWrite(5,1);
  delay(1000);
  digitalWrite(7,1);
   if (count >= 3){
    sound();
    count = 0; 
   }
   delay(500);
}
void card_detecting(){
  
 if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
    return;
    }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
    return;
    }
  uidDec = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
  uidDec = uidDec/100000;
}

void opening(){
  Serial.println("Opening");
  count = 0;
  digitalWrite(4,0);
  for (int i=0; i <= 2; i++){
  digitalWrite(6,0);
  digitalWrite(7,1);
  digitalWrite(5,1);
  delay(200);
  digitalWrite(6,1);
  delay(100); 
}
  red = 1;
  green = 0;
  blue = 1;
  digitalWrite(5,blue);
  digitalWrite(6,green);
  digitalWrite(7,red);
  delay(2000);
  digitalWrite(4,1);
  red = 1;
  green = 1;
  blue = 0;
}

