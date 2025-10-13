#include <CytronWiFiShield.h>
#include <CytronWiFiClient.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>

// 테더링 설정
const char *ssid = "Taehyun"; 
const char *pass = "12344321"; 
ESP8266Server server(80);

const char htmlHeader[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Connection: close\r\n\r\n"
                        "<!DOCTYPE HTML>\r\n"
                        "<html>\r\n";

// =====[ADDED] 실험 4 회로/실험 5를 위한 추가 변수들 =====
const int LED_PIN = 5;                 // LED 연결 핀 (D5) [ADDED]
const int LED_ON_THRESHOLD = 52;       // 조도 임계값(환경에 맞게 조정) [ADDED]
int sensed_light = 0;                  // 현재 조도값 저장용 [ADDED]
                          
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
 
  if(!wifi.begin(2, 3))
  {
    Serial.println(F("Error talking to shield"));
    while(1);
  }
  Serial.println(wifi.firmwareVersion());
  Serial.print(F("Mode: "));Serial.println(wifi.getMode());// 1- station mode, 2- softap mode, 3- both
  Serial.println(F("Start wifi connection"));
  if(!wifi.connectAP(ssid, pass))
  {
    Serial.println(F("Error connecting to WiFi"));
    while(1);
  } 
  Serial.print(F("Connected to "));Serial.println(wifi.SSID());
  Serial.println(F("IP address: "));
  Serial.println(wifi.localIP());
  wifi.updateStatus();
  Serial.println(wifi.status()); //2- wifi connected with ip, 3- got connection with servers or clients, 4- disconnect with clients or servers, 5- no wifi
  clientTest();

  pinMode(LED_PIN, OUTPUT);            // =====[ADDED] LED 핀 모드 설정
  digitalWrite(LED_PIN, LOW);          // =====[ADDED] 초기 상태: LED OFF

  server.begin();
}

void loop() {
  serverTest();
}

void serverTest()
{
  ESP8266Client client = server.available();
  
  if(client.available()>0)
  {
    String req = client.readStringUntil('\r'); 
    // First line of HTTP request looks like "GET /path HTTP/1.1"
    // Retrieve the "/path" part by finding the spaces
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) {
      Serial.print(F("Invalid request: "));
      Serial.println(req);
      return;
    }
    req = req.substring(addr_start + 1, addr_end);
    Serial.print(F("Request: "));
    Serial.println(req);
    client.readString();
    
    if(req.equals("/"))
    {
      IPAddress ip = wifi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      client.print(htmlHeader);
      String htmlBody = "Hello from MWFL";
      htmlBody += "<br>";
      htmlBody += "06_KSY_LTH_KJH";
      htmlBody += "</html>\r\n\r\n";
      client.print(htmlBody);
    }

    else if (req.equals("/team_info")) 
    {
      client.print(htmlHeader);
      client.print("<head>");
      client.print("<title>");
      client.print("HTML example page"); // 페이지 제목
      client.print("</title>");
      client.print("</head>");
  
      client.print("<body bgcolor=#A47864>"); // Body color = Mocha Mousse
      client.print("<font size=36 color=FF69B4>"); // Font color = Hot Pink

      client.print("Team MWFL");
      client.print("<br>"); 
      client.print("06_KSY_LTH_KJH"); // 조원 이름
      client.print("<br>");

      // move to test
      client.print("<br>");
      client.print("<a href=./test>");
      client.print("move to test");
      client.print("</a>");
      client.print("<br>");
  
      client.print("</font>");
      client.print("</body>"); 
      client.print("</html>");
    }

    else if (req.equals("/test")) 
    {
      client.print(htmlHeader);
      client.print("<head>");
      client.print("<title>");
      client.print("Test Page"); // 페이지 제목
      client.print("</title>");
      client.print("</head>");
  
      client.print("<body bgcolor=#000000>"); // Body color = Black 
      client.print("<font size=36 color=808080>"); // Font color = Grey

      client.print("This is Test page");
      client.print("<br>");
      
      client.print("<br>");
      client.print("<a href=./team_info>");
      client.print("move to Team info");
      client.print("</a>");
      client.print("<br>");
  
      client.print("</font>");
      client.print("</body>"); 
      client.print("</html>");
    }
    
    else if(req.equals("/analog"))
    {
      client.print(htmlHeader);
      String htmlBody="";
      for (int a = 0; a < 6; a++)
      {
        htmlBody += "A";
        htmlBody += String(a);
        htmlBody += ": ";
        htmlBody += String(analogRead(a));
        htmlBody += "<br>\r\n";
      }
      htmlBody += "\r\n</html>\r\n";
      client.print(htmlBody);
    }
    
    else if(req.equals("/info"))
    {
      String toSend = wifi.firmwareVersion();
      toSend.replace("\r\n","<br>");
      client.print(htmlHeader);
      client.print(toSend);
      client.print("</html>\r\n");
    }

    else
      client.print("HTTP/1.1 404 Not Found\r\n\r\n");
    
    client.stop();
 
  }
}

void clientTest()
{
  const char destServer[] = "wifitest.adafruit.com";
  ESP8266Client client;
  if (!client.connect(destServer, 80))
  {
    Serial.println(F("Failed to connect to server."));
    client.stop();
    return;
  }
  
  const char *httpRequest = "GET /testwifi/index.html HTTP/1.1\r\n"
                           "Host: wifitest.adafruit.com\r\n"
                           "Connection: close\r\n\r\n";
  if(!client.print(httpRequest))
  {
    Serial.println(F("Sending failed"));
    client.stop();
    return;;
  }

  // set timeout approximately 5s for server reply
  int i=5000;
  while (client.available()<=0&&i--)
  {
    delay(1);
    if(i==1) {
      Serial.println(F("Timeout"));
      return;
      }
  }

  while (client.available()>0)
  {
    //char c = (char)client.read();
    //Serial.print(c);
    Serial.write(client.read());
  }
  
  client.stop();
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환
