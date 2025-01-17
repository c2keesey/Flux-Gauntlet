#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <TimeLib.h>
#include <sunset.h>
#include <WiFiUdp.h>

// TODO: use onebutton.h
#include "src/config/config.h"
#include "src/effects/house/h_EffectsHandler.h"
#include "src/utils/timing.h"
#include "src/oled/OLEDControl.h"
#include "src/config/wifi_config.h"
#include "src/effects/shared/effects/Twinkle.h"

// Env vars
static const bool TIME_OF_DAY_ENABLED = true;

// Wifi and Timing
SunSet sun;
double latitude = LATITUDE;
double longitude = LONGITUDE;
WiFiUDP Udp;
unsigned int localPort = 8888; // local port to listen for UDP packets
static const char ntpServerName[] = "pool.ntp.org";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];

// OLED
OLEDControl oledControl;

double fps = 0;
int displayRate = 1000;
int lastUpdateDisplay = 0;

// LEDs
CRGB bfr_leds[NUM_BFR] = {0};
CRGB bfl_leds[NUM_BFL] = {0};
CRGB *leds[NUM_BFL + NUM_BFR] = {0};
int hue = 100;
int maxBrightness = 255;

// Effects
h_EffectsHandler effectsHandler;

// LEDs

void sendStats()
{
    Serial.print("FPS: ");
    Serial.print(fps);
    Serial.print(" Brite: ");
    Serial.print(calculate_max_brightness_for_power_mW(maxBrightness, MAX_STRIP_DRAW));
}

void setupWiFi()
{
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("\nFailed to connect to WiFi");
    }
}

void testWiFiConnection()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi is still connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("WiFi connection lost. Attempting to reconnect...");
        setupWiFi();
    }
}

time_t getNtpTime()
{
    IPAddress ntpServerIP;
    while (Udp.parsePacket() > 0)
        ;
    Serial.println("Transmit NTP Request");
    WiFi.hostByName(ntpServerName, ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500)
    {
        int size = Udp.parsePacket();
        if (size >= NTP_PACKET_SIZE)
        {
            Serial.println("Receive NTP Response");
            Udp.read(packetBuffer, NTP_PACKET_SIZE);
            unsigned long secsSince1900;
            secsSince1900 = (unsigned long)packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long)packetBuffer[43];
            return secsSince1900 - 2208988800UL + (UTC_OFFSET * SECS_PER_HOUR);
        }
    }
    Serial.println("No NTP Response :-(");
    return 0;
}

void sendNTPpacket(IPAddress &address)
{
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    packetBuffer[0] = 0b11100011;
    packetBuffer[1] = 0;
    packetBuffer[2] = 6;
    packetBuffer[3] = 0xEC;
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    Udp.beginPacket(address, 123);
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}

bool isActivationTime()
{
    sun.setCurrentDate(year(), month(), day());
    int sunset = static_cast<int>(sun.calcSunset());
    int activationStart = sunset - 15;
    int activationEnd = activationStart + 480; // 8 hours after activation start

    int currentMinute = hour() * 60 + minute();

    // Handle case where activation period crosses midnight
    if (activationEnd > 1440)
    {
        return (currentMinute >= activationStart || currentMinute < (activationEnd - 1440));
    }
    else
    {
        return (currentMinute >= activationStart && currentMinute < activationEnd);
    }
}

