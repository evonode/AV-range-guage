//#include <NewPing.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.default 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


long previousMillis = 0;
long previoushighmillis =0;
long previouslowmillis = 0;

long interval = 75;//wait between pings
long hinterval = 20;//High interval
long maxhinterval=140;
long modhinterval = 0;//High interval after any modifications
long linterval = 10;//Low interval
long modlinterval =0;//Low interval after any modifications
long maxlinterval=70;

int ledgraph[]={2,3,4,5,6,7};//pin array of LED positons 2 starting the green 
long maxping=0;//variable to capture the greatest ping distance 
int numofled=6;
int ledrange;
int howmanyledstolight=0;
//int segment = 0;
int dblseg = 0;
int i =0;
int gate = 1;//variable for either a 1 or 0.
int currentled = 0;
int previousled=9;//made high on purpose.  will change on first go through of code.

unsigned int uS;

//sound variables
//none


void setup() {
  
  //set led pin array to output
  for(int s =0;s<6;s++){
    pinMode(ledgraph[s],OUTPUT);  
  }
  
  Serial.begin(115200); // Open serial monitor at 115200 baud to see results in monitor.
  //set sound pin
  pinMode(8, OUTPUT); 

}

void loop() {
  //get current millis and put it in currentMillis
  unsigned long currentMillis = millis();
 
    //check to see if ping interval is reached
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings. default 50
      uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      //if you open your Arduino monitor - ctrl+shift+m you will get feedback.
      /*
      Serial.print(uS);
      Serial.print(" Ping: ");
      Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
      Serial.println("cm");
      */
      if (uS > maxping){
        maxping = uS;
        //segment=maxping;
      }
      
      dblseg=maxping;//segment;
      howmanyledstolight = 0;//Intialize to 0
      i=numofled;
      
      //this will count how many LEDs to light modifying the distance/2 each time
      while ((uS<dblseg)&&(howmanyledstolight<numofled)){
        dblseg=dblseg/2;
        howmanyledstolight++;
        i--;
      }
      //if uS is pointing at something to far away its value is 0 
      //I do not want the LEDs to light at all if something is to far away.
      if(uS==0){
        howmanyledstolight = 0;
      }
      //more output to monitor
      
      /*Serial.print(maxping);
      Serial.print(" leds to light: ");
      Serial.print(howmanyledstolight);
      Serial.print(" at ");
      Serial.print(dblseg);
      Serial.println(" segment lght");
    */
      
        //Turn off every led.  
        for(int c =0;c<6;c++){
          digitalWrite(ledgraph[c],LOW);  
        }
        
        //Turn on only the correct amount of LEDs  
        for (int d=0;d<howmanyledstolight;d++){
          digitalWrite(ledgraph[d],HIGH);
        }
        currentled=howmanyledstolight;
   }
    
    
    
     //Stuff for sound
  if (currentled != previousled){

    previousled=currentled;
    modhinterval=maxhinterval-(hinterval*howmanyledstolight);
    modlinterval=maxlinterval-(linterval*howmanyledstolight);
    previoushighmillis = currentMillis;
    digitalWrite(8, HIGH);
    gate = 1;
  }
  
  if(currentMillis - previouslowmillis > modlinterval && gate == 0 && howmanyledstolight>0){      
    Serial.println("inside gate 0");
              //More output to monitor
          Serial.print(modhinterval);
          Serial.print(" and the low is ");
          Serial.println(modlinterval);
    previoushighmillis=currentMillis;
    gate=1;
    digitalWrite(8, HIGH);
  }
  
  if(currentMillis - previoushighmillis > modhinterval && gate == 1 && howmanyledstolight>0){
          Serial.println("inside gate 1");
                    //More output to monitor
          Serial.print(modhinterval);
          Serial.print(" and the low is ");
          Serial.println(modlinterval);
    previouslowmillis=currentMillis;
    gate=0;
    digitalWrite(8, LOW);
  }
  //end of stuff for sound
}
    
  
  







