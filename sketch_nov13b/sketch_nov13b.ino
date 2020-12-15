#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"
#include <printf.h>
//Declaremos los pines CE y el CSN
#define CE_PIN 7
#define CSN_PIN 8
 
//Variable con la dirección del canal por donde se va a transmitir
byte direccion1[5] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 };
byte direccion2[5] = { 0xC2, 0xC2, 0xC2, 0xC2, 0xC2 };

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar
uint8_t datos[32];

void setup()
{
  radio.begin();
  Serial.begin(9600); 
  printf_begin();
  //Abrimos el canal de Lectura
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.setAddressWidth(5);
  radio.setRetries(0,3);
  radio.setCRCLength(RF24_CRC_8);
  radio.setChannel(0x02);
  radio.setDataRate(RF24_2MBPS);
  radio.openReadingPipe(0, direccion1);
  radio.openReadingPipe(1, direccion2);
  radio.stopListening();
  radio.printDetails();
}

void loop() {
  datos[0] = 0;
  radio.write(datos, 32);
  delay(500);
  datos[0] = 1;
  radio.write(datos, 32);
  delay(500);
  datos[0] = 2;
  radio.write(datos, 32);
  delay(500);
  datos[0] = 4;
  radio.write(datos, 32);
  delay(500);
}
