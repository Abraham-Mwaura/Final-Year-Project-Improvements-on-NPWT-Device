// include the library code:
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String menuItems[][3] = {{" ->MAX PRESSURE", "   MIN PRESSURE", "   START THERAPY"},{"   MAX PRESSURE", " ->MIN PRESSURE", "   START THERAPY"},{"   MAX PRESSURE", "   MIN PRESSURE", " ->START THERAPY"}};
int maxPressure =81;
int minPressure =80;

#define buttonSelect 8
#define buttonDown 9
#define buttonUp 10

int currentItem =0; 

void setup() {
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.setCursor(1, 1);
  lcd.print("  WOUND THERAPY");
  lcd.setCursor(1, 2);
  lcd.print("     DEVICE");
  delay(2200);
  updateMenu();
  Serial.begin(9600);
}

void loop() {

   if(digitalRead(buttonDown) == LOW){
    //we step the values 3 units higher to avoid a negative number.
    currentItem++;
    currentItem= ((currentItem %3) + 3)%3;
    updateMenu();
    Serial.println(currentItem);
    delay(200); //debounce
  }

   if(digitalRead(buttonUp) == LOW){
    currentItem--;
    currentItem= ((currentItem %3) + 3)%3;
    updateMenu();
    Serial.println(currentItem);
    delay(200); //debounce
    }
    
   if(digitalRead(buttonSelect)== LOW){
    delay(200);
    if (currentItem==0){
       setMaxPressure();
    }
        
     if (currentItem==1){
       setMinPressure();
    }
    
    
    delay(200); //debounce
  }

}

void updateMenu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("       SET");
  //max pressure
  lcd.setCursor(0, 1);
  lcd.print(menuItems[currentItem][0]+":"+maxPressure);
  //min pressure
  lcd.setCursor(0, 2);
  lcd.print(menuItems[currentItem][1]+":"+minPressure);
  //start therapy button
  lcd.setCursor(0,3);
  lcd.print(menuItems[currentItem][2]);
  delay(200);
  }

void setMaxPressure(){
    int status=1;
    while(status){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("  MAXIMUM PRESSURE");
      lcd.setCursor(8,2);
      lcd.print(maxPressure);
      
      if(digitalRead(buttonUp)==LOW && maxPressure<=130){
        maxPressure+=1;
      }
      if(digitalRead(buttonDown)==LOW && maxPressure>minPressure){
        maxPressure-=1;
      }
      if(digitalRead(buttonSelect)==LOW){
        status=0;
      }
      
      //to prevent screen flicker and for button debounces
      delay(200);
     }
     updateMenu();
  }

void setMinPressure(){
    int status=1;
    while(status){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("  MINIMUM PRESSURE");
      lcd.setCursor(8,2);
      lcd.print(minPressure);
      
      if(digitalRead(buttonUp)==LOW && minPressure<maxPressure){
        minPressure+=1;
      }
      if(digitalRead(buttonDown)==LOW && minPressure>=80){
        maxPressure-=1;
      }
      if(digitalRead(buttonSelect)==LOW){
        status=0;
      }
      
      //to prevent screen flicker and for button debounces
      delay(200);
     }
     updateMenu();
  }
