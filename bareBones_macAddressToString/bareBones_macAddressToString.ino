// note mac address are far from perfect for this problem -- BUT will work since you have total control of the network
// UUIDs are better  -- we saw those in the BLE lib -- but implimentation maybe messy due to clock needs
// we can stick with MAC-address for now. 

// MAC is 48 bits -- much less that a UUID ( 128 ) 
// expanding them out seems wrong

//https://github.com/1337ninja/UUIDGenerator
//https://github.com/arduino-libraries/ArduinoBLE/issues/1

// this will give each band a unique ID based on network topology
// ID are no longer easily iterated in an array.
// on JS side you may need to stroe the bands in an array or object (?) depending on project needs.
// for size matching reasons I made broadcast ID = 999999999999  ( twelve nines) rather than 255

#include <WiFiNINA.h>
#include "netSecrets.h"

// some vars for holding char array conversions 
char myId[13];
char BROADCAST[13]="999999999999";  // array size needs to match size of myId
                   
char pseudoIncomingId[13] = "A4CF1285BF20"; // this is my device mac at my house

///////please enter your sensitive data in the netSecrets tab
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;

int wifiStatus = WL_IDLE_STATUS;     // the Wifi radio's status

byte mac[6];                     // the MAC address of your Wifi shield


void setup()
{
  // start serial
    Serial.begin(9600);
    while(!Serial);

  // connect to network
    connectToWifi();
  
  // getmyID -->convert mac address to char[] in hex
    if ( getMyId() == 1 )  { 
      Serial.print("myId ");
      Serial.println(myId);
    }
  
}

void loop () {

   // some conparisons to show you how it might be used
  
  // my network MAC / myId = A4CF1285BF20 --> yours will differ change here and above
  if(strcmp(myId, "A4CF1285BF20") == 0){ 
    Serial.println("myId == sd home mac (A4CF1285BF20)");
  } else {
    Serial.println("myId !=  sd home mac (A4CF1285BF20)");
  }

  if(strcmp(myId, pseudoIncomingId) == 0){
    Serial.println("myId == id of fake incoming message");
  }else {
    Serial.println("myId != preset ID");
  }

  // for demo only
  strcpy(myId, BROADCAST); 

  if(strcmp(myId, BROADCAST) == 0){
    Serial.println("got a message broadcast to all devices");
  }

while(1);
  
}

// this function converts teh byte array into a char[] so that 
// mac can be an ID
// compare against this the same way we parsed against message topics with MQTT

int getMyId(){
  int status = 0; 
  // should not get here unless connected to wifi
  if ( WiFi.status() == WL_CONNECTED){
    WiFi.macAddress(mac);
    sprintf(myId,"%02X%02X%02X%02X%02X%02X%c",mac[5],mac[4],mac[3],mac[2],mac[1],mac[0],'\0');
    status = 1; 
  }
  return status;

}



int connectToWifi(){
  int wifiAttempt = 0;
  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  wifiAttempt =1;
  Serial.println("You're connected to the network");
  Serial.println();

  return wifiAttempt;
}
