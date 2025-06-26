const int greenPin = 2;
const int yellowPin = 3;
const int redPin = 4;
const int trig = 10;
const int echo = 11;
long duration;
long distance;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

  int x = getSpeed();
  
  if(x > 20){
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    Serial.println("SLOW DOWN");
  }

  else if(x > 10){
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    Serial.println("Careful");
  }

  else{
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
    Serial.println("Good");
  }

  delay(200);
  

}

long getDistance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  //amount of time trigger needs to stay on to release ultrasonic wave is 10 microseconds
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  //measures the amount of time the echoPin stays high (time from when the ultrasonic wave was emitted, to when echo hits receiver), if no signal is received in 30000 ms call is cancelled
  duration = pulseIn(echo, HIGH, 30000);

  if(duration == 0){
    Serial.println("No Echo Received");
    return 0;
  }


  //sound = 0.034 centimeters per microsecond. sound multiplied by duration in microseconds gives distance in centimeters from sensor to object x2
  distance = duration * .034/2;

  return distance;
}

int getSpeed(){

  int distance1 = getDistance();
  delay(100);
  int distance2 = getDistance();

  int distance = abs(distance2 - distance1);

  int velocity = distance/0.1;

  return velocity;
  
}
