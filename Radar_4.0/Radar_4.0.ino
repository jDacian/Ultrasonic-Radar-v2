
#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  10       // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11       // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 150      // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define BAUD_RATE    115200   // Baud Rate of Serial
#define SERVO_PIN    8        // Set pin for Servo

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo servo;              
int increment = 1;            // increment to move for each interval

int distance;
int angle;

void setup() 
{
  Serial.begin(BAUD_RATE);  // Open serial monitor at 115200 baud to see ping results.
  servo.attach(SERVO_PIN);  
}

void loop() 
{
  updateServo();
  getDistance();
  printData();                    
 
  delay(30);
}

/******************************************************************************************
 * Gets The Approximate Distance from the Obstacle
 ******************************************************************************************/
void getDistace()
{
  distance = sonar.ping_cm();
}

/******************************************************************************************
 * Sends the data from the arduino to the processing app in the computer
 ******************************************************************************************/
void printData()
{
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print("."); 
}

/******************************************************************************************
 * Allows the servo motor to sweep and reverse upon reaching 180 degrees and 0 degrees
 ******************************************************************************************/
void updateServo()
{
  angle += increment;
  
  if ((angle >= 180) || (angle <= 0)) 
      {
        // reverse direction
        increment = -increment;
      }

  servo.write(angle);
}
