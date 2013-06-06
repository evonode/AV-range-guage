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

long interval = 75;
long hinterval = 100;
long modhinterval = 0;
long linterval = 10;
long modlinterval =0;

int ledgraph[]={2,3,4,5,6,7};
long maxping=0;
int numofled=6;
int ledrange;
int howmanyledstolight=0;
int segment = 0;
int dblseg = 0;
int i =0;
int gate = 1;
int currentled = 0;
int previousled=9;


unsigned int uS;

//sound variables
//none


void setup() {
  for(int s =0;s<6;s++){
    pinMode(ledgraph[s],OUTPUT);  
  }
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  //sound pin
  pinMode(8, OUTPUT); 

}

void loop() {
  unsigned long currentMillis = millis();

    
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      //delay(75);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings. default 50
      uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      Serial.print(uS);
      Serial.print(" Ping: ");
      Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
      Serial.println("cm");
      if (uS > maxping){
        maxping = uS;
        //ledrange = maxping/numofled;
        segment=maxping;//63;
      }
      
      dblseg=segment;
      howmanyledstolight = 0;
      i=numofled;
      
      while ((uS<dblseg)&&(howmanyledstolight<numofled)){
        dblseg=dblseg/2;
        howmanyledstolight++;
        i--;
      }
  
  
      if(uS==0){
        howmanyledstolight = 0;
      }
  
      Serial.print(maxping);
      Serial.print(" leds to light: ");
      Serial.print(howmanyledstolight);
      Serial.print(" at ");
      Serial.print(dblseg);
      Serial.println(" segment lght");
      currentled=howmanyledstolight;
      
  
      for(int c =0;c<6;c++){
        digitalWrite(ledgraph[c],LOW);  
      }
  
      for (int d=0;d<howmanyledstolight;d++){
        digitalWrite(ledgraph[d],HIGH);
      
 
  
      }
   
     
    }
    
    
    
    
     
   modhinterval = i*hinterval;

    
     //Stuff for sound
  if (currentled != previousled){
          Serial.println("inside currentled.");
    previousled=currentled;
    modlinterval= linterval;
    previoushighmillis = currentMillis;
    digitalWrite(8, HIGH);
    gate = 1;
  }
  
  if(currentMillis - previouslowmillis > modlinterval && gate == 0 && howmanyledstolight>0){
          Serial.println("inside gate 0");
    previoushighmillis=currentMillis;
    gate=1;
    digitalWrite(8, HIGH);
  }
  
  if(currentMillis - previoushighmillis > modhinterval && gate == 1 && howmanyledstolight>0){
          Serial.println("inside gate 1");
    previouslowmillis=currentMillis;
    gate=0;
    digitalWrite(8, LOW);
  }
  


  //end of stuff for sound
      
    
}
    
  
  







