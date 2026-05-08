# ESP32 Environmental Monitoring System

An ESP32-based system that reads environmental sensor data and displays it on a locally hosted web dashboard. Sends email alerts when readings exceed set thresholds.

## What it does

- Reads temperature, humidity, pressure, and altitude from a BME280 sensor
- Reads air quality from an MQ135 sensor
- Hosts a live web dashboard on the local network at `esp32.local`
- Dashboard auto-refreshes every 5 seconds
- Sends an email alert via Gmail SMTP when:
  - Temperature exceeds 50°C
  - Air quality reaches a dangerous level (MQ135 ADC > 2400)
- Suppresses air quality alerts for 10 minutes on startup to allow the MQ135 to warm up

## Hardware

| Component | Connection |
|-----------|------------|
| ESP32 DevKit | — |
| BME280 | I2C — SDA: GPIO 21, SCL: GPIO 22 |
| MQ135 | Analog — GPIO 32 |

## Setup

1. Clone the repo
2. Create a `secrets.h` file in the project folder (this is gitignored):

```cpp
#define WIFI_SSID     "your_wifi_name"
#define WIFI_PASS     "your_wifi_password"
#define EMAIL_ADDRESS "your_email@gmail.com"
#define EMAIL_PASS    "your_gmail_app_password"
#define EMAIL_RECIPIENT "recipient@email.com"
```

3. In Arduino IDE, set the partition scheme to **Huge APP (3MB No OTA)** — required for the ESP Mail Client library
4. Flash to your ESP32

## Libraries needed

- Adafruit BME280 Library
- Adafruit Unified Sensor
- ESP Mail Client
- ESP32 board support package

All available through the Arduino Library Manager.

## Dashboard

Once running, open a browser on the same network and go to `http://esp32.local` or the IP address printed to the serial monitor.

## Notes

- Uses a Gmail app password, not your regular Gmail password — generate one at myaccount.google.com/apppasswords
- Set `#define SKIP_WARMUP true` in the main sketch to bypass the MQ135 warmup delay during testing
- Sea-level pressure for altitude calculation is set manually via `SEALEVELPRESSURE_HPA` — update this to your local pressure for accurate altitude readings
