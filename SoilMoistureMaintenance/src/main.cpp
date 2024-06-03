#include <Arduino.h>
#include <WiFiMulti.h>
#include <ESP32Servo.h>
#include <WebSocketsClient.h>

//wifi
#define ssid "Maddies2"
#define pass "YessP@ss41"

//websocket connections
#define WS_HOST ""
#define WS_PORT 443
#define WS_URL ""


WiFiMulti wifiMulti;
WebSocketsClient wsClient;

Servo myservo;  
int pos = 0;  
int servoPin = 4;
int soilPin = 35;

void handleWSMessage(){}

//function for websocket
void wsEvent(WStype_t type, uint8_t * payload, size_t length){
  switch(type){
    case WStype_CONNECTED: 
      Serial.println("WS Connected");
      break;
    case WStype_DISCONNECTED: 
      Serial.println("WS Disconnected");
      break;
    case WStype_TEXT: 
      Serial.printf("WS Message: %s\n", payload);


      break;
  }
}
void setup() {
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    
	myservo.attach(servoPin, 1000, 2000); 
  pinMode(soilPin, INPUT);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  wifiMulti.addAP(ssid, pass);
  Serial.println("starting...");

  //Wifi Connecting
  while (wifiMulti.run() != WL_CONNECTED){
    Serial.println(".");
    delay(100);
  }
  Serial.println("Connected");

  wsClient.beginSSL(WS_HOST, WS_PORT, WS_URL, "", "wss");

  wsClient.onEvent(wsEvent);
};



void loop() {

  //Show whether wifi is connected with LED
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  wsClient.loop();

  //Program for moisture maintenance
  int moisture = analogRead(soilPin);


  //convert moisture level to percentage
  float reverse = moisture/40.95;
  float percentage = 1-(reverse/100);


  //turn tap on if the moisture level is below set point
	if (moisture < 2000) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);          // waits 15ms for the servo to reach the position
    //Serial.print("Moisture at: " );
    Serial.println(reverse);
    Serial.println(moisture);


    //turn the tap off when the moisture passes the set point
	}	else if (moisture >= 2000) { // goes from 180 degrees to 0 degrees
		myservo.write(90);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
    Serial.println(reverse);
    Serial.println(moisture);
  }
  delay(1000);
digitalWrite(LED_BUILTIN, HIGH);
};