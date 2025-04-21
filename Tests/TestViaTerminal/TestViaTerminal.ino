#define PIN_DTR 25
#define PIN_TX 27
#define PIN_RX 26

#define PWR_PIN 4

#define LED 12

void ForceModem()
{
  for (int j = 0; j < 20; j++) {
    Serial2.print("AT\r\n");
    String input = Serial2.readString();
    if (input.indexOf("OK") >= 0) {
      Serial.printf("Modem responded");
      return;
    }
  }
    Serial.println("Modem is not online!!!");
}


// ESP32 UART0 naar USB op pinnen TXD0 en RXD0
// SIM7000 communiceert op pinnen GSM_TX IO26 GSM_RX op IO27

void modemPowerOn() {
  // power on table 8 pag 24
  digitalWrite(PWR_PIN, HIGH);
  delay(1000);  //Datasheet Ton min = 1S
  digitalWrite(PWR_PIN, LOW);
  ForceModem();
}

void modemPowerOff() {
  // power off table 9 pag 25
  digitalWrite(PWR_PIN, HIGH);
  delay(1500);  //Datasheet Toff min = 1.2S
  digitalWrite(PWR_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 26, 27);
  //Serial2.updateBaudRate(115200);

  delay(1000);
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, LOW);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, 0);
  delay(250);
  digitalWrite(LED, 1);
  Serial.println("testing started!");
  delay(7500);

  modemPowerOff();
  digitalWrite(LED, 1);
  Serial.println("SIM7000 switched off!");
  delay(7500);

  modemPowerOn();
  digitalWrite(LED, 0);
  Serial.println("SIM7000 switched on!");

}

void loop() {
  byte byteUart;

  while (Serial.available()) {
    byteUart = Serial.read();
    Serial2.write(byteUart);
  }

  while (Serial2.available()) {
    byteUart = Serial2.read();
    Serial.write(byteUart);
  }
}
