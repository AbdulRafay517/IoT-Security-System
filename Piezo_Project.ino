#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h> 
FirebaseData firebaseData;
FirebaseData firebaseData1;
FirebaseData firebaseData2;
//char auth[] = "WS_mxfsveWdAUDRqeH8DxCVfXfEHJ6vv";
#define FIREBASE_HOST "piezo-project-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "8IAF9s6GhTjnGAZgZCOsfnyh1JEjVw9iigz2lvG1"
const char* ssid = "HF Electronotics 2.4Ghz"; //Wifi Name SSID
const char* password = "HF@007219"; //WIFI Passwor
#define buzzer 33
#include "time.h"
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 18000;
void setup() {

  Serial.begin(9600);
   WiFi.begin(ssid, password);
     pinMode(buzzer, OUTPUT);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  digitalWrite(buzzer, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(buzzer, LOW);    // turn the LED off by making the voltage LOW             
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(500);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
}

void loop() {
  //-------------------------------------------Time-Get------------------------------------------------
   struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  
  char formattedTime[20]; // Define a character array to store the formatted time

  // Format the time and store it in the formattedTime array
  strftime(formattedTime, sizeof(formattedTime), "%b %d %Y %H:%M:%S", &timeinfo);

  // Print the formatted time
//  Serial.println(formattedTime);

    //-------------------------------------------------------------------------------------------------
  int sensorValue1 = analogRead(34);
Serial.print("Sensor Value1: ");
Serial.println(sensorValue1);
delay(1);    

int sensorValue2 = analogRead(39);
Serial.print("Sensor Value2: ");
Serial.println(sensorValue2);
delay(1);  

int sensorValue3 = analogRead(36);
Serial.print("Sensor Value3: ");
Serial.println(sensorValue3);
 Firebase.setInt(firebaseData,"/Room/Tile1/Sensor Value", sensorValue1);
  Firebase.setInt(firebaseData,"/Room/Tile2/Sensor Value", sensorValue2);
   Firebase.setInt(firebaseData,"/Room/Tile3/Sensor Value", sensorValue3);
 
  //----------------------------------------Tile_1------------------------------------------------------
  
      if(sensorValue1>0 && sensorValue1<2000){
     Firebase.setString(firebaseData,"/Room/Tile1/Detection", "NO");

      }
      if(sensorValue1>2000){
     Firebase.setString(firebaseData,"/Room/Tile1/Detection", "YES");
     delay(1000);
      Firebase.setString(firebaseData,"/Room/Tile1/Time", formattedTime);
      digitalWrite(buzzer, HIGH);  
     delay(2000);                    
      digitalWrite(buzzer, LOW);    
      sensorValue2=0;
      sensorValue3=0;      

      }
      //-------------------------------------------------------------------------------------------------
       //----------------------------------------Tile_2------------------------------------------------------
  
      if(sensorValue2>0 && sensorValue2<2000){
     Firebase.setString(firebaseData,"/Room/Tile2/Detection", "NO");

      }
      if(sensorValue2>2000){
     Firebase.setString(firebaseData,"/Room/Tile2/Detection", "YES");
     delay(1000);
      Firebase.setString(firebaseData,"/Room/Tile2/Time", formattedTime);
      digitalWrite(buzzer, HIGH);  
     delay(2000);                    
      digitalWrite(buzzer, LOW);    
       sensorValue1=0;
      sensorValue3=0;        

for (int i = 0; i < 2; i++) { // Loop 4 times
    digitalWrite(buzzer, HIGH); // Turn the buzzer on
    delay(500); // Wait for 500 milliseconds (half a second)
    digitalWrite(buzzer, LOW); // Turn the buzzer off
    delay(500); // Wait for 500 milliseconds (half a second)
  }

      }
      //-------------------------------------------------------------------------------------------------
       //----------------------------------------Tile_3------------------------------------------------------
  
      if(sensorValue3>0 && sensorValue3<2000){
     Firebase.setString(firebaseData,"/Room/Tile3/Detection", "NO");

      }
      if(sensorValue3>2000){
     Firebase.setString(firebaseData,"/Room/Tile3/Detection", "YES");
     delay(1000);
      Firebase.setString(firebaseData,"/Room/Tile3/Time", formattedTime);
        sensorValue1=0;
        sensorValue2=0;   
      for (int i = 0; i < 3; i++) { // Loop 4 times
    digitalWrite(buzzer, HIGH); // Turn the buzzer on
    delay(500); // Wait for 500 milliseconds (half a second)
    digitalWrite(buzzer, LOW); // Turn the buzzer off
    delay(500); // Wait for 500 milliseconds (half a second)
  }

      }
      //-------------------------------------------------------------------------------------------------
      
      
}
