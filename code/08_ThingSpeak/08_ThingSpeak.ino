/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 3.2: ThingSpeak — ส่งข้อมูล Sensor ขึ้น Cloud ดูกราฟสวยๆ!
 * 
 * สิ่งที่เรียนรู้:
 * - Cloud Platform คืออะไร
 * - IoT: ส่งข้อมูลขึ้น Internet
 * - ดูข้อมูลย้อนหลังเป็นกราฟ
 * 
 * เตรียมก่อน Upload:
 * 1. สมัคร ThingSpeak: https://thingspeak.com (ใช้ Google Account)
 * 2. สร้าง Channel ใหม่ → ตั้งชื่อ Field:
 *    - Field 1: Temperature
 *    - Field 2: Humidity  
 *    - Field 3: Light
 * 3. ไปที่ API Keys → คัดลอก "Write API Key"
 * 4. วางใน THINGSPEAK_API_KEY ด้านล่าง
 * 
 * Library ที่ต้องติดตั้ง:
 * - ThingSpeak (by MathWorks)
 */

#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

// ⚙️ แก้ตรงนี้!
const char* ssid     = "WORKSHOP_WIFI";      // ← ชื่อ WiFi
const char* password = "12345678";           // ← รหัสผ่าน

unsigned long channelID = 0;                  // ← Channel ID (ตัวเลข)
const char* apiKey = "YOUR_WRITE_API_KEY";   // ← Write API Key

// ขา Pin
#define DHTPIN  14
#define LDR_PIN 34
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 20000;  // ส่งทุก 20 วินาที (ThingSpeak free: ขั้นต่ำ 15 วินาที)

void setup() {
  Serial.begin(115200);
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
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // เริ่ม ThingSpeak
  ThingSpeak.begin(client);
  Serial.println("✅ ThingSpeak พร้อมใช้งาน!");
  Serial.println("=========================================");
}

void loop() {
  unsigned long currentTime = millis();

  // ส่งข้อมูลทุก SEND_INTERVAL
  if (currentTime - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = currentTime;

    // อ่านค่า sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int ldrValue = analogRead(LDR_PIN);
    int lightPercent = map(ldrValue, 0, 4095, 0, 100);

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("❌ อ่าน DHT11 ไม่ได้!");
      return;
    }

    // แสดงค่าใน Serial Monitor
    Serial.print("🌡️ ");
    Serial.print(temperature, 1);
    Serial.print("°C  💧 ");
    Serial.print(humidity, 1);
    Serial.print("%  💡 ");
    Serial.print(lightPercent);
    Serial.print("%  →  ");

    // ตั้งค่า Field ของ ThingSpeak
    ThingSpeak.setField(1, temperature);    // Field 1: อุณหภูมิ
    ThingSpeak.setField(2, humidity);       // Field 2: ความชื้น
    ThingSpeak.setField(3, lightPercent);   // Field 3: แสง

    // ส่งข้อมูล!
    int httpCode = ThingSpeak.writeFields(channelID, apiKey);

    if (httpCode == 200) {
      Serial.println("✅ ส่งข้อมูลขึ้น ThingSpeak สำเร็จ!");
    } else {
      Serial.print("❌ Error code: ");
      Serial.println(httpCode);
    }
  }
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) เปิด ThingSpeak → ดูกราฟ → ลองเอามือบัง LDR แล้วดูกราฟเปลี่ยน
 * 2) เพิ่ม Field 4: Heat Index
 * 3) ตั้ง ThingSpeak React → แจ้งเตือนเมื่ออุณหภูมิเกิน 35°C
 * 4) เปรียบเทียบกราฟของกลุ่มอื่น → ห้องไหนร้อนกว่า?
 * 
 * 📱 ดูกราฟ:
 * เปิด Browser → https://thingspeak.com/channels/[CHANNEL_ID]
 * =============================================
 */
