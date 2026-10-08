# ESP32 OneButton LED Controller (Week 3 - PHY3640)

Dự án điều khiển LED bằng nút nhấn sử dụng thư viện **OneButton** trên kit vi điều khiển **DOIT ESP32 DevKit V1** (thuộc học phần *Phát triển ứng dụng IoT - PHY3640*, Khoa Vật lý - ĐHKHTN, ĐHQGHN).

## 1. Yêu cầu chức năng
- **Single Click**: Bật / Tắt LED (đảo trạng thái). Nếu LED đang ở chế độ nhấp nháy, nhấn single click sẽ dừng nhấp nháy và tắt LED.
- **Double Click**: Chuyển sang chế độ nhấp nháy LED (thay cho hành vi nhấn giữ > 1s ban đầu). Nhấn double click lần nữa sẽ dừng nhấp nháy.
- Thuật toán điều khiển nhấp nháy: Sử dụng hàm `millis()` không chặn (non-blocking) với chu kỳ 200ms để đảm bảo `button.tick()` luôn được gọi liên tục và đáp ứng tức thời.

## 2. Phần cứng và Sơ đồ nối dây
- **Board phát triển**: DOIT ESP32 DevKit V1 (30 chân, vi điều khiển ESP32 Xtensa Dual-core).
- **LED**:
  - Chân GPIO 2: LED tích hợp trên board (Onboard Blue LED, active HIGH).
  - Có thể nối thêm LED ngoài vào chân GPIO 2 (hoặc GPIO 5) nối tiếp với điện trở 220Ω / 330Ω xuống GND.
- **Nút nhấn (Push Button)**:
  - Một đầu nối vào chân GPIO 4 của ESP32.
  - Đầu còn lại nối vào chân GND.
  - Sử dụng cấu hình `INPUT_PULLUP` nội của ESP32 (active LOW, giá trị mặc định HIGH khi thả, LOW khi nhấn).

## 3. Cấu hình PlatformIO (`platformio.ini`)
```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
monitor_speed = 115200
upload_speed = 921600
lib_deps =
    mathertel/OneButton @ ^2.6.1
build_flags =
    -D LED_PIN=2
    -D BTN_PIN=4
```

## 4. Hướng dẫn biên dịch và nạp code
1. Cài đặt extension **PlatformIO IDE** trên VS Code.
2. Clone repository về máy tính:
   ```bash
   git clone https://github.com/quangtd8000/onebutton_led.git
   ```
3. Mở thư mục dự án bằng VS Code / PlatformIO.
4. Biên dịch mã nguồn:
   ```bash
   pio run
   ```
5. Kết nối ESP32 với máy tính qua cáp Micro-USB và nạp chương trình:
   ```bash
   pio run -t upload
   ```
6. Mở Serial Monitor với baudrate 115200 để theo dõi log trạng thái:
   ```bash
   pio device monitor
   ```
