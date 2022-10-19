/* 
  Exemplo: 02-Components/RFIDSimple
*/
 
void setup() {
  Serial.begin(9600);

  initRFID();
}

void loop() {
  
  if(verificaTag()) {
    Serial.println(getUidTag());
  }

}