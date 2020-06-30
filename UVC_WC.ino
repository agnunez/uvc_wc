// @agnuca June 2020
// https://
// fsm code from https://majenko.co.uk/blog/finite-state-machine
/*  // only for ESP8266
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
*/  
// Use 'Dx' for ESP8266 or int pin numbers for arduino

#define RELAY D0         // RELAY = 1 uvc on, RELAY = 0 uvc off
#define PIR   D1         // PIR = 1 presence, PIR = 0  NONE
#define DOOR  D5         // DOOR = 1 closed, DOOR = 0 open 
#define LED   D4         // LED = 0 light on, LED = 1 ligth off

// global variables
unsigned long ts1,ts2,ts3;
unsigned long t1 = 5000;  // Presence delay while empty 5s
unsigned long t2 = 10000;  // Presence delay while dirty 10s
unsigned long t3 = 15000;  // Cleaning time 15s

typedef enum state_t {
    S_EMPTY_CLEAN,    // 0
    S_SOMEONE_CLEAN,  // 1
    S_BUSY, // 2
    S_EMPTY_DIRTY, // 3
    S_CLEANING // 4
};

static state_t state = S_EMPTY_DIRTY; // Initial state EMPTY_DIRTY


// the setup function runs once when you press reset or power the board
void setup() {
/* Only for ESP8266
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
*/
  pinMode(RELAY, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(DOOR, INPUT);
  pinMode(PIR, INPUT);
  uvc(LOW); 
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("Inititialized");
}

void uvc(int uvc_status){
  digitalWrite(RELAY, uvc_status);  
  digitalWrite(LED, !uvc_status);  
}


void loop() {

    switch (state)   {
        case S_EMPTY_DIRTY:
            if (digitalRead(DOOR)>0) {
              Serial.println("DOOR CLOSED");
              state = S_BUSY;
              Serial.println("Change to state S_BUSY");
              break;
            }
            if (digitalRead(PIR)>0) {
              //Serial.println("PIR presence");
              ts2 = millis();            
              break;
            }
            if ((unsigned long)(millis() - ts2) > t2){
               ts2=millis();
               Serial.println("T2_TIMEOUT");
               ts3 = millis();            
               Serial.println("RESET_T3");
               state = S_CLEANING;
               Serial.println("Change to state S_CLEANING");
               uvc(HIGH);
               Serial.println("RED LED WARNING: UVC CLEANING!");
            }
            break;
        case S_CLEANING :
            if (digitalRead(DOOR)>0) {
              Serial.println("DOOR CLOSED");
              uvc(LOW);
              Serial.println("UVC CLEANING INTERRUPTED!");
              state = S_BUSY;
              Serial.println("Change to state S_BUSY");
              break;
            }
            if (digitalRead(PIR)>0) {
              Serial.println("PIR presence");
              uvc(LOW);
              Serial.println("UVC CLEANING INTERRUPTED!");
              state = S_BUSY;
              Serial.println("Change to state S_BUSY");
              break;
            }
            if ((unsigned long)(millis() - ts3) > t3){
               ts3=millis();
               Serial.println("T3_TIMEOUT");
               ts3 = millis();            
               Serial.println("RESET_T3");
               state = S_EMPTY_CLEAN;
               Serial.println("Change to state S_EMPTY_CLEAN");
               Serial.println("GREEN LED");
               digitalWrite(LED,1);
            }
            break;

        case S_EMPTY_CLEAN:
            if (digitalRead(PIR)>0) {
              Serial.println("PIR presence");
              state = S_SOMEONE_CLEAN;
              Serial.println("Change to state S_SOMEONE_CLEAN");
              ts1 = millis();            
              Serial.println("RESET_T1");
            }
            break;

        case S_SOMEONE_CLEAN:
            if ((unsigned long)(millis() - ts1) > t1){
               ts1=millis();
               Serial.println("T1_TIMEOUT");
               state = S_EMPTY_CLEAN;
               Serial.println("Change to state S_EMPTY_CLEAN");
               break;
            }
            if (digitalRead(DOOR)>0) {
              Serial.println("DOOR CLOSED");
              state = S_BUSY;
              Serial.println("Change to state S_BUSY");
              Serial.println("RED LED");
            }
            break;

        case S_BUSY:
            if (digitalRead(DOOR)<1) {
              Serial.println("DOOR OPEN");
              state = S_EMPTY_DIRTY;
              Serial.println("Change to state S_EMPTY_DIRTY");
              ts2 = millis();         
              Serial.println("RESET_T2");
            }
            break;

        default:
            Serial.print("Error state: ");
            Serial.println(state);
            break;
    }
}
