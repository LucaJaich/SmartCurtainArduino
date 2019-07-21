#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int led = 12;

ESP8266WebServer server;

char* ssid = "Fibertel Wifi";
char* passwd = "0142296360";

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.begin(115200);
  WiFi.begin(ssid, passwd);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Adress: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200, "text/plain", "hello world");});
  server.on("/led", setLed);
  server.on("/servo", setServo);
  server.begin();
}

void setLed() {
   String data = server.arg("plain");
   StaticJsonDocument<200> jDocument;
   auto error = deserializeJson(jDocument, data);
   Serial.println(data);
   if (error) {
    Serial.print("Error deserailizing: ");
    Serial.println(error.c_str());
    return;
   }
   String state = jDocument["state"];
   Serial.println(state);
   digitalWrite(led, state.toInt());
   server.send(200, "text/plain", "Led updated correctly");
}

void serServo() {
  String data = server.arg("plain");
  StaticJsonDocument<200> jDocument;
  auto error = deserializeJson(jDocument, data);
  Serial.println(data);
  if (error) {
    Serial.print("Error deserailizing: ");
    Serial.println(error.c_str());
  return;
  String dir = jDocument["dir"];
  Serial.println(dir);
 }
}

void loop() {
  server.handleClient();
}

