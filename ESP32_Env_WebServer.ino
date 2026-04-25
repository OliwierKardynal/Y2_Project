#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <ESPmDNS.h>
#include <ESP_Mail_Client.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "secrets.h"

#include "homepage.h"

// ===== WiFi =====
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

// ===== Email =====
const char *smtpServer = "smtp.gmail.com";
const int smtpPort = 465;
const char *senderEmail = EMAIL_ADDRESS;
const char *senderAppPassword = EMAIL_PASS;
const char *recipientEmail = EMAIL_RECIPIENT;

// ===== Web Server =====
WebServer server(80);

// ===== BME280 =====
#define SEALEVELPRESSURE_HPA 1002
Adafruit_BME280 bme;

// ===== MQ135 =====
#define MQ135_PIN 32

// ===== Alert state =====
bool tempAlertSent = false;
bool airAlertSent = false;

unsigned long lastCheckMs = 0;
const unsigned long checkIntervalMs = 5000;

// ===== MQ135 warmup =====
// Set true to skip the 10-minute warmup (for testing only)
#define SKIP_WARMUP false
const unsigned long WARMUP_MS = 10UL * 60UL * 1000UL;

// SMTP session object
SMTPSession smtp;

// callback for smtp status
void smtpCallback(SMTP_Status status) {
  Serial.println(status.info());

  if (status.success()) {
    Serial.println("email sent");
  } else {
    Serial.println("email failed");
  }
}

bool sendWarningEmail(const String &subject, const String &body) {
  Session_Config config;
  config.server.host_name = smtpServer;
  config.server.port = smtpPort;
  config.login.email = senderEmail;
  config.login.password = senderAppPassword;
  config.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "ESP32 monitor";
  message.sender.email = senderEmail;
  message.subject = subject;
  message.addRecipient("recipient", recipientEmail);

  message.text.content = body.c_str();
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  smtp.callback(smtpCallback);

  if (!smtp.connect(&config)) {
    Serial.println("smtp connect failed");
    return false;
  }

  if (!MailClient.sendMail(&smtp, &message, true)) {
    Serial.print("sendMail error: ");
    Serial.println(smtp.errorReason());
    return false;
  }

  return true;
}

void checkAlerts(float temp, float hum, float pres, float alt, int mq135) {
  // temperature alert
  if (temp > 50.0 && !tempAlertSent) {
    String subject = "ESP32 warning: high temperature";
    String body =
        "Temperature threshold exceeded.\n\n"
        "Temperature: " + String(temp, 1) + " C\n" +
        "Humidity: " + String(hum, 1) + " %\n" +
        "Pressure: " + String(pres, 1) + " hPa\n" +
        "Altitude: " + String(alt, 1) + " m\n" +
        "Air quality ADC: " + String(mq135) + "\n";

    if (sendWarningEmail(subject, body)) {
      tempAlertSent = true;
    }
  }

  if (temp <= 50.0) {
    tempAlertSent = false;
  }

  // air quality alert — suppressed during warmup period
  bool warmedUp = SKIP_WARMUP || (millis() >= WARMUP_MS);
  if (warmedUp && mq135 > 2400 && !airAlertSent) {
    String subject = "ESP32 warning: dangerous air quality";
    String body =
        "Air quality threshold exceeded.\n\n"
        "Temperature: " + String(temp, 1) + " C\n" +
        "Humidity: " + String(hum, 1) + " %\n" +
        "Pressure: " + String(pres, 1) + " hPa\n" +
        "Altitude: " + String(alt, 1) + " m\n" +
        "Air quality ADC: " + String(mq135) + " (Dangerous)\n";

    if (sendWarningEmail(subject, body)) {
      airAlertSent = true;
    }
  }

  if (mq135 <= 2400) {
    airAlertSent = false;
  }
}

String getSensorData() {
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 100.0F;
  float alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  int mq135 = analogRead(MQ135_PIN);

  String aqLabel;
  String aqClass;
  int aqPercent = (mq135 * 100) / 2400;

  if (aqPercent < 0) aqPercent = 0;
  if (aqPercent > 100) aqPercent = 100;

  if (mq135 <= 1000) {
    aqLabel = "Good";
    aqClass = "aq-good";
  } else if (mq135 <= 1600) {
    aqLabel = "Moderate";
    aqClass = "aq-moderate";
  } else if (mq135 <= 2400) {
    aqLabel = "Poor";
    aqClass = "aq-poor";
  } else {
    aqLabel = "Dangerous";
    aqClass = "aq-dangerous";
    aqPercent = 100;
  }

  String data = "";

  // 2x2 stat cards
  data += "<div class='stat-grid'>";
  data += "<div class='stat-card'><div class='stat-label'>Temperature</div><div class='stat-value'>" + String(temp, 1) + "</div><div class='stat-unit'>°C</div></div>";
  data += "<div class='stat-card'><div class='stat-label'>Humidity</div><div class='stat-value'>" + String(hum, 1) + "</div><div class='stat-unit'>%</div></div>";
  data += "<div class='stat-card'><div class='stat-label'>Pressure</div><div class='stat-value'>" + String(pres, 1) + "</div><div class='stat-unit'>hPa</div></div>";
  data += "<div class='stat-card'><div class='stat-label'>Altitude</div><div class='stat-value'>" + String(alt, 1) + "</div><div class='stat-unit'>m</div></div>";
  data += "</div>";

  // Air quality block with horizontal bar
  data += "<div class='aq-section'>";
  data += "<div class='aq-top'><span class='aq-label-text'>Air Quality (MQ135)</span><span class='aq-badge " + aqClass + "'>" + aqLabel + "</span></div>";
  data += "<div class='aq-reading'>" + String(mq135) + "</div>";
  data += "<div class='aq-bar-h'><div class='aq-fill-h " + aqClass + "' style='width:" + String(aqPercent) + "%'></div></div>";
  data += "</div>";

  return data;
}

// root page
void handleRoot() {
  String page = homePagePart1 + getSensorData() + homePagePart2;
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);

  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("mDNS responder started (esp32.local)");
  }

  server.on("/", handleRoot);
  server.onNotFound([]() { server.send(404, "text/plain", "404 - Not Found"); });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  unsigned long now = millis();
  if (now - lastCheckMs >= checkIntervalMs) {
    lastCheckMs = now;

    float temp = bme.readTemperature();
    float hum = bme.readHumidity();
    float pres = bme.readPressure() / 100.0F;
    float alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
    int mq135 = analogRead(MQ135_PIN);

    checkAlerts(temp, hum, pres, alt, mq135);
  }

  delay(2);
}