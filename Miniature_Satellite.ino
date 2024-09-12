#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>


SoftwareSerial gpsSerial(0,1);  

void setup() {
  Serial.begin(9600);  // Initialize Serial communication
  gpsSerial.begin(9600);  // Initialize GPS module communication

  Serial.println("==CubeSat TRACKING==");
}

void loop() {
  if (gpsSerial.available()) {
    char c = gpsSerial.read();

    // Look for the start of an NMEA sentence
    if (c == '$') {
      String sentence = gpsSerial.readStringUntil('\r');  // Read the entire NMEA sentence
      parseNmeaSentence(sentence); 
    }
  }
}

void parseNmeaSentence(String sentence) {
  
    if (sentence.startsWith("$GPGGA")) {
    
    String dataFields[15];
    int fieldIndex = 1;
    int startIndex = 8;  
    int endIndex = sentence.indexOf(',', startIndex);

    while (endIndex != -1) {
      dataFields[fieldIndex] = sentence.substring(startIndex, endIndex);
      startIndex = endIndex + 1;
      endIndex = sentence.indexOf(',', startIndex);
      fieldIndex++;
    }

    String time = dataFields[1];
    String lat = dataFields[2];
    String lng = dataFields[4];
    String altitude = dataFields[9];

    // Print the extracted information
    Serial.println("Time: " + time);
    Serial.println("Latitude: " + lat);
    Serial.println("Longitude: " + lng);
    Serial.println("Altitude: " + altitude);
    Serial.println();
  }
}
