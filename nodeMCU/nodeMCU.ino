//#include <DHT.h>  // Including library for dht
//
//#include <ESP8266WiFi.h>
//
//String apiKey = "QLOLXAF6FB46RQ9X";     //  Enter your Write API key from ThingSpeak
//
//const char *ssid =  "Airtel-E5573-6F9D";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "8f41yjfq";
//const char* server = "api.thingspeak.com";
//
//#define DHTPIN D1
////pin where the dht11 is connected
//#define photocellpin A0
//
//DHT dht(DHTPIN, DHT11);
//
//WiFiClient client;
//
//void setup()
//{
//  Serial.begin(9600);
//  delay(10);
//  dht.begin();
//
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//
//
//  WiFi.begin(ssid, pass);
//
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//
//}
//
//void loop()
//{
//  delay(1000);
//  float h = dht.readHumidity();
//  delay(1000);
//  float t = dht.readTemperature();
//  delay(1000);
//  float photocellvalue = analogRead(photocellpin);
//  Serial.print("Light intensity value: ");
//  Serial.println(photocellvalue, DEC);
//  
//
//  if (isnan(h) || isnan(t))
//  {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
//
//  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
//  {
//
//    String postStr = apiKey;
//    postStr += "&field1=";
//    postStr += String(t);
//    postStr += "&field2=";
//    postStr += String(h);
//    postStr += "&field3=";
//    postStr += String(photocellvalue);
//    postStr += "\r\n\r\n";
//
//    client.print("POST /update HTTP/1.1\n");
//    client.print("Host: api.thingspeak.com\n");
//    client.print("Connection: close\n");
//    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
//    client.print("Content-Type: application/x-www-form-urlencoded\n");
//    client.print("Content-Length: ");
//    client.print(postStr.length());
//    client.print("\n\n");
//    client.print(postStr);
//
//    Serial.print("Temperature: ");
//    Serial.print(t);
//    Serial.print(" degrees Celcius, Humidity: ");
//    Serial.print(h);
//    Serial.println("%. Send to Thingspeak.");
//  }
//  client.stop();
//
//  Serial.println("Waiting...");
//  delay(20000);
//  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
//
//}
#include<SoftwareSerial.h>
#include <DHT.h>  // Including library for dht
 
#include <ESP8266WiFi.h>
 
String apiKey = "QLOLXAF6FB46RQ9X";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Airtel-E5573-6F9D";     // replace with your wifi ssid and wpa2 key
const char *pass =  "8f41yjfq";
const char* server = "api.thingspeak.com";
 
#define DHTPIN D1          //pin where the dht11 is connected
#define photocellpin A0
DHT dht(DHTPIN, DHT11);
SoftwareSerial myserial(D2,D3);
WiFiClient client;
 
void setup() 
{
      myserial.begin(9600);
       Serial.begin(9600);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
      String waterLevel=myserial.readStringUntil('\r');
      delay(1000);
      float h = dht.readHumidity();
      delay(1000);
      float t = dht.readTemperature()*100;
      delay(1000);
     int photocellvalue = analogRead(photocellpin);
     Serial.print("Light intensity value: ");
     Serial.println(photocellvalue, DEC);
     Serial.print("temp");
     Serial.println(t);
     Serial.print("humi");
     Serial.println(h);
     Serial.println(waterLevel);
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }   
                  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(photocellvalue);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);         
 }
