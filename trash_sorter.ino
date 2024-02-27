const int inductive=2;
const int capacitive=3;
const int trigPin = 6;
const int echoPin = 7;
int Moisture_signal = A7;
long duration;
int distance;

int i = 0;

#include <Servo.h>

Servo tservo;
Servo binservo;

void setup() {
   pinMode(inductive, INPUT);
   pinMode(capacitive, INPUT);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   tservo.attach(4);
   binservo.attach(5);
   
   Serial.begin(9600);
   Serial.println("Running...");
}

void loop() {
 int moisture_method_call = moisture(Moisture_signal);
 int inductive_method_call = inductive_method(inductive);
 int capacitive_method_call = capacitive_method(capacitive);
 int dis_method_call = dis(trigPin, echoPin);

//  Serial.print("Moisture Percentage - ");
 Serial.println(moisture_method_call);
 Serial.println(dis_method_call);
//  Serial.print("Inductive Value - ");
//  Serial.println(inductive_method_call);
//  Serial.print("Capacitive Value - ");
//  Serial.println(capacitive_method_call);

    if(inductive_method_call == HIGH)
    {
      i += 1;
      Serial.println("METAL");
      binservo.write(0);
      delay(400); //315 degress
      binservo.write(90);
      delay(400);

      delay(500);

      tservo.write(180);
      delay(200);
      tservo.write(90);
      delay(200);

      delay(1000);

      tservo.write(0);

      delay(1000);

      tservo.write(180);
      delay(200);
      tservo.write(90);
      delay(200);

      binservo.write(0);
      delay(168); //315 degress
      binservo.write(90);
      delay(168);
    }
    else if(capacitive_method_call == HIGH)
    {
      i += 1;
      Serial.println("GLASS");
      binservo.write(0);
      delay(650); //158
      binservo.write(90);
      delay(650);

      delay(500);

      tservo.write(180);
      delay(200);
      tservo.write(90);
      delay(200);

      delay(1000);

      tservo.write(0);

      delay(1000);

      tservo.write(180);
      delay(200);
      tservo.write(90);
      delay(200);


      binservo.write(0);
      delay(580); //315 degress
      binservo.write(90);
      delay(580);

    }
    else if(moisture_method_call >= 20)
    {
      i += 1;
      Serial.println("ORGANIC");
      binservo.write(0);
      delay(300); //335 degress
      binservo.write(90);
      delay(300);

      delay(500);

      tservo.write(180);
      delay(200);
      tservo.write(90);
      delay(200);

      delay(1000);

      tservo.write(0);

      delay(1000);

      tservo.write(180);
      delay(200);
      tservo.write(90);
      delay(200);

      binservo.write(0);
      delay(250); //315 degress
      binservo.write(90);
      delay(250);
    }

 delay(200);
}

int moisture(int Moisture_signal){
 int Moisture = analogRead(Moisture_signal);
 int per = 101-(Moisture/10.23);
 return per;
}

int inductive_method(int inductive){
 int inductive_value = digitalRead(inductive);
 return inductive_value;
}

int capacitive_method(int capacitive){
 int capacitive_value = digitalRead(capacitive);
 return capacitive_value;
}

int dis(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}