// include the library code:
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//control buttons
#define buttonSelect 8
#define buttonDown 9
#define buttonUp 10

String startMenuItems [][2] = {
  {"->SUCTION MODE","  THERAPY MODE"},
  {"  SUCTION MODE","->THERAPY MODE"}
  };
  
const char* suctionModeItems [][4] = {
  {"->SET PRESSURE","  START SUCTION","  BACK"},
  {"  SET PRESSURE","->START SUCTION","  BACK"},
  {"  SET PRESSURE","  START SUCTION","<-BACK"},
  {"  SET PRESSURE","  PRESSURE:","<-STOP SUCTION"}
  };
  
String therapyPressureTypes [][5] = {
  {"->LOW PRESSURE","  MEDIUM PRESSURE","  HIGH PRESSURE","  BACK"},
  {"  LOW PRESSURE","->MEDIUM PRESSURE","  HIGH PRESSURE","  BACK"},
  {"  LOW PRESSURE","  MEDIUM PRESSURE","->HIGH PRESSURE","  BACK"},
  {"  LOW PRESSURE","  MEDIUM PRESSURE","  HIGH PRESSURE","<-BACK"},
  {"  LOW:50-100mmHG","  MEDIUM:100-150mmHG","  HIGH:150-200mmHG",""}
   };
   
const char* therapyParameters[][5] = {
  {"->TARGET  :","  DURATION:","  THERAPY :","  START THERAPY","  EXIT"},
  {"  TARGET  :","->DURATION:","  THERAPY :","  START THERAPY","  EXIT"},
  {"  TARGET  :","  DURATION:","->THERAPY :","  START THERAPY","  EXIT"},
  {"  TARGET  :","  DURATION:","  THERAPY :","->START THERAPY","  EXIT"},
  {"  TARGET  :","  DURATION:","  THERAPY :","  START THERAPY","<-EXIT"}
};

int operatingPressure[][2]={
  {50,200}, //suction mode
  {50,100}, //low pressure
  {100,150}, //medium pressure
  {150,200}  //high pressure
};

const char*therapyFuncPrModes[]={"LOW P:","MED P:","HIG P:"};
const char*therapyTypes []={"CONTINOUS","VARIABLE"};
                                                     
int currentItem =0; 
int suctionPressure =51;
int actualPressure=0;
int suctionDuration =15;
int therapyType=0;
int therapyPressureRange=0;
char buffer[20];

void setup() {
    pinMode(buttonUp, INPUT_PULLUP);
    pinMode(buttonDown, INPUT_PULLUP);
    pinMode(buttonSelect, INPUT_PULLUP);
    
    // set up the LCD's number of columns and rows:
    lcd.begin(20, 4);
    // Print a message to the LCD.
      lcd.setCursor(1, 1);
    lcd.print(" NEGATIVE PRESSURE");
    lcd.setCursor(1, 2);
    lcd.print("     DEVICE");
    delay(2200);
    Serial.begin(9600);
}

void loop() {
    startMenu();
    //serves as the delay for the loop and function call too.
    delay(200);
}

void startMenu(){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("SELECT MODE OPTION");
        lcd.setCursor(1,1);
        lcd.print(startMenuItems[currentItem][0]);
        lcd.setCursor(1,2);
        lcd.print(startMenuItems[currentItem][1]);
        lcd.setCursor(0,3);
        lcd.print("(move up&down,enter)");
        if(digitalRead(buttonDown) == LOW){
           //removed delay here for long press
           
          //we step the values 3 units higher to avoid a negative number.
          currentItem++;
          currentItem= ((currentItem %2) + 2)%2;
      
          }
          
          if(digitalRead(buttonUp) == LOW){
            
           //removed delay here for long press
          currentItem--;
          currentItem= ((currentItem %2) + 2)%2;
 
          }
          
          if(digitalRead(buttonSelect)== LOW){
                delay(100); //in button delay
                if (currentItem==0){
                   // delay(200); //Avoid sudden skip to next highligheed option
                    suctionMode();
                      delay(200); //delay a bit after function call
                   } 
                if (currentItem==1){
                    therapyMode();
                    delay(200);  
                } 
        }  
}

void suctionMode(){
  currentItem=0;
  while (true){
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
      
      if(digitalRead(buttonDown) == LOW){
        //removed delay here for long press
        currentItem++;
        currentItem= ((currentItem %3) + 3)%3;
        }
        
      if(digitalRead(buttonUp) == LOW){
        //removed delay here for long press
        currentItem--;
        currentItem= ((currentItem %3) + 3)%3;
        }
       //delay(200); 
       if(digitalRead(buttonSelect)==LOW){
             delay(100); //debounce
            if (currentItem==0){
                setSuctionPressure(therapyPressureRange);
                delay(200);
               currentItem=0;
           }
            if (currentItem==1){
                suctionFunc();
                delay(200);
               currentItem=0;
           }
            if (currentItem==2){
                  currentItem=0;
                  break;
             }
      }
        //debounce and screen flicker
        delay(200);
    }
        
    currentItem=0;
    startMenu();
    delay(200);
}


