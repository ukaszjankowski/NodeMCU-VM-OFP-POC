/*
 * NodeMCU Virtual machine & on the fly programming proof of concept
 * 
 * Copyright (c) 2016, Lukasz Jankowski
 * All rights reserved.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Ticker.h>

const char *ssid = "FunProvider";
const char *password = "thereisnospoon";

Ticker ticker;
ESP8266WebServer server(80);
String currentCode = "ewwdwwwwwwed";
int ip = 0;

void run()
{    
  if (ip >= currentCode.length())
    ip = 0;

  char currentOp = currentCode[ip];

  switch (currentOp) {
    case 'e':
      digitalWrite(2, 0);
      break;

    case 'd':
      digitalWrite(2, 1);
      break;

    case 'w':
      for (int i = 0; i < 10000; i++) {}
      break;
  }

  ip++;
}

void handleUpdate() {
  currentCode = server.arg("code");
  server.send(200, "text/html", "<h1>Code updated, watch me blinking n00b!</h1>");
}

void hc() {
    server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<h1>You will never be as awesome as microcontroller with a blue, blinking led!</h1>");
}

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  ticker.attach(0.3, hc);

	delay(1000);

	WiFi.softAP(ssid, password);

	server.on("/", handleRoot);
  server.on("/update", handleUpdate);
	server.begin();
}

void loop() {
  run();
}
