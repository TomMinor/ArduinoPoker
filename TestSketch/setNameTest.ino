//Enter the name on the LCD
//to scroll through the alphabet press UP or DOWN
//to confirm the letter press SELECT
//to move forward or back press RIGHT or LEFT
//Remember to press SELECT everytime you confirm a letter -> that letter will be inserted in the array representing the player's name

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char alphabet [] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char name[16];
int index = 25;
int initPosX = 0;
int initPosY = 1;
int currentPosX, currentPosY;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Enter Name:");
  //where insertion name starts from
  lcd.setCursor(initPosX, initPosY);
  currentPosX = initPosX;
  currentPosY = initPosY;

}

void loop() {
  int x;
  x = analogRead (0);
  lcd.setCursor(currentPosX,currentPosY);
  
  if (x < 60) {    
    currentPosX += 1;
    lcd.setCursor(currentPosX,currentPosY);
    index = 25;
    delay(400);
  }
  
  if (x > 60 && x < 200) { //UP
    index+=1;
    if(alphabet[index] == '\0'){
      index = 0;
    }
    lcd.print(alphabet[index]);
    delay(400);
  
  }
  else if (x > 200 && x < 400){ //DOWN
    index-=1;
    if(alphabet[index] == '\0'){
      index = 25;
    }
    lcd.print(alphabet[index]);
    delay(400);
  }
  else if (x > 400 && x < 600){ //LEFT
    currentPosX -= 1;
    lcd.setCursor(currentPosX,currentPosY);
    delay(400);
  }
  else if (x> 600 && x < 800){ //SELECT
    name[currentPosX] = alphabet[index];
    //Testing bit
    lcd.setCursor(11,1);
    lcd.print(name);
  }
}
