// ==== Lab6 Exp.5: HTTP server + LDR + LED ====
#include <CytronWiFiShield.h>
#include <CytronWiFiClient.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>

const char *ssid = "No.3";
const char *pass = "testtest";
ESP8266Server server(80);

// ----- HTML 헤더 -----
const char htmlHeader[] =
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Connection: close\r\n\r\n"
  "<!DOCTYPE HTML>\r\n"
  "<html>\r\n";

// ----- 핀/임계값 (LED_PIN=2, TH=500) -----
const int LED_PIN = 2;
const int LED_ON_THRESHOLD = 500;   // 주변 밝기에 맞춰 조정

// 디버그에 도움
static String parsePathFromFirstLine(const String& firstLine) {
  // "GET /path HTTP/1.1" -> "/path"
  int s = firstLine.indexOf(' ');
  int e = (s >= 0) ? firstLine.indexOf(' ', s + 1) : -1;
  if (s < 0 || e < 0) return "/";
  return firstLine.substring(s + 1, e);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  if (!wifi.begin(2, 3)) {
    Serial.println(F("Error talking to shield"));
    while (1);
  }
  Serial.println(wifi.firmwareVersion());
  Serial.print(F("Mode: ")); Serial.println(wifi.getMode());

  Serial.println(F("Start wifi connection"));
  if (!wifi.connectAP(ssid, pass)) {
    Serial.println(F("Error connecting to WiFi"));
    while (1);
  }
  Serial.print(F("Connected to ")); Serial.println(wifi.SSID());
  Serial.println(F("IP address: ")); Serial.println(wifi.localIP());
  wifi.updateStatus();
  Serial.println(wifi.status()); // 2~5

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  server.begin();
}

void loop() {
  serverTest();
}

void serverTest() {
  ESP8266Client client = server.available();
  if (client.available() <= 0) return;

  String req = client.readStringUntil('\r');
  String path = parsePathFromFirstLine(req);
  Serial.print(F("Request: ")); Serial.println(path);
  client.flush();

  if (path.equals("/favicon.ico")) {
    client.print("HTTP/1.1 404 Not Found\r\n\r\n");
    client.stop();
    return;
  }

  // 조도 읽기(A0)
  int sensed_light = analogRead(A0);

  // 출력
  if (path.equals("/")) {
    client.print(htmlHeader);

    if (sensed_light > LED_ON_THRESHOLD) {
      client.print("<body bgcolor=#F0FFFF>");
      client.print("<font size=5 color=#000000>");
      client.print("Room is currently BRIGHT");
      client.print("<br>");
    } else {
      client.print("<body bgcolor=#000000>");
      client.print("<font size=5 color=#F0FFFF>");
      client.print("Room is currently DARK");
      client.print("<br>");
    }

    client.print("LDR value: ");
    client.print(sensed_light);
    client.print("<br>");

    client.print("<a href=./>");   // home
    client.print("REFRESH");
    client.print("</a>");
    client.print("<br>");

    client.print("<a href=./on>"); // on
    client.print("ON");
    client.print("</a>");
    client.print("<br>");

    client.print("<a href=./off>"); // off
    client.print("OFF");
    client.print("</a>");
    client.print("<br>");
    client.print("<br>");

    client.print("</font>");
    client.print("</body>");
    client.print("</html>");
  }
  else if (path.equals("/on")) {
    client.print(htmlHeader);
    client.print("<body><font size=5>");
    client.print("LED is ON");
    digitalWrite(LED_PIN, HIGH);
    client.print("</font></body></html>");
  }
  else if (path.equals("/off")) {
    client.print(htmlHeader);
    client.print("<body><font size=5>");
    client.print("LED is OFF");
    digitalWrite(LED_PIN, LOW);
    client.print("</font></body></html>");
  }
  else {
    client.print("HTTP/1.1 404 Not Found\r\n\r\n");
  }

  // 디버그
  Serial.print(F("LDR=")); Serial.print(sensed_light);
  Serial.print(F("  LED=")); Serial.println(digitalRead(LED_PIN) ? F("ON") : F("OFF"));

  client.stop();
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환