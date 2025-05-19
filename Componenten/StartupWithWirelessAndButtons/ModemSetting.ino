void modemPowerOn() {
  digitalWrite(PWR_PIN, HIGH);
  delay(1000);  //Datasheet Ton min = 1S
  digitalWrite(PWR_PIN, LOW);
  Serial.println("SIM7000 switched on!");
}

void modemPowerOff() {
  digitalWrite(PWR_PIN, HIGH);
  delay(1500);  //Datasheet Toff min = 1.2S
  digitalWrite(PWR_PIN, LOW);
  Serial.println("SIM7000 switched off!");
}

bool forceModem()
{
  for (int j = 0; j < 20; j++) {
    Serial2.print("AT\r\n");
    String input = Serial2.readString();
    if (input.indexOf("OK") >= 0) {
      Serial.println("Modem responded");
      return true;
    }
  }
    Serial.println("Modem is not online!!!");
    return false;
}

void ManageModemState(){
  static int previousState = -1;
  static unsigned long previousStep;
  bool commandOk = false;
  String message;
  switch(mainState){
    case 0:
      if (previousState != mainState) {
        previousState = mainState;
        previousStep = millis();
      }

      if(millis() - previousStep > 7500){
        mainState = 1;
      }

      break;

    case 1:
      if (previousState != mainState) {
        pinMode(PWR_PIN, OUTPUT);
        digitalWrite(PWR_PIN, LOW);
        modemPowerOff();
        previousStep = millis();
        previousState = mainState;
      }

      if(millis() - previousStep > 7500){        
        mainState = 2;
      }

      break;

    case 2:
      if (previousState != mainState) {
        modemPowerOn();
        previousStep = millis();
        previousState = mainState;
      }

      if(millis() - previousStep > 7500){        
        mainState = 3;
      }

      break;

      case 3:
        previousState = mainState;
        if(forceModem()){
          mainState = 4;
        }
        else {
          Serial.println("Reset modem");
        }

        break;
      
      case 4:
        previousState = mainState;
        message = readModem();

        if(message.indexOf("PSUTTZ") != -1){
        mainState = 5;
        }

        break;
      
      case 5:
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CGNSPWR=1","OK");
          Serial.println("at state 5");
        }       
        
        if(commandOk){
          mainState = 6;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 4;
          }
        }

        break;   

      case 6:
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+SGPIO=0,4,1,1","OK");
          Serial.println("at state 6");
        }       
        
        if(commandOk){
          mainState = 7;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 5;
          }
        }
      
        break;

      case 7:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CIPSHUT","SHUT OK");
          Serial.println("at state 7");
        }       
        
        if(commandOk){
          mainState = 8;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 6;
          }
        } 

        break;  

      case 8:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CSTT=\"internet.proximus.be\"","OK");
          Serial.println("at state 8");
        }       
        
        if(commandOk){
          mainState = 9;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 7;
          }
        }

        break;

      case 9:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CIICR","OK");
          Serial.println("at state 9");
        }       
        
        if(commandOk){
          mainState = 10;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 8;
          }
        }

        break;

      case 10:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessIP("AT+CIFSR");
          Serial.println("at state 10");
        }       
        
        if(commandOk){
          mainState = 11;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 9;
          }
        }

        break;

      case 11:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CIPSHUT","SHUT OK");
          Serial.println("at state 11");
        }       
        
        if(commandOk){
          mainState = 12;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 10;
          }
        }   

      case 12:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CSTT=\"internet.proximus.be\"","OK");
          Serial.println("at state 12");
        }       
        
        if(commandOk){
          mainState = 13;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 11;
          }
        }

      case 13:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessResponse("AT+CIICR","OK");
          Serial.println("at state 13");
        }       
        
        if(commandOk){
          mainState = 14;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 12;
          }
        }

      case 14:
        //try sending command once, if it fails 'commandOk' is always false, after 1 second previous state is reset to trigger command again
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          commandOk = sendModemAndProcessIP("AT+CIFSR");
          Serial.println("at state 14");
        }       
        
        if(commandOk){
          mainState = 15;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 13;
          }
        }

      case 15:
        if (previousState != mainState) {
          previousState = mainState;
          previousStep = millis();
          String tcpCommand = createTCPCommand();
          commandOk = sendModemAndProcessResponse(tcpCommand,"OK");
          Serial.println("at state 15");
        } 
        
        if(commandOk){
          mainState = 16;
        }
        else{
          if (millis() - previousStep > 1000) {
            previousState = 14;
          }
        }

      case 16:
        sendHandshake();
        manageProcess();
        digitalWrite(startupLEDPin, true);
        break;

  }
}