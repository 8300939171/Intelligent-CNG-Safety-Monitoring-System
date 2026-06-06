#include <Wire.h>
#include <Adafruit_BME280.h>
#include <MPU6050.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= SENSOR OBJECTS =================
Adafruit_BME280 bme;
MPU6050 mpu;

// ================= PINS =================
#define GAS_PIN 34

#define RED_LED 27
#define WHITE_LED 26
#define GREEN_LED 25

// ================= VARIABLES =================
int gasLevel = 0;
int tempLevel = 0;
int vibLevel = 0;

// Previous acceleration values
int16_t prev_ax = 0;
int16_t prev_ay = 0;
int16_t prev_az = 0;

void setup() {

  Serial.begin(115200);

  // ================= GPS =================
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  delay(2000);

  // ================= I2C =================
  Wire.begin(21, 22);

  // ================= LED OUTPUTS =================
  pinMode(RED_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // ================= GAS SENSOR =================
  pinMode(GAS_PIN, INPUT);

  // ================= OLED INIT =================
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED FAILED");
    while (1);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15, 22);
  display.println("BOOTING");

  display.display();

  // ================= BME280 =================
  bool bmeStatus = bme.begin(0x76);

  if (!bmeStatus) {
    bmeStatus = bme.begin(0x77);
  }

  if (bmeStatus)
    Serial.println("BME280 CONNECTED");
  else
    Serial.println("BME280 NOT FOUND");

  // ================= MPU6050 =================
  mpu.initialize();

  if (mpu.testConnection())
    Serial.println("MPU6050 CONNECTED");
  else
    Serial.println("MPU6050 NOT FOUND");

  delay(2000);
}

void loop() {

  // =========================================
  // GAS SENSOR
  // =========================================
  int gasDetected = digitalRead(GAS_PIN);

  // =========================================
  // TEMPERATURE
  // =========================================
  float temp = bme.readTemperature();

  // =========================================
  // MPU6050 VIBRATION
  // =========================================
  int16_t ax, ay, az;

  mpu.getAcceleration(&ax, &ay, &az);

  float vibration =
    abs(ax - prev_ax) +
    abs(ay - prev_ay) +
    abs(az - prev_az);

  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  // =========================================
  // RESET LEVELS
  // =========================================
  gasLevel = 0;
  tempLevel = 0;
  vibLevel = 0;

  // =========================================
  // GAS LOGIC
  // HIGH = GAS DETECTED
  // =========================================
    if (gasDetected == LOW) {

    gasLevel = 2;

    Serial.println("Gas Status : LEAK DETECTED");
  }
  else{
    Serial.println("Gas Status : NOT DETECTED");
  }


  // =========================================
  // TEMPERATURE LOGIC
  // =========================================
  if (temp > 45) {

    tempLevel = 2;
  }
  else if (temp > 35) {

    tempLevel = 1;
  }

  // =========================================
  // VIBRATION LOGIC
  // =========================================
  if (vibration > 8000) {

    vibLevel = 2;
  }
  else if (vibration > 3000) {

    vibLevel = 1;
  }

  // =========================================
  // FINAL STATUS
  // =========================================
  int finalLevel = max(gasLevel, max(tempLevel, vibLevel));

  // =========================================
  // LED CONTROL
  // =========================================
  if (finalLevel == 0) {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }

  else if (finalLevel == 1) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }

  else {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }

  // =========================================
  // SERIAL MONITOR
  // =========================================
  Serial.println("========== SYSTEM ==========");

  if (finalLevel == 0)
    Serial.println("STATUS : SAFE");

  else if (finalLevel == 1)
    Serial.println("STATUS : WARNING");

  else
    Serial.println("STATUS : FAULT");

  Serial.print("Temperature :");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Vibration :");
  Serial.println(vibration);

  // =========================================
  // OLED DISPLAY UI
  // =========================================
  display.clearDisplay();

  // ===== TITLE =====
  display.setTextSize(1);
  display.setCursor(18, 0);
  display.println("SMART SAFETY SYSTEM");

  display.drawLine(0, 10, 128, 10, WHITE);

  // ===== MAIN STATUS =====
  display.setTextSize(2);
  display.setCursor(12, 16);

  if (finalLevel == 0) {

    display.println("SAFE");
  }
  else if (finalLevel == 1) {

    display.println("WARNING");
  }
  else {

    display.println("FAULT");
  }

  // ===== TEMPERATURE VALUE =====
  display.setTextSize(1);

  display.setCursor(0, 42);
  display.print("TEMP : ");
  display.print(temp, 1);
  display.print(" C");

  // ===== SENSOR STATUS =====
  display.setCursor(0, 54);

  if (gasLevel == 2)
    display.print("GAS!");
  else
    display.print("GAS OK");

  display.setCursor(48, 54);

  if (tempLevel > 0)
    display.print("TEMP!");
  else
    display.print("TEMP OK");

  display.setCursor(100, 54);

  if (vibLevel > 0)
    display.print("VIB!");
  else
    display.print("VIB OK");

  display.display();

  // =========================================
  // GPS RAW DATA
  // =========================================
  while (Serial2.available()) {

    char c = Serial2.read();

    Serial.write(c);
  }

  delay(1000);
}
