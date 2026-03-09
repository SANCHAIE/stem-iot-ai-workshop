/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 2.2: LDR — วัดค่าแสง
 * 
 * สิ่งที่เรียนรู้:
 * - Analog Input (analogRead)
 * - Voltage Divider (วงจรแบ่งแรงดัน)
 * - ADC (Analog to Digital Converter) ค่า 0-4095
 * 
 * การต่อวงจร (Voltage Divider):
 * 3.3V → LDR → จุดกลาง → R 10kΩ → GND
 *                 ↓
 *           ESP32 GPIO 34 (ADC)
 * 
 * แสงมาก → LDR ความต้านทานต่ำ → ค่า ADC สูง
 * แสงน้อย → LDR ความต้านทานสูง → ค่า ADC ต่ำ
 */

#define LDR_PIN 34   // ขา ADC (GPIO 34 เป็น input-only เหมาะกับ sensor)

void setup() {
  Serial.begin(115200);
  
  Serial.println("=== LDR Light Sensor ===");
  Serial.println("ลองบังแสง / ส่องไฟดูค่าเปลี่ยน!");
  Serial.println("-----------------------------------");
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);  // อ่านค่า 0-4095

  // แปลงเป็นเปอร์เซ็นต์แสง (ประมาณ)
  int lightPercent = map(ldrValue, 0, 4095, 0, 100);

  // แสดงผล
  Serial.print("💡 ค่า ADC: ");
  Serial.print(ldrValue);
  Serial.print("  |  แสง: ");
  Serial.print(lightPercent);
  Serial.print("%  |  ");

  // แสดงระดับแสงเป็นข้อความ
  if (lightPercent > 70) {
    Serial.println("☀️ สว่างมาก");
  } else if (lightPercent > 40) {
    Serial.println("🌤️ สว่างปานกลาง");
  } else if (lightPercent > 15) {
    Serial.println("🌥️ สลัว");
  } else {
    Serial.println("🌑 มืด");
  }

  delay(500);
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) ใช้มือบัง LDR → ค่าเปลี่ยนเป็นเท่าไหร่?
 * 2) ใช้ไฟฉายมือถือส่อง → ค่าสูงสุดเท่าไหร่?
 * 3) จดค่าแสง 5 จุดในห้อง ลงใบงาน
 * 4) จุดไหนมืดสุด? สว่างสุด? ทำไม?
 * =============================================
 */
