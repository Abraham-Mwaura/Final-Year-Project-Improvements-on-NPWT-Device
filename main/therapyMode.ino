
const char* therapyPressureTypes [][4] = {
  {"->LOW PRESSURE","  MEDIUM PRESSURE","  HIGH PRESSURE","  BACK"},
  {"  LOW PRESSURE","->MEDIUM PRESSURE","  HIGH PRESSURE","  BACK"},
  {"  LOW PRESSURE","  MEDIUM PRESSURE","->HIGH PRESSURE","  BACK"},
  {"  LOW PRESSURE","  MEDIUM PRESSURE","  HIGH PRESSURE","<-BACK"},

   };

void therapyMode(){
  char buffer[20];
  currentItem=0;
  while(true){

      if (millis() - lastUpdate > updateInterval) {
          lcd.clear();
          lcd.setCursor(0,0);
          sprintf(buffer, "%s", therapyPressureTypes[currentItem][0]);
          lcd.print(buffer);

          lcd.setCursor(0,1);
          sprintf(buffer,"%s", therapyPressureTypes[currentItem][1]);
          lcd.print(buffer);

          lcd.setCursor(0,2);
          sprintf(buffer,"%s", therapyPressureTypes[currentItem][2]);
          lcd.print(buffer);

          lcd.setCursor(0,3);
          sprintf(buffer,"%s", therapyPressureTypes[currentItem][3]);
          lcd.print(buffer);
          lastUpdate=millis();
        }

      if(isButtonPressed(buttonDown)){
             
             currentItem++;
             currentItem= ((currentItem %4) + 4)%4;
          }

      if(isButtonPressed(buttonUp)){     
             currentItem--;
             currentItem= ((currentItem %4) + 4)%4;
            
          }
        
      if(isButtonPressed(buttonSelect)){
                    if (currentItem==0){
                      therapyFunc();
                    }
                    if (currentItem==1){
                      therapyFunc();  
                    }
                  if (currentItem==2){
                      therapyFunc();
                    }
                  if(currentItem==3){
                        currentItem=0;
                        break; 
                  }
          }
       }
    
      
}
