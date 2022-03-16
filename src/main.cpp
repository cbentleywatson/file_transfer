#include <Arduino.h>
//#include <file_transmitter.h>
#include <flow_transmitter.h>
void setup()
{
  Serial.begin(115200);
  // Receiver modem;
  // modem.init_connection(15000, 100);
}

int count = 1;
void loop()
{
  delay(1000);
  // Serial.println("out");
  if (count == 1)
  {
    Receiver modem1;
    modem1.init_connection(3600000, 100);
    // Serial.print("a");
    // Serial.print("c");
    int rec = modem1.readInt(2000);
    // rec = 19;
    //  unsigned char rec = 1234;
    // COMPLETE DO NOT TOUch!!!
    modem1.send_int(rec);
  

    modem1.run_server(DEFAULT_SERVER_TIMEOUT, DEFAULT_SERVER_LISTEN_TIMEOUT);
    //     file_transmitter receiver;
    // Serial.print("q");
    // Serial.print("a");
    // Serial.print("c");

    //  receiver.init_server();
    // receiver.init_connection();
    // Serial.read
    count++;
  }
  // Serial.print('e');
  //  Serial.println("ll");
}