#include <ZumoMotors.h>
#include <SoftwareSerial.h>
#define LED_PIN 13

#define RxD 0    //receive data on digital 0
#define TxD 1 //transmit on digital 1

SoftwareSerial blueToothSerial(RxD, TxD);
ZumoMotors motors;

void setupBlueToothConnection(){
  blueToothSerial.begin(115200);
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as     "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  //blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
} 

int counter = 0;
int incoming;
int keyValue = 0;
void setup(void){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  pinMode(RxD,INPUT);
  pinMode(TxD,OUTPUT);
  setupBlueToothConnection();
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
}

void loop()
{
  // run left motor forward
  
  digitalWrite(LED_PIN, HIGH);
  

  if (blueToothSerial.available() > 0){
    keyValue =  blueToothSerial.read();
    if (keyValue == 65) //goes right
    {
         motors.setSpeeds(200,-200);
    }
    if (keyValue== 66)
    {
          motors.setSpeeds(-200,200);
  
    }
    if (keyValue== 67) // goes straight
    {
          motors.setSpeeds(200,200);
  
    }
    if (keyValue== 68) //goes  backward
    {
          motors.setSpeeds(-200,-200); 
    }
    if (keyValue== 69){
          motors.setSpeeds(0,0);                     
    }
  }
}

