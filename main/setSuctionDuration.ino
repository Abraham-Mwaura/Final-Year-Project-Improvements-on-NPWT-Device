void setSuctionDuration(){
            while(true){
                  if (millis() - lastUpdate > updateInterval) {
                        lcd.clear();
                        lcd.setCursor(2,1);
                        lcd.print("SUCTION DURATION");
                        lcd.setCursor(4,2);
                        lcd.print(suctionDuration);
                        lcd.setCursor(7,2);
                        lcd.print("Min");
                    lastUpdate=millis();
                  }


              
              
              if(isButtonPressed(buttonDown)&& suctionDuration<31){
                  suctionDuration+=1;  
                }
              if(isButtonPressed(buttonUp) && suctionDuration>1){
                  suctionDuration-=1;  
                }
               
              if(isButtonPressed(buttonSelect)){
                  currentItem=0;
                  break;
                }
             
            }
         }
