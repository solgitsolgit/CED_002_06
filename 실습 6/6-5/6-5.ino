// ==== Lab6 Exp.5: HTTP server + LDR + LED ====
// Cytron ESPWiFi Shield 기반
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

// ----- 핀/임계값 -----
const int LED_PIN = 5;
const int LED_ON_THRESHOLD = 52;   // 주변 밝기에 맞춰 조정

// ----- path 파싱 -----
static String parsePathFromFirstLine(const String& firstLine) {
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
  Serial.println(wifi.status());

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
  client.readString();

  if (path.equals("/favicon.ico")) {
    client.print("HTTP/1.1 404 Not Found\r\n\r\n");
    client.stop();
    return;
  }

  // 조도 읽기
  int sensed_light = analogRead(A0);
  bool isBright = (sensed_light > LED_ON_THRESHOLD);

  // 색상 및 문구 설정
  const char* bgColor = isBright ? "#F0FFFF" : "#000000";
  const char* fontColor = isBright ? "#000000" : "#F0FFFF";
  const char* roomMsg = isBright ? "Room is currently BRIGHT" : "Room is currently DARK";

  // ====== 출력 시작 ======
  if (path.equals("/")) {
    client.print(htmlHeader);
    client.print("<body bgcolor=");
    client.print(bgColor);
    client.print("><font size=5 color=");
    client.print(fontColor);
    client.print(">");

    // --- 본문 ---
    client.print("CED 002, Group 06<br>");
    client.print("Room is currently ");
    client.print(isBright ? "BRIGHT" : "DARK");
    client.print("<br>");
    client.print("LDR value: ");
    client.print(sensed_light);
    client.print("<br><br>");

    // 링크
    client.print("<a href=./>REFRESH</a><br>");
    client.print("<a href=./on>ON</a><br>");
    client.print("<a href=./off>OFF</a><br><br>");

    client.print("</font></body></html>");
  }
  else if (path.equals("/on")) {
    digitalWrite(LED_PIN, HIGH);
    client.print(htmlHeader);
    client.print("<body bgcolor=");
    client.print(bgColor);
    client.print("><font size=5 color=");
    client.print(fontColor);
    client.print(">");
    client.print("CED 002, Group 06<br>");
    client.print("LED is ON<br>");
    client.print(roomMsg);
    client.print("<br>LDR value: ");
    client.print(sensed_light);
    client.print("<br><br>");
    client.print("<a href=./>REFRESH</a><br>");
    client.print("<a href=./off>OFF</a><br>");
    client.print("</font></body></html>");
  }
  else if (path.equals("/off")) {
    digitalWrite(LED_PIN, LOW);
    client.print(htmlHeader);
    client.print("<body bgcolor=");
    client.print(bgColor);
    client.print("><font size=5 color=");
    client.print(fontColor);
    client.print(">");
    client.print("CED 002, Group 06<br>");
    client.print("LED is OFF<br>");
    client.print(roomMsg);
    client.print("<br>LDR value: ");
    client.print(sensed_light);
    client.print("<br><br>");
    client.print("<a href=./>REFRESH</a><br>");
    client.print("<a href=./on>ON</a><br>");
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