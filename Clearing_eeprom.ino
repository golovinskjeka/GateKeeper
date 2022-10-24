#include <EEPROM.h>
void setup() {
  for (int i=0; i <= 1023; i++){
     EEPROM.put(i, 0); 
   }
}

void loop() {
  // put your main code here, to run repeatedly:

}
