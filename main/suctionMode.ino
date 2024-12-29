const char* suctionModeItems [][3] = {
  {"->SET PRESSURE","  START SUCTION","  BACK"},
  {"  SET PRESSURE","->START SUCTION","  BACK"},
  {"  SET PRESSURE","  START SUCTION","<-BACK"}
  };
  
void suctionMode(){
  char buffer[20];
  currentItem=0;
  
  suctionPressure=operatingPressure[therapyPressureRange][0];
  while (true){
      if (millis() - lastUpdate > updateInterval) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("MIN P:50,MAX:200mmHg");
          lcd.setCursor(0,1);
          sprintf(buffer,"%s:%d",suctionModeItems[currentItem][0],suctionPressure);
          lcd.print(buffer);
          lcd.setCursor(0,2);
          sprintf(buffer,"%s",suctionModeItems[currentItem][1]);
          lcd.print(buffer);
          lcd.setCursor(0,3);
          sprintf(buffer,"%s",suctionModeItems[currentItem][2]);
          lcd.print(buffer);
          lastUpdate = millis();
       }
      
      if(isButtonPressed(buttonDown)){
          currentItem++;
          currentItem= ((currentItem %3) + 3)%3;
          }
          
      if(isButtonPressed(buttonUp)){
          currentItem--;
          currentItem= ((currentItem %3) + 3)%3;
          }

       if(isButtonPressed(buttonSelect)){
            if (currentItem==0){
             
                setSuctionPressure(therapyPressureRange);
           }
            if (currentItem==1){
                suctionFunc();
                currentItem=0;
           }
            if (currentItem==2){
                  currentItem=0;
                  break;
             }
      }
    }     
}