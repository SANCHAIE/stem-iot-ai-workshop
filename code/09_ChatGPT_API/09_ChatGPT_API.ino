/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 5: ESP32 × ChatGPT API — ให้ AI วิเคราะห์ค่า Sensor!
 * 
 * สิ่งที่เรียนรู้:
 * - API คืออะไร (Application Programming Interface)
 * - Generative AI ทำงานยังไง
 * - ส่งข้อมูลจาก sensor ให้ AI วิเคราะห์
 * - JSON format
 * 
 * เตรียมก่อน Upload:
 * 1. ใส่ API Key ของ OpenAI (อาจารย์แจกให้)
 * 2. แก้ชื่อ WiFi / รหัสผ่าน
 * 
 * Library ที่ต้องติดตั้ง:
 * - ArduinoJson (by Benoit Blanchon)
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

// ⚙️ แก้ตรงนี้!
const char* ssid     = "WORKSHOP_WIFI";
const char* password = "12345678";
const char* apiKey   = "sk-xxxxxxxxxxxxx";  // ← API Key จากอาจารย์

// ขา Pin
#define DHTPIN  14
#define LDR_PIN 34
#define DHTTYPE DHT11
#define BUTTON  15      // กดปุ่มเพื่อถาม AI

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUTTON, INPUT_PULLUP);

  // เชื่อมต่อ WiFi
  Serial.print("กำลังเชื่อมต่อ WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("✅ WiFi เชื่อมต่อสำเร็จ!");
  Serial.println("=========================================");
  Serial.println("🤖 ESP32 × ChatGPT API");
  Serial.println("กดปุ่มเพื่อให้ AI วิเคราะห์สภาพแวดล้อม!");
  Serial.println("=========================================");
}

// =============================================
// 🤖 ส่งข้อมูลให้ ChatGPT วิเคราะห์
// =============================================
String askChatGPT(float temp, float humid, int light) {
  if (WiFi.status() != WL_CONNECTED) {
    return "❌ WiFi ไม่ได้เชื่อมต่อ";
  }

  HTTPClient http;
  http.begin("https://api.openai.com/v1/chat/completions");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", String("Bearer ") + apiKey);
  http.setTimeout(30000);  // รอ 30 วินาที

  // สร้าง Prompt
  String prompt = "คุณเป็นผู้เชี่ยวชาญด้านสภาพแวดล้อมในห้องเรียน "
                  "วิเคราะห์ข้อมูลจาก sensor ต่อไปนี้แล้วให้คำแนะนำสั้นๆ เป็นภาษาไทย (ไม่เกิน 3 บรรทัด):\n"
                  "- อุณหภูมิ: " + String(temp, 1) + " °C\n"
                  "- ความชื้น: " + String(humid, 1) + " %\n"
                  "- แสงสว่าง: " + String(light) + " %";

  // สร้าง JSON body
  JsonDocument doc;
  doc["model"] = "gpt-4o-mini";
  doc["max_tokens"] = 200;
  
  JsonArray messages = doc["messages"].to<JsonArray>();
  JsonObject msg = messages.add<JsonObject>();
  msg["role"] = "user";
  msg["content"] = prompt;

  String requestBody;
  serializeJson(doc, requestBody);

  Serial.println("📤 กำลังส่งข้อมูลให้ AI วิเคราะห์...");

  int httpCode = http.POST(requestBody);
  String response = "";

  if (httpCode == 200) {
    String payload = http.getString();
    
    JsonDocument responseDoc;
    deserializeJson(responseDoc, payload);
    
    response = responseDoc["choices"][0]["message"]["content"].as<String>();
  } else {
    response = "❌ Error: " + String(httpCode) + " - " + http.getString();
  }

  http.end();
  return response;
}

void loop() {
  // กดปุ่มเพื่อถาม AI
  if (digitalRead(BUTTON) == LOW) {
    delay(50);  // debounce
    
    // อ่านค่า sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int ldrValue = analogRead(LDR_PIN);
    int lightPercent = map(ldrValue, 0, 4095, 0, 100);

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("❌ อ่าน DHT11 ไม่ได้!");
      delay(1000);
      return;
    }

    // แสดงค่า sensor
    Serial.println("=========================================");
    Serial.println("📊 ข้อมูลจาก Sensor:");
    Serial.print("   🌡️ อุณหภูมิ: "); Serial.print(temperature, 1); Serial.println(" °C");
    Serial.print("   💧 ความชื้น: "); Serial.print(humidity, 1); Serial.println(" %");
    Serial.print("   💡 แสง: "); Serial.print(lightPercent); Serial.println(" %");
    Serial.println("-----------------------------------------");

    // ส่งให้ AI วิเคราะห์
    String aiResponse = askChatGPT(temperature, humidity, lightPercent);
    
    Serial.println("🤖 AI วิเคราะห์:");
    Serial.println(aiResponse);
    Serial.println("=========================================");

    // รอปล่อยปุ่ม
    while (digitalRead(BUTTON) == LOW) {
      delay(10);
    }
    delay(500);
  }
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) แก้ prompt → ให้ AI ตอบเป็นภาษาอังกฤษ
 * 2) แก้ prompt → ให้ AI ให้คะแนนความสบาย 1-10
 * 3) แก้ prompt → ให้ AI เปรียบเทียบกับสภาพอากาศในเมืองต่างๆ
 * 4) คิดดู: ถ้าเพิ่ม sensor อีก (เสียง, CO2) AI จะวิเคราะห์อะไรได้อีก?
 * 
 * 💡 หลักการ Prompt Engineering:
 * - ถามชัด → ได้คำตอบชัด
 * - ให้ context → AI เข้าใจมากขึ้น
 * - ระบุ format → ได้คำตอบตรงรูปแบบ
 * =============================================
 */
