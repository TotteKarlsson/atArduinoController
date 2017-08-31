/* 
This sketch expects an Adafruit Motor Shield for Arduino v2
---->	http://www.adafruit.com/products/1438
- Adjust LEDs by PWM on motor line 3 (front)
- Removed sensor reads
*/
/*March 2017 - TK removed all coax logic, preparing to add sensor code
 * 
*/

double sketchVersion = 1.0;
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the "motor" shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Name the "motor" ports by solenoid function:
Adafruit_DCMotor *frontLEDs = AFMS.getMotor(3);

  // Name the input lines by pushbutton order:
  int pushButton_3 = 4;
  int pushButton_4 = 5;


  //When controlling over Serial, the following
  //booleans are enabled 
  bool btn4(false); //Turn on LEDs  
  bool btn3(false); //Turn off LEDs
  
  //To control light intensity
  int frontLEDDrive(128);
      
  void checkPINStates();
  void processByte(char ch); 

  //Allow nice syntax for serial printing
  template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }
  
void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz
  
    // depower devices:
    frontLEDs->run(RELEASE);
         
    // set solenoid "on" duty cycles:    
    frontLEDs->setSpeed(frontLEDDrive);
         
    // set the pushbutton pins as inputs:
    pinMode(pushButton_3, INPUT); // front OFF
    pinMode(pushButton_4, INPUT); // front ON
    
    // setup serial port
    Serial.begin(19200);
    sendInfo();    
}

void loop() 
{ 
    while(Serial.available() > 0)
    {         
        processByte(Serial.read());
    }    
   
    if (digitalRead(pushButton_3) || btn3 == true)
    {
        Serial << "[BUTTON_3_DOWN]";
        frontLEDs->run(RELEASE);
        btn3 = false; 
    }  

    if (digitalRead(pushButton_4) || btn4 == true)
    {
        Serial << "[BUTTON_4_DOWN]";
        frontLEDs->run(FORWARD);        
        btn4 = false;         
    }    
}
  
void processByte(char ch)
{
    switch(ch)
    {
        case '3':            btn3 = true ;        break;
        case '4':            btn4 = true ;        break;
                
        case 'f':
            frontLEDDrive = Serial.parseInt();
            frontLEDs->setSpeed(frontLEDDrive);
            Serial << "[FRONT_LED_DRIVE=" << frontLEDDrive<<"]";                        
        break;
        
        case 'i': //Return info about current HW state
            sendInfo();
        break;
        
        default: //Do nothing
            Serial << "[UNHANDLED_CHAR_RECEIVED:'"<<ch<<"']";
        ;
    }    
}

void sendInfo()
{
    Serial << "[ARRAYBOT LIGHTS VERSION="<<sketchVersion<<"]";    
    
    //Read and report states of "light pins"                
    Serial << "[" << ((digitalRead(4)) ? "PIN_4=HIGH," : "PIN_4=LOW") << "]";
    Serial << "[" << ((digitalRead(5)) ? "PIN_5=HIGH," : "PIN_5=LOW") << "]";    
    Serial << "[FRONT_LED_DRIVE="<<frontLEDDrive<<"]";    
}
  
