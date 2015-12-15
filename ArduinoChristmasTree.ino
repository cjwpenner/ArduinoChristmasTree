/* Arduino Christmas Tree
16 character 2 line I2C Display
Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
GND - GND
VCC - 5V
SDA - ANALOG Pin 4
SCL - ANALOG pin 5
On most Arduino boards, SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5. On the Arduino Mega, SDA is digital pin 20 and SCL is 21.
NOTE: The Blue Potentiometer (Photo) adjusts Contrast. If you don't see any characters, adjust it. Start clockwise and back down to where the characters are bright and the background does not have boxes behind the characters.

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Variables )-----*/
int count=1;
//LED Pin Variables
const int ledArray[] = { 12, 11, 10, 9, 8, 7, 6, 5}; // This is the variable where you declare the LED pin-out in the order you're connecting it 
byte ledData=0; // This is the actual number that's going to be displayed. Byte is used since only 8 LEDs are used. After 255 it overflows back to 0. 
unsigned int timerRef, timerNow; // These are the time tracking variables. For better understanding check out arduino.cc's BlinkWithoutDelay 
const unsigned int waitms = 500; // This is the delay in milliseconds 
int diffms; // Time difference in milliseconds 
int ledNo = 8; // Total number of LEDs being used
 
/*
 * setup() - this function runs once when you turn your Arduino on
 * We the three control pins to outputs
 */

void setup()   /*----( SETUP: RUNS ONCE )----*/
{  
   // Here we initialize all the LED pins to output and start our 'clock' timer 
      for(int i=0; i < ledNo; i++)
      {
              pinMode(ledArray[i], OUTPUT);
      }
      timerRef = millis();


//LCD Set Up
lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of LCD backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

//-------- Write Intro characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
lcd.setCursor(0,0); //Start at character 0 on line 0
lcd.print("Merry Christmas");
delay(2000);  

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  timerNow = millis();
      diffms = timerNow - timerRef;
      diffms = abs(diffms);
      /* The Loop() runs as fast as possible, and at every point that it runs I check if enough time has elapsed between the previous 
     execution of the if statement below using the handy millis(). The if statement below gets tested all the time, but since most 
     of the time it's false, the program simply continues without processing statements inside the if-block */
      if(diffms >= waitms)
      {
              
             
              setLED(ledData);
              ledData = ledData + 1;
              timerRef = millis();
              lcd.clear();
 
      }
 lcd.print("Cristmas Count");
 lcd.setCursor(0,1);
 lcd.print(ledData);
delay (500);
}

void setLED(byte number)
{
      int bitOutput;
      for(int i = 0; i < 8; i++) //Although I've directly used the number '8' the more correct way would be to use sizeof(number) in case you want a generic solution 
      {
              bitOutput = number & 1;
              digitalWrite(ledArray[i], bitOutput);
              number=number>>1;
      }
}

 
/* ( THE END ) */
