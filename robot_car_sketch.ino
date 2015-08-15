
#define leftMotorPin1 9 //Pin number for left Motor
#define leftMotorPin2 8 //Pin number for left Motor

#define rightMotorPin1 13 // Pin number for right Motor
#define rightMotorPin2 12 // Pin number for right Motor


#define trigPin 2
#define echoPin 4

#define minObjDistInch 6 //set minimum object distance before collision happens
#define scanInterval 100 //scan interval for ultrasonic sensor in 1/1000 of a seconds

long duration, cm, inches;

void setup() {

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //built in 3 seconds delay to power on the Car.
  delay(3000);
}

void loop()
{
  //sets both motors to full speed in the same direction
  goForward();
   
  //every scanInterval mili seconds, check for distance in inches
  inches = distanceIn();
  delay(scanInterval);

  //Check for obstacles
  if (inches < minObjDistInch) {
    //stops both motors
    comeToStop();
    delay(1000);
  
    //sets both motors to full speed in opposite direction
    goBackward();
    delay(1000);

    //sets only the left motor to rotate so the robot turns
    turnRight();
    delay(1500);
    
  }//end if statement
  
}//ends loop

void goForward(){
  digitalWrite(leftMotorPin1,HIGH);
  digitalWrite(leftMotorPin2,LOW);
  
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void goBackward(){
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void turnLeft(){
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);

  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void turnRight(){
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void comeToStop(){
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);  
}

int distanceIn(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(4);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // converts the time to a distance
  inches = (duration / 2) / 74;
  return inches;
}
