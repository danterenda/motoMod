const int BTN_SIGNAL_LEFT = 3;
const int BTN_SIGNAL_RIGHT = 2;

const int salidaGiroIzq =  13;
const int salidaGiroDer =  12;

long IzqOnTime = 0;
long IzqlastSwitchTime = 0;

long DerOnTime = 0;
long DerlastSwitchTime = 0;

int bounceTime = 60;
int holdTime = 250;
int doubleTime = 750;
int hold = 0;
int single = 0;
int lastReading = LOW;


//LEFT SIGNAL
int LSbuttonState = LOW;         // current state of the button
int LSlastButtonState = LOW;     // previous state of the button
//RIGHT SIGNAL
int RSbuttonState = LOW;         // current state of the button
int RSlastButtonState = LOW;     // previous state of the button




//long previousMillis = 0;        // will store last time LED was updated
//long interval = 200;           // interval at which to blink (milliseconds)

//FUNCTIONS////////////////////////////////////////////////////////////////
void CheckButtonState(int buttonPin, long &buttonTimer, int &buttonState, int &lastButtonState);
//void CheckSignal (int &othersignal);

void setup() {
  pinMode(salidaGiroIzq, OUTPUT);  
  pinMode(salidaGiroDer, OUTPUT);
  pinMode(BTN_SIGNAL_RIGHT, INPUT);
  pinMode(BTN_SIGNAL_LEFT, INPUT);
  Serial.begin(9600);
  Serial.println("The current button states are as follows:");
  Serial.println("-LS-RS-");
}

void loop(){
    CheckButtonState (BTN_SIGNAL_LEFT,  IzqOnTime, LSbuttonState, LSlastButtonState);
    CheckButtonState (BTN_SIGNAL_RIGHT, DerOnTime, RSbuttonState, RSlastButtonState);
   // Serial.print("--");
   // Serial.print(IzqOnTime);
   // Serial.print("--");
   // Serial.print(DerOnTime);
   // Serial.print("--");
   // Serial.println(" ");
}  //loop
void CheckButtonState (int buttonPin, long &buttonTimer, int &buttonState, int &lastButtonState){
    // read the pushbutton input pin:
    buttonState = digitalRead(buttonPin);
    //f
    if (buttonState == HIGH && lastButtonState == LOW) {
        buttonTimer = millis();
        Serial.print("first pressed-");
        Serial.print(IzqOnTime);
        Serial.print("-");
        Serial.print(DerOnTime);
        //Serial.print(buttonPin);
        Serial.println(" ");
    }
    //held
    if (buttonState == HIGH && lastButtonState == HIGH) {
        if ((millis() - buttonTimer) > holdTime) {
            //invertLED(); 
            //Serial.print("hold-");
            //Serial.print(IzqOnTime);
            //Serial.print(IzqOnTime);
            //Serial.println(" "); 
            hold = 1;
        }
    }
    //released
    if (buttonState == LOW && lastButtonState == HIGH) {
        if (((millis() - buttonTimer) > bounceTime) && hold != 1) {
             /*
             if ((millis() - buttonTimer) >= doubleTime) {
                 single = 1;
                 buttonTimer = millis();
             }  
             if ((millis() - buttonTimer) < doubleTime) {
                 Serial.println("double press");
                 single = 0;
                 buttonTimer = millis();
             } 
             */ 
        }
        if (hold == 1) {
            Serial.println("held");
            //digitalWrite(led2, LEDstate);
            hold = 0;
        }  
   }
   lastReading = buttonState;
   if (single == 1 && (millis() - buttonTimer) > doubleTime) {
       Serial.println("single press");
       single = 0;
   }
}


