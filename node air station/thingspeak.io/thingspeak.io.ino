/* This arduino code is sending data to thingspeak server every 30 seconds.

Created By Embedotronics Technologies*/

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>

#define DHTPIN D2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


float humidityData;
float temperatureData;
float hic;


const char* ssid = "farafir";// 
const char* password = "8psmZZ3dkw";
//WiFiClient client;
char server[] = "api.thingspeak.com";   //eg: 192.168.0.222


WiFiClient client;    


void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ 
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  // Compute heat index in Celsius (isFahreheit = false)
  hic = dht.computeHeatIndex(temperatureData, humidityData, false);
  
  Sending_To_thingspeak(); 
  delay(60000); // interval
 }

 void Sending_To_thingspeak()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /update?api_key=8NLHT145IXB2M3FC&field1=0");
    client.print("GET /update?api_key=8NLHT145IXB2M3FC&field1=0");     //YOUR URL
    Serial.println(temperatureData);
    client.print(temperatureData);
    client.print("&field2=");
    Serial.println("&field2=");
    client.print(humidityData);
    Serial.println(humidityData);

    client.print("&field3=");
    Serial.println("&field3=");
    client.print(hic);
    Serial.println(hic);
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
