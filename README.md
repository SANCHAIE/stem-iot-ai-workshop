# STEM Engineering Workshop: From Embedded Systems to IoT and AI

## โครงการบริการวิชาการ STEM Engineering Workshop สำหรับนักเรียนมัธยมศึกษา

Workshop 1 วัน สำหรับนักเรียน ม.3 ที่ไม่เคยเขียนโปรแกรม เรียนรู้ตั้งแต่พื้นฐาน LED จนถึง AI

**จัดโดย:** คณะวิศวกรรมศาสตร์ มหาวิทยาลัยบูรพา  
**สำหรับ:** นักเรียนห้องเรียนพิเศษ SC-ICT ม.3 โรงเรียนปิยะมหาราชาลัย จ.นครพนม  
**จำนวน:** 33 คน (11 กลุ่ม × 3 คน)  
**บอร์ด:** ESP32 DevKit  

---

## 📁 โครงสร้างโปรเจกต์

```
stem-iot-ai-workshop/
├── README.md
├── code/
│   ├── 01_Blink/              # LED กระพริบ
│   ├── 02_TrafficLight/       # ไฟจราจร 3 สี
│   ├── 03_Button_LED/         # ปุ่มกดควบคุม LED
│   ├── 04_DHT22/              # อ่านอุณหภูมิ/ความชื้น
│   ├── 05_LDR/                # อ่านค่าแสง
│   ├── 06_IF_Condition/       # เงื่อนไข sensor → LED
│   ├── 07_WebServer/          # ESP32 Web Server
│   ├── 08_ThingSpeak/         # ส่งข้อมูลขึ้น ThingSpeak
│   └── 09_ChatGPT_API/       # ESP32 × ChatGPT API
├── docs/                      # เอกสารโครงการ
├── worksheets/                # ใบงานนักเรียน
└── slides/                    # สไลด์ประกอบการสอน
```

---

## ⏰ กำหนดการ

### ช่วงเช้า (3 ชม.) — Embedded Systems → IoT

| เวลา | กิจกรรม | Code |
|---|---|---|
| 08.00 - 08.30 | ลงทะเบียน | - |
| 08.30 - 08.45 | พิธีเปิด | - |
| 08.45 - 09.45 | **กิจกรรมที่ 1:** พื้นฐาน LED + ปุ่มกด | `01_Blink` `02_TrafficLight` `03_Button_LED` |
| 09.45 - 10.45 | **กิจกรรมที่ 2:** Sensor วัดสิ่งแวดล้อม | `04_DHT22` `05_LDR` `06_IF_Condition` |
| 10.45 - 11.00 | พักอาหารว่าง | - |
| 11.00 - 12.00 | **กิจกรรมที่ 3:** IoT (Web Server + ThingSpeak) | `07_WebServer` `08_ThingSpeak` |

### ช่วงบ่าย (3 ชม.) — AI

| เวลา | กิจกรรม | Code |
|---|---|---|
| 13.00 - 14.00 | **กิจกรรมที่ 4:** ML + Teachable Machine | (ใช้เว็บ) |
| 14.00 - 15.00 | **กิจกรรมที่ 5:** Generative AI + ChatGPT × ESP32 | `09_ChatGPT_API` |
| 15.00 - 15.15 | พักอาหารว่าง | - |
| 15.15 - 16.15 | **กิจกรรมที่ 6:** AI Ideation + แนะนำสาขา | - |
| 16.15 - 16.30 | สรุป + มอบเกียรติบัตร | - |

---

## 🔌 อุปกรณ์ต่อกลุ่ม (11 ชุด)

- ESP32 DevKit + สาย USB-C
- Breadboard + สายจัมเปอร์
- LED แดง/เหลือง/เขียว + ตัวต้านทาน 220Ω × 3
- ปุ่มกด + ตัวต้านทาน 10kΩ
- DHT22 (เซนเซอร์อุณหภูมิ/ความชื้น)
- LDR + ตัวต้านทาน 10kΩ

---

## 💻 การติดตั้ง Software

### Arduino IDE
1. ดาวน์โหลด Arduino IDE จาก https://www.arduino.cc/en/software
2. เพิ่ม ESP32 Board:
   - ไปที่ File → Preferences → Additional Board Manager URLs
   - เพิ่ม: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - ไปที่ Tools → Board → Boards Manager → ค้นหา "ESP32" → Install
3. เลือก Board: **ESP32 Dev Module**

### Library ที่ต้องติดตั้ง
- **DHT sensor library** by Adafruit (สำหรับ DHT22)
- **ThingSpeak** by MathWorks (สำหรับ ThingSpeak)
- **ArduinoJson** by Benoit Blanchon (สำหรับ ChatGPT API)
- **WiFi** (มาพร้อม ESP32 board แล้ว)
- **HTTPClient** (มาพร้อม ESP32 board แล้ว)

วิธีติดตั้ง: Sketch → Include Library → Manage Libraries → ค้นหาชื่อ → Install

---

## 🔗 บริการออนไลน์ที่ต้องเตรียม

| บริการ | URL | หมายเหตุ |
|---|---|---|
| ThingSpeak | https://thingspeak.com | สมัครฟรีด้วย Google Account |
| Teachable Machine | https://teachablemachine.withgoogle.com | เปิดผ่าน Chrome ไม่ต้องสมัคร |
| ChatGPT API | https://platform.openai.com | ต้องเตรียม API key + ตั้ง spending limit |

---

## 📐 วงจรต่อสาย (Pin Assignment)

### กิจกรรมที่ 1-3: LED + ปุ่มกด
```
ESP32 GPIO 2  → ตัวต้านทาน 220Ω → LED แดง → GND
ESP32 GPIO 4  → ตัวต้านทาน 220Ω → LED เหลือง → GND
ESP32 GPIO 5  → ตัวต้านทาน 220Ω → LED เขียว → GND
ESP32 GPIO 15 → ปุ่มกด → GND (ใช้ INPUT_PULLUP)
```

### กิจกรรมที่ 4-6: Sensor
```
DHT22 VCC  → 3.3V
DHT22 DATA → ESP32 GPIO 14 (ต่อ pull-up 10kΩ ไป 3.3V)
DHT22 GND  → GND

LDR → 3.3V (ขาหนึ่ง)
LDR → ESP32 GPIO 34 + ตัวต้านทาน 10kΩ → GND (voltage divider)
```

---

## 👨‍🏫 วิธีการสอน

ใช้วิธี **Copy → Run → Modify → Learn** สำหรับนักเรียนมือใหม่:
1. **Copy** — แจก code สำเร็จรูป ให้ copy ลง Arduino IDE
2. **Run** — กด Upload ดูผลลัพธ์ทันที
3. **Modify** — ให้แก้ค่าตัวเลข เช่น delay, threshold, สี LED
4. **Learn** — อธิบายหลักการว่าทำไมถึงทำงานแบบนั้น

---

## 📝 License

MIT License — สามารถนำไปใช้ ดัดแปลง และเผยแพร่ได้อย่างอิสระ

## 👤 ผู้จัดทำ

ผศ.ดร.สัญชัย เอียดปราบ  
สาขาวิศวกรรมระบบสมองกลฝังตัวและสื่อสารอิเล็กทรอนิกส์  
คณะวิศวกรรมศาสตร์ มหาวิทยาลัยบูรพา
