/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 2.3: IF Condition — เงื่อนไขควบคุม LED ตามค่า Sensor
 * 
 * สิ่งที่เรียนรู้:
 * - if-else เงื่อนไข
 * - Threshold (ค่าขีดแบ่ง)
 * - ระบบแจ้งเตือนอัตโนมัติ
 * - อ่าน sensor หลายตัวพร้อมกัน
 * 
 * การต่อวงจร: (รวมจากกิจกรรมก่อนหน้า)
 * LED แดง   → GPIO 2 (เตือนร้อน)
 * LED เหลือง → GPIO 4 (เตือนมืด)
 * LED เขียว  → GPIO 5 (ปกติ)
 * DHT11      → GPIO 14
 * LDR        → GPIO 34
 */

#include <DHT.h>

// ขา Pin
#define LED_RED    2
#define LED_YELLOW 4
#define LED_GREEN  5
#define DHTPIN     14
#define LDR_PIN    34
#define DHTTYPE    DHT11

// ⚙️ ค่า Threshold — ลองเปลี่ยนดู!
#define TEMP_THRESHOLD   33.0   // ถ้าร้อนเกินกี่องศา → ไฟแดง
#define LIGHT_THRESHOLD  25     // ถ้าแสงต่ำกว่ากี่ % → ไฟเหลือง

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  dht.begin();

  Serial.println("=== Smart Alert System ===");
  Serial.print("🌡️ Threshold อุณหภูมิ: ");
  Serial.print(TEMP_THRESHOLD);
  Serial.println(" °C");
  Serial.print("💡 Threshold แสง: ");
  Serial.print(LIGHT_THRESHOLD);
  Serial.println(" %");
  Serial.println("-----------------------------------");
}

void loop() {
  // อ่านค่า sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  int lightPercent = map(ldrValue, 0, 4095, 0, 100);

  // ตรวจสอบ DHT22
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("❌ อ่าน DHT11 ไม่ได้!");
    delay(2000);
    return;
  }

  // แสดงค่า
  Serial.print("🌡️ ");
  Serial.print(temperature, 1);
  Serial.print("°C  💧 ");
  Serial.print(humidity, 1);
  Serial.print("%  💡 ");
  Serial.print(lightPercent);
  Serial.print("%  → ");

  // =============================================
  // 🧠 เงื่อนไข IF — หัวใจของระบบอัจฉริยะ!
  // =============================================
  
  bool isHot  = (temperature > TEMP_THRESHOLD);
  bool isDark = (lightPercent < LIGHT_THRESHOLD);

  if (isHot && isDark) {
    // 🔴🟡 ทั้งร้อนและมืด → ไฟแดง + เหลือง
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    Serial.println("⚠️ ร้อนและมืด! เปิดแอร์ + เปิดไฟ");
  }
  else if (isHot) {
    // 🔴 ร้อนเกิน → ไฟแดง
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    Serial.println("🔴 ร้อนเกิน! ควรเปิดแอร์");
  }
  else if (isDark) {
    // 🟡 มืดเกิน → ไฟเหลือง
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    Serial.println("🟡 มืดเกิน! ควรเปิดไฟ");
  }
  else {
    // 🟢 ปกติ → ไฟเขียว
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("🟢 สภาพแวดล้อมปกติ");
  }

  delay(2000);
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) เปลี่ยน TEMP_THRESHOLD เป็น 30 → ไฟแดงติดบ่อยขึ้นไหม?
 * 2) เปลี่ยน LIGHT_THRESHOLD เป็น 50 → ไฟเหลืองติดบ่อยขึ้นไหม?
 * 3) เพิ่มเงื่อนไข: ถ้าความชื้นเกิน 80% → LED ทุกดวงกระพริบ
 * 4) คิดดู: ถ้าต่อ Relay แทน LED จะสั่งเปิดแอร์/เปิดไฟได้จริงไหม?
 * =============================================
 */
