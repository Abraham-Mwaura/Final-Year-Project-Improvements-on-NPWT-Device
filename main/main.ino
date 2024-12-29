// include the library code:
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//control buttons
#define buttonSelect 8
#define buttonDown 9
#define buttonUp 10


int operatingPressure[][2]={
  {50,200}, //suction mode
  {50,100}, //low pressure
  {100,150}, //medium pressure
  {150,200}  //high pressure
};
const char*therapyTypes []={"CONTINOUS","VARIABLE"};

 const char* startMenuItems [][2] = {
  {"->SUCTION MODE","  THERAPY MODE"},
  {"  SUCTION MODE","->THERAPY MODE"}
  };

int currentItem =0; 
int suctionPressure =51;
int actualPressure=0;
unsigned long suctionDuration =15;
int therapyType=0;
int therapyPressureRange=0;
unsigned long lastUpdate = 0;
const int updateInterval = 200; // Update screen every 200ms



void suctionMode();
void setSuctionPressure();
void suctionFunc();
void therapyMode();
void therapyFunc();
void setSuctionDuration();
void suctionTherapyFunc();
bool isButtonPressed(int buttonPin);
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
  if (millis() - lastUpdate > updateInterval) {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("SELECT MODE OPTION");
        lcd.setCursor(1,1);
        sprintf(buffer,"%s",startMenuItems[currentItem][0] );
        lcd.print(buffer);

        lcd.setCursor(1,2);
        sprintf(buffer,"%s",startMenuItems[currentItem][1] );
        lcd.print(buffer);

        lcd.setCursor(0,3);
        lcd.print("(move up&down,enter)");
        lastUpdate = millis();
  }

        if(isButtonPressed(buttonDown)){
          currentItem++;
          currentItem= ((currentItem %2) + 2)%2;
      
          }
          
          if(isButtonPressed(buttonUp) ){
          currentItem--;
          currentItem= ((currentItem %2) + 2)%2;
 
          }
          
          if(isButtonPressed(buttonSelect)){
                delay(100); //in button delay
                if (currentItem==0){
                    suctionMode();
                   } 
                if (currentItem==1){
                    therapyMode();
                } 
        }  

}