void setup()
{
    Serial.begin(9600);
    delay(1000);

    pinMode(PIN_BFL, OUTPUT);
    pinMode(PIN_BFR, OUTPUT);

    FastLED.addLeds<WS2812, PIN_BFL, GRB>(bfl_leds, NUM_BFL);
    FastLED.addLeds<WS2812, PIN_BFR, GRB>(bfr_leds, NUM_BFR);

    for (int i = 0; i < NUM_BFL; i++)
    {
        leds[i] = &bfl_leds[i];
    }
    for (int i = 0; i < NUM_BFR; i++)
    {
        leds[NUM_BFL + i] = &bfr_leds[NUM_BFR - i - 1];
    }
    FastLED.clear();
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_STRIP_DRAW);

    // OLED
    oledControl.init();
    oledControl.addProjectName("Flux Arch");

    // Effects
    effectsHandler.setupEffectLibrary();

    // WiFi setup
    setupWiFi();

    // SunSet library setup
    sun.setPosition(latitude, longitude, UTC_OFFSET);
    sun.setTZOffset(UTC_OFFSET);
    setSyncProvider(getNtpTime);
    setSyncInterval(60 * 60);

    Udp.begin(localPort);

    // Serial
    randomSeed(analogRead(0));

    printTimeDebug();

    BaseEffect *effect = new Twinkle(20, &rainbow_cp, true, 20);
    effect->trigger();
    effectsHandler.addEffect(effect);
}

// Add this function to format the current time
String getFormattedTime()
{
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour(), minute(), second());
    return String(buffer);
}

void printTimeDebug()
{
    sun.setCurrentDate(year(), month(), day());
    int sunrise = static_cast<int>(sun.calcSunrise());
    int sunset = static_cast<int>(sun.calcSunset());

    Serial.println("Time Debug:");
    Serial.print("UTC Offset: ");
    Serial.print(UTC_OFFSET);
    Serial.println(" hours");

    Serial.print("Current time (local): ");

    Serial.println(getFormattedTime());

    Serial.print("Sunrise time (local): ");
    Serial.print(sunrise / 60);
    Serial.print(":");
    Serial.printf("%02d", sunrise % 60);
    Serial.println();

    Serial.print("Sunset time (local): ");
    Serial.print(sunset / 60);
    Serial.print(":");
    Serial.printf("%02d", sunset % 60);
    Serial.println();

    Serial.println("-------------------");
}

double calculateFPS(unsigned long currentLoopStart, unsigned long lastLoopStart)
{
    if (lastLoopStart != 0)
    {
        double loopTime = (currentLoopStart - lastLoopStart) / 1000.0;
        if (loopTime > 0)
        {
            return FramesPerSecond(loopTime);
        }
    }
    return 0.0;
}

void activateFireworks()
{

    EVERY_N_SECONDS(random(2, 5))
    {
        effectsHandler.triggerEffect(0);
    }

    EVERY_N_MINUTES(random(5, 10))
    {
        for (int i = 0; i < 10; i++)
        {
            effectsHandler.triggerEffect(0);
        }
    }
}

void loop()
{
    static unsigned long lastActivationCheck = 0;
    static bool isActive = false;
    static unsigned long lastLoopStart = 0;

    unsigned long currentTime = millis();

    // Check activation status every 10 minutes
    if (currentTime - lastActivationCheck >= 600000 || lastActivationCheck == 0)
    {
        testWiFiConnection();
        if (TIME_OF_DAY_ENABLED)
        {
            isActive = isActivationTime();
        }
        else
        {
            isActive = true;
        }
        lastActivationCheck = currentTime;

        // Clear and turn off LEDs when transitioning to inactive state
        if (!isActive)
        {
            FastLED.clear();
            FastLED.show();
            FastLED.setBrightness(0);
        }
        else
        {
            // Restore brightness when becoming active
            FastLED.setBrightness(BRIGHTNESS);
        }
    }

    if (isActive)
    {
        // FPS
        unsigned long loopStart = millis();
        fps = calculateFPS(loopStart, lastLoopStart);
        lastLoopStart = loopStart;

        // Effects
        // activateFireworks();

        effectsHandler.drawFrame();
        FastLED.show(); // Make sure to show the updated LEDs
    }
    else
    {
        delay(60000); // Check every 1 minute if it's activation time
    }

    EVERY_N_MINUTES(1)
    {
        testWiFiConnection();
    }
}
