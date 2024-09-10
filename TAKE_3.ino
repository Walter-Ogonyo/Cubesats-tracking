#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(4, 3); 

TinyGPSPlus gps; 

void setup() {
  Serial.begin(9600);         
  gpsSerial.begin(9600);      

  Serial.println("==CubeSat TRACKING==");
}

void loop() {
  
  while (gpsSerial.available() > 0)
    gps.encode(gpsSerial.read()); 
    
         if (gps.location.isUpdated()) {
          
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
        
        Serial.print("Altitude: ");
        Serial.println(gps.altitude.meters());
      }

        if (millis() > 5000 && gps.charsProcessed() < 10)
{
  Serial.println("ERROR: not getting any GPS data!");
  
  Serial.println("GPS stream dump:");
  while (true) // infinite loop
    if (gpsSerial.available() > 0)
      Serial.write(gpsSerial.read());
}
  }
  

  
