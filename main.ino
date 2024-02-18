#include "DHTStable.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
DHTStable DHT;

#define DHT22_PIN       2
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct
{
    uint32_t total;
    uint32_t ok;
    uint32_t crc_error;
    uint32_t time_out;
    uint32_t connect;
    uint32_t ack_l;
    uint32_t ack_h;
    uint32_t unknown;
} counter = { 0,0,0,0,0,0,0,0};


void setup()
{
  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");

      // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE); 
}

void loop()
{

    uint32_t start = micros();
    int chk = DHT.read22(DHT22_PIN);
    uint32_t stop = micros();

    // DISPLAY DATA
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(",\t");
    Serial.print(DHT.getTemperature(), 1);

    // DISPLAY COUNTERS
    delay(2000);
    oled.clearDisplay();

    oled.setCursor(0, 10);        // position to display
    oled.print(DHT.getHumidity());
    oled.setCursor(66, 10); 
    oled.print("%");
  
    oled.setCursor(0, 40);        // position to display
    oled.print(DHT.getTemperature());
    int offsetX = 63;
    int offsetY = 42;
    float radius = 2;

    for(int i = 0; i <= 11; i++) {
        const float angle = 2 * PI / 12 * i;
        int posX = round(cos(angle) * radius) + offsetX;
        int posY = round(sin(angle) * radius) + offsetY;
        oled.drawPixel(posX,posY, WHITE);
    }

    oled.setCursor(67, 40);
    oled.print("C");
    oled.display();               // show on OLED
}


// -- END OF FILE --

