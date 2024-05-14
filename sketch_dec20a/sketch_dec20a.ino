#include <ESP32Servo.h>
Servo myservo;  
int pos = 0;  
int servoPin = 4;
int soilPin = 35;
void setup() {
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    
	myservo.attach(servoPin, 1000, 2000); 
  pinMode(soilPin, INPUT);
  Serial.begin(115200);

};
void loop() {
  int moisture = analogRead(soilPin);
  //int percentage = 100 - (moisture * 100 / 4095);
  float reverse = moisture/40.95;
  float percentage = 1-(reverse/100);
	if (moisture < 2000) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);          // waits 15ms for the servo to reach the position
    //Serial.print("Moisture at: " );
    Serial.println(reverse);
    Serial.println(moisture);
	}	else if (moisture >= 2000) { // goes from 180 degrees to 0 degrees
		myservo.write(90);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
    Serial.println(reverse);
    Serial.println(moisture);
  }
  delay(1000);
};
