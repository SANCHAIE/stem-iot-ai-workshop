/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 3.1: ESP32 Web Server — ดูค่า Sensor + ควบคุม LED จากมือถือ!
 * 
 * สิ่งที่เรียนรู้:
 * - WiFi เชื่อมต่ออินเทอร์เน็ต
 * - Web Server คืออะไร
 * - HTML พื้นฐาน
 * - ควบคุมอุปกรณ์ผ่านเว็บ
 * 
 * วิธีใช้:
 * 1. แก้ชื่อ WiFi และรหัสผ่านด้านล่าง
 * 2. Upload โปรแกรม
 * 3. เปิด Serial Monitor ดู IP Address
 * 4. เปิด Browser บนมือถือ พิมพ์ IP Address
 * 5. ดูค่า sensor + กดปุ่มควบคุม LED ได้เลย!
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ⚙️ แก้ตรงนี้! ใส่ชื่อ WiFi และรหัสผ่าน
const char* ssid     = "WORKSHOP_WIFI";    // ← ชื่อ WiFi
const char* password = "12345678";         // ← รหัสผ่าน

// ขา Pin
#define LED_RED    2
#define LED_YELLOW 4
#define LED_GREEN  5
#define DHTPIN     14
#define LDR_PIN    34
#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

bool ledRedState    = false;
bool ledYellowState = false;
bool ledGreenState  = false;

// =============================================
// 🌐 สร้างหน้าเว็บ HTML
// =============================================
String getHTML() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  int lightPercent = map(ldrValue, 0, 4095, 0, 100);

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Smart Monitor</title>
  <style>
    * { box-sizing: border-box; margin: 0; padding: 0; }
    body { font-family: 'Segoe UI', Tahoma, sans-serif; background: #1a1a2e; color: #fff; padding: 20px; }
    h1 { text-align: center; font-size: 1.5em; margin-bottom: 20px; color: #e94560; }
    .card { background: #16213e; border-radius: 15px; padding: 20px; margin-bottom: 15px; }
    .sensor-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; }
    .sensor-box { background: #0f3460; border-radius: 10px; padding: 15px; text-align: center; }
    .sensor-box .icon { font-size: 2em; }
    .sensor-box .value { font-size: 1.8em; font-weight: bold; margin: 5px 0; }
    .sensor-box .label { font-size: 0.8em; color: #a0a0a0; }
    .led-grid { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 10px; }
    .btn { border: none; border-radius: 10px; padding: 15px; font-size: 1em; cursor: pointer; width: 100%; color: #fff; }
    .btn-red-on { background: #e94560; } .btn-red-off { background: #4a1a2e; }
    .btn-yellow-on { background: #f5a623; } .btn-yellow-off { background: #4a3a1e; }
    .btn-green-on { background: #2ecc71; } .btn-green-off { background: #1a4a2e; }
    .refresh { display: block; width: 100%; padding: 12px; background: #e94560; color: #fff;
               border: none; border-radius: 10px; font-size: 1em; cursor: pointer; margin-top: 10px; }
  </style>
</head>
<body>
  <h1>🔌 ESP32 Smart Monitor</h1>
  
  <div class="card">
    <div class="sensor-grid">
      <div class="sensor-box">
        <div class="icon">🌡️</div>
        <div class="value">)rawliteral";
  
  html += String(temperature, 1);
  html += R"rawliteral(°C</div>
        <div class="label">อุณหภูมิ</div>
      </div>
      <div class="sensor-box">
        <div class="icon">💧</div>
        <div class="value">)rawliteral";
  
  html += String(humidity, 1);
  html += R"rawliteral(%</div>
        <div class="label">ความชื้น</div>
      </div>
      <div class="sensor-box">
        <div class="icon">💡</div>
        <div class="value">)rawliteral";
  
  html += String(lightPercent);
  html += R"rawliteral(%</div>
        <div class="label">แสง</div>
      </div>
      <div class="sensor-box">
        <div class="icon">📊</div>
        <div class="value">)rawliteral";
  
  html += String(ldrValue);
  html += R"rawliteral(</div>
        <div class="label">ADC</div>
      </div>
    </div>
  </div>
  
  <div class="card">
    <h2 style="margin-bottom:10px;">🎮 ควบคุม LED</h2>
    <div class="led-grid">
      <a href="/toggle/red"><button class="btn )rawliteral";
  html += ledRedState ? "btn-red-on" : "btn-red-off";
  html += R"rawliteral(">🔴 แดง<br>)rawliteral";
  html += ledRedState ? "ON" : "OFF";
  html += R"rawliteral(</button></a>
      <a href="/toggle/yellow"><button class="btn )rawliteral";
  html += ledYellowState ? "btn-yellow-on" : "btn-yellow-off";
  html += R"rawliteral(">🟡 เหลือง<br>)rawliteral";
  html += ledYellowState ? "ON" : "OFF";
  html += R"rawliteral(</button></a>
      <a href="/toggle/green"><button class="btn )rawliteral";
  html += ledGreenState ? "btn-green-on" : "btn-green-off";
  html += R"rawliteral(">🟢 เขียว<br>)rawliteral";
  html += ledGreenState ? "ON" : "OFF";
  html += R"rawliteral(</button></a>
    </div>
  </div>
  
  <button class="refresh" onclick="location.reload()">🔄 รีเฟรช</button>
  
  <script>
    // Auto refresh ทุก 5 วินาที
    setTimeout(function(){ location.reload(); }, 5000);
  </script>
</body>
</html>
)rawliteral";

  return html;
}

// =============================================
// จัดการ Request
// =============================================
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void handleToggleRed() {
  ledRedState = !ledRedState;
  digitalWrite(LED_RED, ledRedState);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleToggleYellow() {
  ledYellowState = !ledYellowState;
  digitalWrite(LED_YELLOW, ledYellowState);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleToggleGreen() {
  ledGreenState = !ledGreenState;
  digitalWrite(LED_GREEN, ledGreenState);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  dht.begin();

  // เชื่อมต่อ WiFi
  Serial.print("กำลังเชื่อมต่อ WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("✅ เชื่อมต่อ WiFi สำเร็จ!");
  Serial.print("📱 เปิด Browser แล้วไปที่: http://");
  Serial.println(WiFi.localIP());
  Serial.println("=========================================");

  // ตั้งค่า Web Server
  server.on("/", handleRoot);
  server.on("/toggle/red", handleToggleRed);
  server.on("/toggle/yellow", handleToggleYellow);
  server.on("/toggle/green", handleToggleGreen);
  server.begin();
}

void loop() {
  server.handleClient();
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) เปลี่ยนสีพื้นหลังเว็บ → แก้ค่า background ใน CSS
 * 2) เพิ่มปุ่ม "เปิดหมด" / "ปิดหมด"
 * 3) เปิดเว็บจากมือถือเพื่อน → ใช้ IP เดียวกันได้!
 * 4) คิดดู: ถ้าอยากให้ sensor update โดยไม่ต้อง refresh?
 *    (คำตอบ: ใช้ AJAX หรือ WebSocket)
 * =============================================
 */
