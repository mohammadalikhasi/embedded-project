#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <string.h>

const char* ssid = "Galaxy A34 5G EA6D";
const char* password = "1273776690";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.65.170:5000";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 3000;

void wifi_setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void wifi_POST(int type,int timeout_seconds) {

  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      client.setTimeout(timeout_seconds * 1000);

      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "type=";     

      Serial.println(httpRequestData);

            

      switch (type){
        case 1 : httpRequestData += "1" ;
        break;
        case 2 : httpRequestData += "2" ;
        break;
        case 3 : httpRequestData += "3" ;
        break;
        case 4 : httpRequestData += "4" ;
        break;

      }
      
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void setup() {
  wifi_setup();
  Serial.begin(115200);
}

void loop() {
  // get_date();
  if (Serial.available()) {
    char data = Serial.read();
    if (data == '1'){
        wifi_POST(1,10);
    }
    if (data == '2'){
        wifi_POST(2,10);
    }
    if (data == '3'){
        wifi_POST(3,10);
    }
    if (data == '4'){
        wifi_POST(4,10);
    }
    // Serial.write(Serial.read());
    Serial.println(data);

  }

  //Send an HTTP POST request every 10 minutes
  
}
