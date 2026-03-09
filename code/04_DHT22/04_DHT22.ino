/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 2.1: DHT22 — วัดอุณหภูมิและความชื้น
 * 
 * สิ่งที่เรียนรู้:
 * - Analog Sensor คืออะไร
 * - การอ่านค่าจากเซนเซอร์ DHT22
 * - Serial Monitor แสดงผลข้อมูล
 * - การใช้ Library
 * 
 * การต่อวงจร:
 * DHT22 Pin 1 (VCC)  → 3.3V
 * DHT22 Pin 2 (DATA) → ESP32 GPIO 14 (ต่อ R 10kΩ pull-up ไป 3.3V)
 * DHT22 Pin 3 (NC)   → ไม่ต่อ
 * DHT22 Pin 4 (GND)  → GND
 * 
 * Library ที่ต้องติดตั้ง:
 * - DHT sensor library (by Adafruit)
 * - Adafruit Unified Sensor
 */

#include <DHT.h>

#define DHTPIN  14        // ขาที่ต่อ DHT22
#define DHTTYPE DHT22     // ชนิดเซนเซอร์

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  Serial.println("=== DHT22 Sensor ===");
  Serial.println("อ่านค่าอุณหภูมิและความชื้นทุก 2 วินาที");
  Serial.println("-----------------------------------");
}

void loop() {
  // อ่านค่าจากเซนเซอร์
  float humidity = dht.readHumidity();         // ความชื้น (%)
  float temperature = dht.readTemperature();   // อุณหภูมิ (°C)

  // ตรวจสอบว่าอ่านค่าได้หรือไม่
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("❌ อ่านค่าจาก DHT22 ไม่ได้! ตรวจสอบสายว่าต่อถูกต้อง");
    delay(2000);
    return;
  }

  // คำนวณ Heat Index (ดัชนีความร้อน)
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  // แสดงผลบน Serial Monitor
  Serial.print("🌡️ อุณหภูมิ: ");
  Serial.print(temperature, 1);  // ทศนิยม 1 ตำแหน่ง
  Serial.print(" °C");

  Serial.print("  |  💧 ความชื้น: ");
  Serial.print(humidity, 1);
  Serial.print(" %");

  Serial.print("  |  🔥 Heat Index: ");
  Serial.print(heatIndex, 1);
  Serial.println(" °C");

  delay(2000);  // DHT22 ต้องรออย่างน้อย 2 วินาทีระหว่างการอ่าน
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) เปลี่ยนเป็น °F → ใช้ dht.readTemperature(true)
 * 2) คำนวณค่าเฉลี่ยจาก 5 ครั้งที่อ่าน
 * 3) จดค่าอุณหภูมิและความชื้นลงใบงาน 5 จุดในห้อง
 * =============================================
 * 
 * 📊 ตารางเก็บข้อมูล (จดลงใบงาน):
 * | จุดที่ | ตำแหน่ง      | อุณหภูมิ (°C) | ความชื้น (%) |
 * |--------|-------------|---------------|-------------|
 * | 1      | หน้าห้อง     |               |             |
 * | 2      | หลังห้อง     |               |             |
 * | 3      | ข้างหน้าต่าง  |               |             |
 * | 4      | ใต้แอร์      |               |             |
 * | 5      | กลางห้อง     |               |             |
 * | เฉลี่ย  |             |               |             |
 * =============================================
 */
