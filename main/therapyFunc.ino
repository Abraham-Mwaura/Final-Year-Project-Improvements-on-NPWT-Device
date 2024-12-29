
const char* therapyTypePressureRange []={"  LOW:50-100mmHG","  MEDIUM:100-150mmHG","  HIGH:150-200mmHG"};

const char* therapyParameters[][5] = {
  {"->TARGET  :","  DURATION:","  THERAPY :","  START THERAPY","  EXIT"},
  {"  TARGET  :","->DURATION:","  THERAPY :","  START THERAPY","  EXIT"},
  {"  TARGET  :","  DURATION:","->THERAPY :","  START THERAPY","  EXIT"},
  {"  TARGET  :","  DURATION:","  THERAPY :","->START THERAPY","  EXIT"},
  {"  TARGET  :","  DURATION:","  THERAPY :","  START THERAPY","<-EXIT"}
};

void therapyFunc(){
  //to be able to display different therapies
  therapyPressureRange=currentItem;
  currentItem=0;
  suctionPressure= operatingPressure[therapyPressureRange+1][0];
  char buffer[20];
  suctionPressure=operatingPressure[therapyPressureRange+1][0];
  while(true){
      if (millis() - lastUpdate > updateInterval) {
          if(currentItem>2){
              lcd.clear();
              lcd.setCursor(0,0);
              
              sprintf(buffer, "%s", therapyTypePressureRange[therapyPressureRange]);
              lcd.print(buffer);

              lcd.setCursor(0,1);
              lcd.print(therapyParameters[currentItem][3]);
              lcd.setCursor(0,2);
              lcd.print(therapyParameters[currentItem][4]);
              }
          else{
              lcd.clear();
              lcd.setCursor(0,0);
              sprintf(buffer, "%s", therapyTypePressureRange[therapyPressureRange]);
              lcd.print(buffer);
              
              lcd.setCursor(0,1);
              sprintf(buffer,"%s%dmmHg",therapyParameters[currentItem][0],suctionPressure);
              lcd.print(buffer);
              
              lcd.setCursor(0,2);
              sprintf(buffer,"%s%dMins",therapyParameters[currentItem][1],suctionDuration);
              lcd.print(buffer);
              
              lcd.setCursor(0,3);
              sprintf(buffer,"%s%s",therapyParameters[currentItem][2],therapyTypes[therapyType]);
              lcd.print(buffer);
              }

    lastUpdate=millis();
  }  

            if(isButtonPressed(buttonDown)){
              currentItem+=1;
              currentItem= ((currentItem %5) + 5)%5;
            }

            if(isButtonPressed(buttonUp)){   
              currentItem-=1;
              currentItem= ((currentItem %5) + 5)%5;
              
            }

          if(isButtonPressed(buttonSelect)){
                  if(currentItem==0){
                    setSuctionPressure(therapyPressureRange+1);   
                }
                  if(currentItem==1){
                    setSuctionDuration();
                }
                if(currentItem==2){
                    therapyType=therapyType==0?1:0;
                }

                if(currentItem==3){
                  suctionTherapyFunc();
                }
              
                if(currentItem==4){
                  currentItem=0;
                    break;
                } 
            }
          }
  }