void setSuctionPressure(int operatingRange){
            suctionPressure=operatingPressure[operatingRange][0];
            while(true){
              lcd.clear();
              lcd.setCursor(2,1);
              lcd.print("SUCTION PRESSURE");
              lcd.setCursor(8,2);
              lcd.print(suctionPressure);
              
              if(digitalRead(buttonUp)==LOW && suctionPressure<=operatingPressure[operatingRange][1]){
                  //removed delay for long press working
                  suctionPressure+=1;  
                }
              if(digitalRead(buttonDown)==LOW && suctionPressure>operatingPressure[operatingRange][0]){
                 //removed delay for long press working
                  suctionPressure-=1;  
                }
                
              if(digitalRead(buttonSelect)==LOW){
                  delay(100); //in button delay
                  currentItem=0;
                   //delay(200); 
                  break;
                }
                 //delay(200); 
            delay(200);     
            }
          }




void suctionFunc(){
          while(true){
          actualPressure=analogRead(A1);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("MIN P:50,MAX:200mmHg");
          lcd.setCursor(0,1);
          sprintf(buffer,"%s:%d",suctionModeItems[3][0],suctionPressure);
          lcd.print(buffer);
          lcd.setCursor(0,2);
          sprintf(buffer, "%s:%d",suctionModeItems[3][1],actualPressure);
          lcd.print(buffer);
          lcd.setCursor(0,3);
          lcd.print(suctionModeItems[3][2]);
       
          if(digitalRead(buttonSelect)==LOW){
                  delay(100); //in button delay
                  currentItem=0;
                  //delay(200);
                  break;
           }
         delay(200);
          }
         }


void therapyMode(){
   currentItem=0;
  while(true){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(therapyPressureTypes[currentItem][0]);
          lcd.setCursor(0,1);
          lcd.print(therapyPressureTypes[currentItem][1]);
          lcd.setCursor(0,2);
          lcd.print(therapyPressureTypes[currentItem][2]);
          lcd.setCursor(0,3);
          lcd.print(therapyPressureTypes[currentItem][3]);

          if(digitalRead(buttonDown)==LOW){
              //removed delay here for long press
             currentItem++;
             currentItem= ((currentItem %4) + 4)%4;
          }

          if(digitalRead(buttonUp)==LOW){     
                //removed delay here for long press
             currentItem--;
             currentItem= ((currentItem %4) + 4)%4;
            
          }
        
          if(digitalRead(buttonSelect)==LOW){
              delay(100); //in button delay
            if(currentItem==3){
                currentItem=0;
                //delay(200);
                break; 
            }
            if (currentItem==0){
              //therapyMode=currentItem;
               therapyFunc();
                delay(200);
            }
            if (currentItem==1){
             // therapyMode=currentItem;
               therapyFunc();
             delay(200);
            }
          if (currentItem==2){
             // therapyMode=currentItem;
               therapyFunc();
               delay(200);
            }
            

          }
      delay(200);
       }
    
       startMenu();  
       delay(200); 
}


void therapyFunc(){
  //to be able to display different therapies
  therapyPressureRange=currentItem;
  currentItem=0;
  suctionPressure= operatingPressure[therapyPressureRange+1][0];
  while(true){
        if(currentItem>2){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(therapyPressureTypes[4][therapyPressureRange]);
            lcd.setCursor(0,1);
            lcd.print(therapyParameters[currentItem][3]);
            lcd.setCursor(0,2);
            lcd.print(therapyParameters[currentItem][4]);
         }
         else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(therapyPressureTypes[4][therapyPressureRange]);
            
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


         
          if(digitalRead(buttonDown)==LOW){
            //removed delay for long press working
             currentItem+=1;
             currentItem= ((currentItem %5) + 5)%5;
          }

          if(digitalRead(buttonUp)==LOW){   
             //removed delay for long press working
             currentItem-=1;
             currentItem= ((currentItem %5) + 5)%5;
            
          }

            //delay(200);
         if(digitalRead(buttonSelect)==LOW){
                delay(100); //in button delay
                if(currentItem==0){
                  setSuctionPressure(therapyPressureRange);
                   delay(200);
               }

                 if(currentItem==1){
                  setSuctionDuration();
                  delay(200);
               }
               
               if(currentItem==2){
                  therapyType=therapyType==0?1:0;
                  //delay(200);
               }

                if(currentItem==3){
                 suctionTherapyFunc();
                   delay(200);
               }
            
               if(currentItem==4){
                currentItem=0;
               //delay(200);
                  break;
               }
            
            
          }
           delay(200);
        }
        therapyMode();
        delay(200);
}


void setSuctionDuration(){
            while(true){
              lcd.clear();
              lcd.setCursor(2,1);
              lcd.print("SUCTION DURATION");
              lcd.setCursor(4,2);
              lcd.print(suctionDuration);
              lcd.setCursor(7,2);
              lcd.print("Min");
              
              
              if(digitalRead(buttonUp)==LOW && suctionDuration<31){
                 // delay(100); //in button delay
                  suctionDuration+=1;  
                }
              if(digitalRead(buttonDown)==LOW && suctionDuration>1){
                  //delay(100); //in button delay
                  suctionDuration-=1;  
                }
               
              if(digitalRead(buttonSelect)==LOW){
                  delay(100); //in button delay
                  currentItem=0;
                  //delay(200);
                  break;
                }
                  delay(200); 
            }
         }


void suctionTherapyFunc(){
  int startTime=millis();
         while(true){
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
              lcd.print(suctionDuration-(millis()-startTime)/1000);
              lcd.setCursor(0,3);
              lcd.print("->STOP THERAPY");
              
        
              if(digitalRead(buttonSelect)==LOW ||(((millis()-startTime)/1000) > suctionDuration) ){
                      delay(100); //in button delay
                   currentItem=0;
                   break;
                }
             delay(200);
            }
    
  
}
