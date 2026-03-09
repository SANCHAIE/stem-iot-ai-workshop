/*
 * STEM Engineering Workshop: From Embedded Systems to IoT and AI
 * กิจกรรมที่ 1.3: ปุ่มกด + LED — Digital Input
 * 
 * สิ่งที่เรียนรู้:
 * - Digital Input (อ่านค่าจากปุ่มกด)
 * - INPUT_PULLUP (ตัวต้านทานภายใน)
 * - if-else เงื่อนไข
 * - กดปุ่มเปลี่ยนสถานะ (Toggle)
 * 
 * การต่อวงจร:
 * ESP32 GPIO 2  → R 220Ω → LED แดง → GND
 * ESP32 GPIO 4  → R 220Ω → LED เหลือง → GND
 * ESP32 GPIO 5  → R 220Ω → LED เขียว → GND
 * ESP32 GPIO 15 → ปุ่มกด → GND (ใช้ INPUT_PULLUP ไม่ต้องต่อตัวต้านทาน)
 */

#define LED_RED    2
#define LED_YELLOW 4
#define LED_GREEN  5
#define BUTTON     15

int state = 0;               // สถานะปัจจุบัน (0=แดง, 1=เขียว, 2=เหลือง)
bool lastButtonState = HIGH;  // สถานะปุ่มครั้งก่อน

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);  // ใช้ตัวต้านทานภายใน ESP32

  // เริ่มต้นไฟแดง
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  
  Serial.println("=== Traffic Light with Button ===");
  Serial.println("กดปุ่มเพื่อเปลี่ยนไฟ!");
}

void loop() {
  bool buttonState = digitalRead(BUTTON);

  // ตรวจจับการกดปุ่ม (จาก HIGH → LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);  // debounce — ป้องกันสัญญาณกระเด้ง
    
    state = state + 1;     // เปลี่ยนสถานะ
    if (state > 2) {
      state = 0;           // วนกลับเป็นแดง
    }

    // สั่ง LED ตามสถานะ
    if (state == 0) {
      // 🔴 แดง
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_GREEN, LOW);
      Serial.println("🔴 ไฟแดง — หยุด!");
    } 
    else if (state == 1) {
      // 🟢 เขียว
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("🟢 ไฟเขียว — ไปได้!");
    } 
    else if (state == 2) {
      // 🟡 เหลือง
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_GREEN, LOW);
      Serial.println("🟡 ไฟเหลือง — เตรียมหยุด!");
    }
  }

  lastButtonState = buttonState;  // จำสถานะปุ่ม
  delay(10);
}

/*
 * =============================================
 * 🎯 ลองทำ (Challenges):
 * =============================================
 * 1) เพิ่มสถานะที่ 4: ไฟทุกดวงกระพริบ (โหมดฉุกเฉิน)
 * 2) กดค้าง 3 วินาที → เข้าโหมดกระพริบเหลือง
 * 3) คิดดู: ถ้ามีปุ่ม 2 ปุ่ม จะออกแบบยังไง?
 * =============================================
 */
