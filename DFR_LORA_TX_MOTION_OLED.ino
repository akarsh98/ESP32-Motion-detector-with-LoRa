#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     9 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ss 27
#define rst 26
#define dio0 22
int counter = 0;
const int sensorpin = 25;
int buttonState = 0; 

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  pinMode(sensorpin,INPUT);
  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
    if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
  
  display.display();
  delay(2);
  display.clearDisplay();
}

void loop() {
  buttonState = digitalRead(sensorpin);

  if (buttonState == HIGH) {
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("Motion"));
    display.setCursor(0,20); 
    display.print("Detected");
    display.display();
    LoRa.beginPacket();
    LoRa.print("ON");
    LoRa.endPacket();
  } else {
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("Motion"));
    display.setCursor(0,20); 
    display.print("Stable");
    display.display();
    LoRa.beginPacket();
    LoRa.print("OFF");
    LoRa.endPacket();
  }

  delay(1000);
}
