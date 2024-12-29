void setSuctionPressure(int operatingRange){
            
           while(true){
              if (millis() - lastUpdate > updateInterval) {
                  lcd.clear();
                  lcd.setCursor(2,1);
                  lcd.print("SUCTION PRESSURE");
                  lcd.setCursor(8,2);
                  lcd.print(suctionPressure);
                  lastUpdate=millis();
               }

              
              if(isButtonPressed(buttonDown)&&suctionPressure<=operatingPressure[operatingRange][1]){
                  suctionPressure+=1;  
                }
              if(isButtonPressed(buttonUp)&& suctionPressure>operatingPressure[operatingRange][0]){
                  suctionPressure-=1;  
                }
                
              if(isButtonPressed(buttonSelect)){
                  currentItem=0;
                  break;
                }  
            }
    
          }

