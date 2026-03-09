/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 1.2: Traffic Light - ไฟจราจร 3 สี
 * 
 * สิ่งที่เรียนรู้:
 * - ควบคุม LED หลายดวงพร้อมกัน
 * - ลำดับการทำงาน (Sequence)
 * - คิดเชิง Algorithm
 * 
 * การต่อวงจร:
 * ESP32 GPIO 2  → R 220Ω → LED แดง → GND
 * ESP32 GPIO 4  → R 220Ω → LED เหลือง → GND
 * ESP32 GPIO 5  → R 220Ω → LED เขียว → GND
 */

#define LED_RED    2    // ไฟแดง
#define LED_YELLOW 4    // ไฟเหลือง
#define LED_GREEN  5    // ไฟเขียว

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  // 🔴 ไฟแดง — หยุด! (3 วินาที)
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  delay(3000);

  // 🟢 ไฟเขียว — ไปได้! (3 วินาที)
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);
  delay(3000);

  // 🟡 ไฟเหลือง — เตรียมหยุด! (1 วินาที)
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);
  delay(1000);
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) เปลี่ยนเวลาแต่ละสี เช่น เขียว 5 วินาที
 * 2) เพิ่ม "เขียวกระพริบ" ก่อนเปลี่ยนเป็นเหลือง
 *    (ติด 300ms ดับ 300ms × 3 ครั้ง)
 * 3) คิดดู: ไฟจราจรจริงเป็นยังไง? มีขั้นตอนอะไรบ้าง?
 * =============================================
 */
