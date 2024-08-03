#define Relay D5
#define buzzer D6 // Assuming buzzer is connected to pin D6

#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "HF Electronotics 2.4Ghz"
#define WIFI_PASSWORD "HF@007219"
#define FIREBASE_HOST "piezo-project-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "8IAF9s6GhTjnGAZgZCOsfnyh1JEjVw9iigz2lvG1"

String tile1;
String tile2;
String tile3;

FirebaseData firebaseData;

void setup () {
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH); // Initially turn off relay
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW); // Initially turn off buzzer

  Serial.begin(9600);  // Initialize serial connection for debugging
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(500);
}

void loop () {
  //--------------------------------------------Tile1----------------------------------------
  if (Firebase.getString(firebaseData, "/Room/Tile1/Detection")) {
    tile1 = firebaseData.stringData();
    Serial.println(tile1);
    if (tile1 == "YES") {
//      digitalWrite(Relay, LOW); // Turn on Relay
//      Serial.println("Relay ON Due to Tile One");
//         delay(5000);
    }
  }
  //----------------------------------------Tile2-------------------------------------------------
  if (Firebase.getString(firebaseData, "/Room/Tile2/Detection")) {
    tile2 = firebaseData.stringData();
    Serial.println(tile2);
    if (tile2 == "YES") {
//      digitalWrite(Relay, LOW); // Turn on Relay
//       Serial.println("Relay ON Due to Tile TWO");
//          delay(5000);
    }
  }
  //-----------------------------------------------------------------------------------------------
  if (Firebase.getString(firebaseData, "/Room/Tile3/Detection")) {
    tile3 = firebaseData.stringData();
    Serial.println(tile3);
    if (tile3 == "YES") {
//      digitalWrite(Relay, LOW); // Turn on Relay
//       Serial.println("Relay ON Due to Tile Three");
//       delay(5000);
    }
  }

  // If none of the tiles have value "Yes", turn off the relay
  if (tile1 == "YES" || tile2 == "YES" || tile3 == "YES") {
    digitalWrite(Relay, LOW); // Turn on Relay
       Serial.println("Relay ON Due to Tile Three");
       delay(40000);
        digitalWrite(Relay, HIGH);// Turn off Relay
  }

  delay(1000); // Delay to avoid excessive readings
}
