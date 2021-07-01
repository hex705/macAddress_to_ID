// note mac address are far from perfect for this problem -- BUT will work since you have total control of the network
// UUIDs are better  -- we saw those in the BLE lib -- but implimentation maybe messy due to clock needs
// we can stick with MAC-address for now. 

// MAC is 48 bits -- much less that a UUID ( 128 ) 
// expanding them out seems wrong
// https://github.com/1337ninja/UUIDGenerator
//https://github.com/arduino-libraries/ArduinoBLE/issues/1

#include <WiFiNINA.h>
#include "netSecrets.h"

// some vars for holding char array conversions 
char myId[13];
char myId_hex[13]; // hex keeps it at 12 bytes +1 for \0 - double check this
char myId_dec[13]; // hex keeps it at 12 bytes +1 for \0 - double check this
char BROADCAST[]="255";
char pseudoIncomingId[] = "A4CF1285BF20";

// some vars for holding string converstion 
String myId_DEC_String;
String myId_HEX_String;
String temp ;

///////please enter your sensitive data in the netSecrets tab
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;

int status = WL_IDLE_STATUS;     // the Wifi radio's status

byte mac[6];                     // the MAC address of your Wifi shield


void setup()
{
 Serial.begin(9600);
 while(!Serial);

  connectToWifi();
  WiFi.macAddress(mac); // note this is the WiFi object (WiFi) -- not your client!

  printManyWays(); // so many ways to convert the mac address 

  if ( getMyId() == 1 )  {; // gets ID as char array in HEX
    Serial.print("myId ");
    Serial.println(myId);
  }
  
}

void loop () {
  // my network MAC / myId = A4CF1285BF20;
  if(strcmp(myId, "A4CF1285BF20") == 0){
    Serial.println("myId == expected (A4CF1285BF20)");
  }

  if(strcmp(myId, pseudoIncomingId) == 0){
    Serial.println("myId == id of fake incoming message");
  }

while(1);
  
}

// this function converts the byte array into a char[] so that 
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

void printManyWays(){
   // show mac in hex
  Serial.print("1) MAC address raw (hex) ::          ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  
  // https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
  // show mac address once inside char array 
  Serial.print("2) MAC Address IN hex -- char[] ::   ");
  sprintf(myId_hex,"%02X%02X%02X%02X%02X%02X%c",mac[5],mac[4],mac[3],mac[2],mac[1],mac[0],'\0');
  Serial.println(myId_hex);

  // convert to string HEXidecimal format
  for (int i = 5; i >=0; i--){
   temp = String(mac[i],HEX);
   myId_HEX_String += temp; // mac[5]+mac[4]+mac[3]+mac[2]+mac[1]+mac[0];
  }
   Serial.print("3) MAC address HEXidecimal string :: " );
   Serial.println(myId_HEX_String);

  // show the mac address again in decimal 
  Serial.print("\n\n4) MAC (dec) ::                      ");
  Serial.print(mac[5],DEC);
  Serial.print(":");
  Serial.print(mac[4],DEC);
  Serial.print(":");
  Serial.print(mac[3],DEC);
  Serial.print(":");
  Serial.print(mac[2],DEC);
  Serial.print(":");
  Serial.print(mac[1],DEC);
  Serial.print(":");
  Serial.println(mac[0],DEC);

  // show MAC address in decimal 
  Serial.print("5) MAC Address IN decimal-- char[] ::"); 
  sprintf(myId_dec,"%i%i%i%i%i%i%c",mac[5],mac[4],mac[3],mac[2],mac[1],mac[0],'\0');
  Serial.println(myId_dec);

  // convert MAC to string decimal format
  for (int j = 5; j >=0; j--){
   temp = String(mac[j],DEC);
   myId_DEC_String += temp; // mac[5]+mac[4]+mac[3]+mac[2]+mac[1]+mac[0];
  }
  Serial.print("6) Mac address decimal -- String ::  ");
  Serial.println(myId_DEC_String);

  Serial.println("\n\nPrint Many Ways is Done");

}
