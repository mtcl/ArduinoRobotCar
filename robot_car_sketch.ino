
#define leftMotorPin 12 //Pin number for left Motor
#define leftMotorPinAna 3 //Pin number for left analog control
#define leftMotorPinStop 9 //Pin number for left Motor stop

#define rightMotorPin 13 //Pin number for right Motor
#define rightMotorPinAna 11 //Pin number for right analog control
#define rightMotorPinStop 8 //Pin number for right Motor stop

#define trigPin 2
#define echoPin 4

#define minObjDistInch 6 //set minimum object distance before collision happens
#define scanInterval 100 //scan interval for ultrasonic sensor in 1/1000 of a seconds

long duration, cm, inches;

void setup() {

  pinMode(leftMotorPin,OUTPUT);
  pinMode(leftMotorPinAna,OUTPUT);
  pinMode(leftMotorPinStop,OUTPUT);
  
  pinMode(rightMotorPin,OUTPUT);
  pinMode(rightMotorPinAna,OUTPUT);
  pinMode(rightMotorPinStop,OUTPUT);
  
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
	
	digitalWrite(leftMotorPinStop,LOW);
	digitalWrite(leftMotorPin,HIGH);
	digitalWrite(leftMotorPinAna,250);
	
	digitalWrite(rightMotorPinStop,LOW);
	digitalWrite(rightMotorPin, HIGH);
	digitalWrite(rightMotorPinAna, 250);
	
}

void goBackward(){
	
	digitalWrite(leftMotorPinStop,LOW);
	digitalWrite(leftMotorPin,LOW);
	digitalWrite(leftMotorPinAna,150);
	
	digitalWrite(rightMotorPinStop,LOW);
	digitalWrite(rightMotorPin, LOW);
	digitalWrite(rightMotorPinAna, 150);
	
}

void turnLeft(){
	
	digitalWrite(leftMotorPin,HIGH);
	digitalWrite(leftMotorPinAna,250);
	digitalWrite(leftMotorPinStop,LOW);
  
	digitalWrite(rightMotorPinStop,HIGH);
}

void turnRight(){
	
	digitalWrite(leftMotorPinStop,HIGH);
  
	digitalWrite(rightMotorPin, HIGH);
	digitalWrite(rightMotorPinAna, 250);
	digitalWrite(rightMotorPinStop,LOW);
}

void comeToStop(){
	
	digitalWrite(leftMotorPinStop,HIGH);
	digitalWrite(rightMotorPinStop,HIGH);  
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
