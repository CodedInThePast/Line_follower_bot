#define LEFT_SENSOR A0
#define RIGHT_SENSOR A3
#define FRONT_SENSOR1 A1  
#define FRONT_SENSOR2 A2  

// L298N Motor Driver Pins
#define ENA 6  
#define IN1 7  
#define IN2 8  
#define ENB 9  
#define IN3 10 
#define IN4 11 

void setup() {
    Serial.begin(9600);

    pinMode(LEFT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);
    pinMode(FRONT_SENSOR1, INPUT);
    pinMode(FRONT_SENSOR2, INPUT);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

// Function to move forward
void moveForward(int speed) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

// Function to turn left
void turnLeft(int speed) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);  
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);   

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

// Function to turn right
void turnRight(int speed) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);   
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);  

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

// Function to stop motors
void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

}

void loop() {
    int left = analogRead(LEFT_SENSOR);
    int right = analogRead(RIGHT_SENSOR);
    int front1 = analogRead(FRONT_SENSOR1);  
    int front2 = analogRead(FRONT_SENSOR2);  
    
    Serial.println(left);

    int threshold = 500; 
    int speed = 70;  
    int speedturn = 80;
    String previousmove=" ";

    if ((left > threshold && right < threshold && front1 < threshold && front2 <threshold) || (left < threshold && right > threshold && front1 > threshold && front2 > threshold) ){
      turnLeft(speedturn);
      delay(50);
    }
   
    else if((left < threshold && right > threshold && front1 < threshold && front2 <threshold) || (left > threshold && right < threshold && front1 > threshold && front2 > threshold)||(left > threshold && right > threshold && front1 > threshold && front2>threshold)){
      turnRight(speedturn);
      delay(50);
    
    }else if((left < threshold && right < threshold && front1 > threshold && front2 > threshold) || (left > threshold && right > threshold && front1 < threshold && front2 < threshold)){
      moveForward(speed);
      delay(50);
    }else if (( left>threshold && front1 > threshold && front2<threshold && right <threshold) || ( left<threshold && front1 < threshold && front2 > threshold && right > threshold)){
      moveForward(speed);
      delay(50);
    }
    else if ((front1 < threshold && front2 < threshold && left < threshold && right < threshold)) {
        if (previousmove== "right"){
          turnLeft(speedturn);
          delay(50);
        }else if(previousmove== "left"){
          turnRight(speedturn);
          delay(50);
        }
    }
      else{
          moveForward(speed);
          delay(50);
      }

}
