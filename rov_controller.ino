
#include <string.h>
#include <SoftwareSerial.h>

//---------------------------------------- PIN settings-------------- 
#define SSerialTX        10  //Serial Transmit pin
#define SSerialRX        12  //Serial Receive pin

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

/*-----( Declare objects )-----*/

const int Left_Forward_buttonPin = 5;     // the number of the pushbutton pin
const int Left_Back_buttonPin = 3;     // the number of the pushbutton pin
const int Right_Forward_buttonPin = 4;     // the number of the pushbutton pin
const int Right_Back_buttonPin = 7;     // the number of the pushbutton pin
const int Up_buttonPin = 6;     // the number of the pushbutton pin
const int Down_buttonPin = 2;     // the number of the pushbutton pin
      // the number of the LED pin
int num_pins = 6;
const int pins[6] = {Left_Forward_buttonPin,Left_Back_buttonPin,Right_Forward_buttonPin, Right_Back_buttonPin, Up_buttonPin,Down_buttonPin}; 
int pins_value[6] = {0,0,0,0,0,0};
 
//--------------------------------

String output_value;
String buttonState_value;
String outMessage = "";
char message[31];
float actual_temp = 0;
float voltage;
float temperature;
 
int buttonState = 0;         // variable for reading the pushbutton status

int ledPin = 1;

//--------------------initialize---------------
void setup() {
  
  // --- this is the LED
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  
  Serial.begin(4800);
  RS485Serial.begin(4800);   

  for  (int i = 0; i < num_pins; i++) {  
     pinMode(pins[i], INPUT);   
     Serial.println(i);
  }
  
  Serial.println("starting...");
}


//----------------------------loop-----------------------

void loop()
{
  digitalWrite(A1, LOW);
  get_pin_state();
  send_pin_state(240); 
  
  Serial.print("Thruster status: ");
  for  (int i = 0; i < num_pins; i++) {
    Serial.print( pins_value[i]);
    if (pins_value[i] == 1) {
        digitalWrite(A1, HIGH);
       
    } 
    
  }

  Serial.println();  
}


void get_pin_state() {  
    buttonState_value ="";
    // we need to get the pin values and append them to the output string 
    output_value ="<";
    for  (int i = 0; i < num_pins; i++) {
        // read the state of the pushbutton value:
        int buttonState = digitalRead(pins[i]);
        // check if the pushbutton is pressed.
        // if it is, the buttonState is HIGH:
        if (i != 0)  { 
           output_value +=",";
        }  
    
        if ((buttonState == LOW) ) {   
            buttonState_value = String(1);
            pins_value[i] =1; 
        } 
        else {
           buttonState_value = String(0);
           pins_value[i] =0;    
         }
        output_value += buttonState_value;
    }  
    output_value +=">";
}
  
void send_pin_state (int delay_time) {  
  
  
  
  RS485Serial.print(output_value);          // Send byte to Remote Arduino
  Serial.println(output_value);
  
    delay(delay_time);
    RS485Serial.flush();


}




// if we were sending data to the master, this function would read it in 
void request_data (void) {

  
  String stringOne = "";
  String temperature_str;
  String  voltage_str;

   voltage_str = stringOne.substring(0,2);
 
   voltage = (voltage_str.toInt());
   voltage = voltage/10;  
     
   temperature = (temperature_str.toInt()); 
   temperature = temperature/10;
   
}

