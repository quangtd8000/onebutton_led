#include <Arduino.h>
#include <OneButton.h>

#ifndef LED_PIN
#define LED_PIN 2
#endif

#ifndef BTN_PIN
#define BTN_PIN 4
#endif

// Khởi tạo OneButton: chân BTN_PIN, active LOW = true (sử dụng internal pull-up)
OneButton button(BTN_PIN, true);

bool isBlinking = false;
bool ledState = false;
unsigned long previousMillis = 0;
const unsigned long blinkInterval = 200; // Chu kỳ nhấp nháy 200ms

// Single click: Bật/Tắt LED (nếu đang nháy thì dừng nháy và tắt)
void handleClick() {
    if (isBlinking) {
        isBlinking = false;
        ledState = false;
    } else {
        ledState = !ledState;
    }
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.println(ledState ? "[LED] ON" : "[LED] OFF");
}

// Double click: Chuyển sang chế độ nháy LED (thay vì nhấn giữ lâu >1s)
void handleDoubleClick() {
    isBlinking = !isBlinking;
    if (isBlinking) {
        Serial.println("[MODE] Double click -> Chuyen sang che do BLINK (200ms)");
    } else {
        ledState = false;
        digitalWrite(LED_PIN, LOW);
        Serial.println("[MODE] Dung che do BLINK -> LED OFF");
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Gán các hàm callback cho sự kiện nút bấm
    button.attachClick(handleClick);
    button.attachDoubleClick(handleDoubleClick);

    Serial.println("=================================================");
    Serial.println("ESP32 DevKit V1 - OneButton Single LED Controller");
    Serial.println("Board: DOIT ESP32 DevKit V1");
    Serial.println("Single Click: Bat/Tat LED");
    Serial.println("Double Click: Chuyen sang / Thoat che do Nhap nhay LED");
    Serial.println("=================================================");
}

void loop() {
    // Luôn gọi tick() liên tục trong loop() để giải mã tín hiệu nút nhấn và khử rung
    button.tick();

    // Điều khiển nhấp nháy non-blocking bằng hàm millis()
    if (isBlinking) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= blinkInterval) {
            previousMillis = currentMillis;
            ledState = !ledState;
            digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        }
    }
}
