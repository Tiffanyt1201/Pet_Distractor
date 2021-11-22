#include <Servo.h>

Servo ser;

// Defining digital pins for servo 
int serPin = 8;
int pos = 0;

// Defining digital pins for ultrasonic sensor 
const int trigPin = 5; 
const int echoPin = 6; 

// Initializing variables for ultrasonic sensor distance 
long duration; 
int distance; 

// Initializing variable for time servo has run after activation
int timer = 0;

// Initializing variables for detecting if servo has been triggered
bool triggered = false;
bool on = false;

/**
 * Setup Code (run once)
 */
void setup() {
  //Setup for ultrasonic sensor 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  Serial.begin(9600);

  //Setup for servo 
  ser.attach(serPin);
  ser.write(pos);
}

/**
 * Main Code (to run repeatedly)
 */
void loop() {
  // Delay of servo 
  delay(500);
  
  digitalWrite(trigPin, LOW); 
  delay(2); 
  digitalWrite(trigPin, HIGH); 
  delay(10); 
  digitalWrite(trigPin, LOW); 

  // Calculating the distance between object and ultrasonic sensor 
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 /2; 
  
  // Object is within a certain distance and servo has NOT already been triggered 
  if(distance < 15 && triggered == false){
    triggered = true;
  } else{
    triggered = false;
  }
  
  // Trigger is set to true and servo has not already been turned on 
  if(triggered && on == false){
    on = true;
    timer = 0;
    //Serial.println("I'm here");
  }

  // Turn on servo and start timer 
  if(on){
    timer ++;
    ser.write(pos);
    if(pos == 0)
     pos = 180; 
    else
      pos = 0; 
  }

  // turn off servo after 100 seconds 
  if(timer >= 200){
    on = false;
    timer = 0;
  }
  
}
