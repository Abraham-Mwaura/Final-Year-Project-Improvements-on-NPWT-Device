
const char*therapyFuncPrModes[]={"LOW P:","MED P:","HIG P:"};

void suctionTherapyFunc(){
  char buffer[20];
  unsigned long startTime=millis(); //500
  unsigned long remainingTime=0;
  
  while(millis()-startTime<suctionDuration*1000){
    if (millis() - lastUpdate > updateInterval) {
        lcd.clear();
        lcd.setCursor(0,0);
        sprintf(buffer,"%s%s:mmHg",therapyFuncPrModes[therapyPressureRange],therapyTypes[therapyType]);
        lcd.print(buffer);
        lcd.setCursor(0,1);
        lcd.print("SET P:");
        lcd.setCursor(6,1);
        lcd.print(suctionPressure);
        lcd.setCursor(10,1);
        lcd.print("SUC P:");
        lcd.setCursor(16,1);
        lcd.print(analogRead(A1));
        lcd.setCursor(0,2);
        lcd.print("Remaining time:");
        lcd.setCursor(15,2);
        remainingTime=suctionDuration-((millis()-startTime)/1000);     //600-500
        lcd.print(remainingTime);
        lcd.setCursor(0,3);
        lcd.print("->STOP THERAPY");
        lastUpdate=millis();
      }

      if(  isButtonPressed(buttonSelect)){
            currentItem=0;
            //Serial.println(remainingTime);
            break;
                }
      }
     
}