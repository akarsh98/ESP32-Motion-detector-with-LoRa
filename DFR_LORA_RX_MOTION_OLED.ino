#include <SPI.h>
#include <LoRa.h>

#define ss 27
#define rst 26
#define dio0 13

void setup() {
  Serial.begin(115200);
  while (!Serial);
 pinMode(2,OUTPUT);
  LoRa.setPins(ss, rst, dio0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void loop() {

}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");
  // read packet
  for (int i = 0; i < packetSize; i++) {
    if((char)LoRa.read()=='N')
    {
      Serial.print("led");
      digitalWrite(2,HIGH);
      delay(2222);
    }
    else
    {
      Serial.println("band");
      digitalWrite(2,LOW);
    }
  }

}

