#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
 
const char* ssid = "Aditya";
const char* password =  "12345678";
  
AsyncWebServer server(80);
AsyncWebSocket ws("/chat");
  
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  
  if(type == WS_EVT_CONNECT){
  
    Serial.println("Websocket client connection received");
     
  } else if(type == WS_EVT_DISCONNECT){
 
    Serial.println("Client disconnected");
  
  } else if(type == WS_EVT_DATA){
  
    ws.textAll(data, len);
 
    Serial.print("Data received: ");
  
    for(int i=0; i < len; i++) {
          Serial.print((char) data[i]);
    }
  
    Serial.println();
  }
}
  
void setup(){
  Serial.begin(115200);
  
  if(!SPIFFS.begin()){
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }
 
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());
  
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
 
  server.on("/chat", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/chat.html", "text/html");
  });
  
  server.on("/chat.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/chat.js", "text/javascript");
  });

  server.on("/chat.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/chat.css", "text/css");
    });
 
  server.begin();
}
  
void loop(){}
