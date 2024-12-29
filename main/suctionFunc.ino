const char* suctionFuncItems[] ={"  SET PRESSURE","  PRESSURE:","<-STOP SUCTION"};

void suctionFunc(){
         char buffer[20];
          while(true){
            actualPressure=analogRead(A1);
            if (millis() - lastUpdate > updateInterval) {
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("MIN P:50,MAX:200mmHg");
                  lcd.setCursor(0,1);
                  sprintf(buffer,"%s:%d",suctionFuncItems[0],suctionPressure);
                  lcd.print(buffer);
                  lcd.setCursor(0,2);
                  sprintf(buffer, "%s:%d",suctionFuncItems[1],actualPressure);
                  lcd.print(buffer);
                  lcd.setCursor(0,3);
                  lcd.print(suctionFuncItems[2]);
                  lastUpdate=millis();
            }

          
              if(isButtonPressed(buttonSelect)){  
                      currentItem=0;
                      break;
              }


          }
         }