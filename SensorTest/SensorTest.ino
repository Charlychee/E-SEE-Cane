// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //
//

// Sensor #1 //
#define echoPin1 2 
#define trigPin1 3 

// Sensor #1 //
//#define echoPin1 4 
//#define trigPin1 5 


#define Noise1 4
#define Noise2 5
#define Noise3 6
#define Noise4 7

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(Noise1, OUTPUT);
    pinMode(Noise2, OUTPUT);
      pinMode(Noise3, OUTPUT);
        pinMode(Noise4, OUTPUT);
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT

  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  //logic
  if (distance < 25){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, HIGH);
  digitalWrite(Noise3, HIGH);
  digitalWrite(Noise4, HIGH);
  }
  
  else if (distance < 50){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, HIGH);
  digitalWrite(Noise3, HIGH);
  digitalWrite(Noise4, LOW);
  }
  
   else if (distance < 75){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, HIGH);
  digitalWrite(Noise3, LOW);
  digitalWrite(Noise4, LOW);
   }

    else if (distance < 100){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, LOW);
  digitalWrite(Noise3, LOW);
  digitalWrite(Noise4, LOW);
    }
    else {
  digitalWrite(Noise1, LOW);
  digitalWrite(Noise2, LOW);
  digitalWrite(Noise3, LOW);
  digitalWrite(Noise4, LOW);
    }
  
}
