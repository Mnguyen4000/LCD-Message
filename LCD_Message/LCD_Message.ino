// Include Libraries for RFID - rfid-master
#include <SPI.h>
#include <MFRC522.h>

// Include Libraries for LCD - LiquidCrystal-I2C-Library-Master
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address
/* 16 characters wide, with 2 rows*/

// Defining pins for the RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


 
void setup()
{
pinMode(3,OUTPUT); // Setup for LED at pin 3
Serial.begin(9600);  // Begin Serial Monitor
SPI.begin(); // Sets SCK, MOSI AND SS to OUTPUTS : SSK and MOSI (LOW), and SS (HIGH)   
mfrc522.PCD_Init();   
Serial.println("Approximate your card to the reader...");// Message in Serial Monitor
Serial.println(); // Blank line in Serial Monitor

lcd.begin(); // Initialises the LCD with 16 characters, 2 lines and turns on backlight
lcd.clear(); // Clears all characters in LCD
}

void loop()
{ 
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println(); // Blank line in Serial Monitor
  Serial.print("Message : ");
  content.toUpperCase(); // Turns string 'content' to UPPERCASE letters

  
  if (content.substring(1) == "D9 C7 A5 5A") // D9 C7 A5 5A is KEYCHAIN, 59 DB 34 99 FOR WHITECARD
  { 
    Serial.println("Authorised access");
    Serial.println();
    Serial.println("HIGH"); // Message for when LED is on
    digitalWrite(3, HIGH); // LED turns on when scan matches
    int RNG = random(1,11); //  Picks a random int from 1 - 10
    static char hey[][40] = {
                  // Message 1
                  "SOCIETY", "BOTTOM TEXT",  
                  
                  // Message 2
                  "AMONGUS", "SUSSY BAKA",   
                        
                  // Message 3     
                  "8====3", "Woah! Wicked!!!",   
                    
                  // Message 4     
                  "I'm gonna", "say the word.",     
                  
                  // Message 5     
                  "POGGERS", " - Alex",          
                         
                  // Message 6
                  "Access Denied", "Reason: Stupid.",   
                  
                  // Message 7
                  "L + Ratio +", "Forfeit Bacon",  
                       
                  // Message 8
                  "OWO UWU oWo", "what's this?",     
                   
                    // Message 9
                  "Sad green frog", "said 'pepega'.",   
                  
                  // Message 10
                  "Peter Parker", "Peter Pooper"        
                            }; // Generates an array of phrases

    lcd.setCursor(1, 0); // Cursor at top line (1,0)
    int top = (RNG * 2) - 2; // Index of first part of message
    lcd.print(hey[top]); // Prints message at set cursor
    
    lcd.setCursor(1, 1); // Cursor at bottom line (1,1)
    int bot = (RNG * 2) - 1; // Index of second part of message
    lcd.print(hey[bot]);// Prints message at set cursor
    
    delay(1000); // After 1 second
    lcd.clear(); // Clear LCD message
    digitalWrite(3, LOW); // Turns off LED
    Serial.println("LOW"); // Alerts that LED is off

  
  }
  else
  {
    Serial.println(" Access denied");

    // Only occurs when using whitecard/not-the-keychain
    lcd.setCursor(1, 0);
    lcd.print("Nice WHITE");
    lcd.setCursor(1, 1);
    lcd.print("Cards");
    delay(1000);
    lcd.clear();
  }
}
