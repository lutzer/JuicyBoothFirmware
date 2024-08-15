#include <FastLED.h>  // include FastLED *before* Artnet

// Please include ArtnetEther.h to use Artnet on the platform
// which can use both WiFi and Ethernet
#include <ArtnetEther.h>
// #include <ArtnetNativeEther.h>  // only for Teensy 4.1
// this is also valid for other platforms which can use only Ethernet
// #include <Artnet.h>

#define NUM_LEDS_PER_STRIP 1024

#define STRIP1_PIN 30
#define STRIP2_PIN 31
#define STRIP3_PIN 32

#define STRIP1_UNIVERSE 1
#define STRIP2_UNIVERSE 2
#define STRIP3_UNIVERSE 3

// Ethernet stuff
const IPAddress ip(192, 168, 0, 201);
uint8_t mac[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};

ArtnetReceiver artnet;

CRGB leds1[NUM_LEDS_PER_STRIP];
CRGB leds2[NUM_LEDS_PER_STRIP];
CRGB leds3[NUM_LEDS_PER_STRIP];

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println("init");

    FastLED.addLeds<NEOPIXEL, STRIP1_PIN>(leds1, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, STRIP2_PIN>(leds2, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, STRIP3_PIN>(leds3, NUM_LEDS_PER_STRIP);

    Ethernet.begin(mac, ip);
    artnet.begin();

    artnet.forwardArtDmxDataToFastLED(STRIP1_UNIVERSE, leds1, NUM_LEDS_PER_STRIP);
    artnet.forwardArtDmxDataToFastLED(STRIP2_UNIVERSE, leds1, NUM_LEDS_PER_STRIP);
    artnet.forwardArtDmxDataToFastLED(STRIP3_UNIVERSE, leds1, NUM_LEDS_PER_STRIP);

    Serial.println("init:complete");
}

void loop() {
    artnet.parse();  // check if artnet packet has come and execute callback
    FastLED.show();
}
