/* 
This sketch expects an Adafruit Motor Shield for Arduino v2
---->	http://www.adafruit.com/products/1438
- Adjust LEDs by PWM on motor lines 1 (coax), 3 (front), 4 (back) - 
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
Adafruit_DCMotor *backLEDs  = AFMS.getMotor(4);

  // Name the input lines by pushbutton order:
  int pushButton_1 = 2;
  int pushButton_2 = 3;
  int pushButton_3 = 4;
  int pushButton_4 = 5;
  int pushButton_5 = 6;

  //When controlling over Serial, the following
  //booleans are enabled
  bool btn1(false); //Not in use
  bool btn2(false);  //Not in use
  
  bool btn3(false); //Turn off LEDs
  bool btn4(false); //Turn on LEDs 
  bool btn5(false); //Flash/toggle the LEDs   

  //To control light intensity
  int frontLEDDrive(128);
  int backLEDDrive(128);

  int flashFlag     = false;
  int flashToggle   = true;
  int flashInterval = 50;
  unsigned long flashMillis = millis();
    
  void checkPINStates();
  void processByte(char ch); 

  //Allow nice syntax for serial printing
  template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }
  
void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz
  
    // depower devices:
    frontLEDs->run(RELEASE);
    backLEDs->run(RELEASE);
       
    // set solenoid "on" duty cycles:    
    frontLEDs->setSpeed(frontLEDDrive);
    backLEDs->setSpeed(backLEDDrive);
     
    // set the pushbutton pins as inputs:
    pinMode(pushButton_1, INPUT); // Coax LEDs OFF
    pinMode(pushButton_2, INPUT); // Coax LEDs ON
    pinMode(pushButton_3, INPUT); // front&back OFF
    pinMode(pushButton_4, INPUT); // front&back ON
    pinMode(pushButton_5, INPUT); // front-back ALT

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
        backLEDs->run(RELEASE);
        flashFlag = false;
        btn3 = false; 
    }  

    if (digitalRead(pushButton_4) || btn4 == true)
    {
        Serial << "[BUTTON_4_DOWN]";
        frontLEDs->run(FORWARD);
        backLEDs->run(FORWARD);
        flashFlag = false;
        btn4 = false; 
    }

    if (digitalRead(pushButton_5) || btn5 == true)
    {
        Serial << "[BUTTON_5_DOWN]";
        flashFlag   = true;
        flashToggle = true;
        flashMillis = millis();
        btn5 = false; 
    }

    if (flashFlag && (millis() >= flashMillis))
    {
        if (flashToggle)
        {
            frontLEDs->run(FORWARD);
            backLEDs->run(RELEASE);
            flashToggle = false;
        }
        else
        {
            frontLEDs->run(RELEASE);
            backLEDs->run(FORWARD);
            flashToggle = true;
        }
        flashMillis = millis() + flashInterval;
    }
}
  
void processByte(char ch)
{
    switch(ch)
    {
        case '1':            btn1 = true ;        break;
        case '2':            btn2 = true ;        break;
        case '3':            btn3 = true ;        break;
        case '4':            btn4 = true ;        break;
        case '5':            btn5 = true ;        break;
        
        case 'f':
            frontLEDDrive = Serial.parseInt();
            frontLEDs->setSpeed(frontLEDDrive);
            Serial << "[FRONT_LED_DRIVE=" << frontLEDDrive<<"]";                        
        break;

        case 'b':
            backLEDDrive = Serial.parseInt();
            backLEDs->setSpeed(backLEDDrive);
            Serial << "[BACK_LED_DRIVE="<<backLEDDrive<<"]";                                    
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
    Serial << "[" << ((digitalRead(1)) ? "PIN_1=HIGH," : "PIN_1=LOW") << "]";
    Serial << "[" << ((digitalRead(2)) ? "PIN_2=HIGH," : "PIN_2=LOW") << "]";    
    Serial << "[" << ((digitalRead(3)) ? "PIN_3=HIGH," : "PIN_3=LOW") << "]";    
    Serial << "[" << ((digitalRead(4)) ? "PIN_4=HIGH," : "PIN_4=LOW") << "]";
    Serial << "[" << ((digitalRead(5)) ? "PIN_5=HIGH," : "PIN_5=LOW") << "]";    
    Serial << "[" << ((digitalRead(6)) ? "PIN_6=HIGH," : "PIN_6=LOW") << "]"; 
    Serial << "[" << ((digitalRead(7)) ? "PIN_7=HIGH," : "PIN_7=LOW") << "]";    
    Serial << "[" << ((digitalRead(8)) ? "PIN_8=HIGH," : "PIN_8=LOW") << "]";            
    Serial << "[FRONT_LED_DRIVE="<<frontLEDDrive<<"]";
    Serial << "[BACK_LED_DRIVE="<<backLEDDrive<<"]";
}
  
