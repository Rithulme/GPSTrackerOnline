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
          if (previousState != mainState) {
            previousState = mainState;
            previousStep = millis();
            commandOk = sendModemAndProcessResponse("AT+CNACT=1,internet.proximus.be","PDP: ACTIVE");
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
          if (previousState != mainState) {
            previousState = mainState;
            previousStep = millis();
            commandOk = sendModemAndProcessResponse("AT+SMCONF=\"URL\"," + serverURL + "," + serverPort,"OK");
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
          if (previousState != mainState) {
            previousState = mainState;
            previousStep = millis();
            commandOk = sendModemAndProcessResponse("AT+SMCONF=\"CLIENTID\",\"ESP32\"","OK");
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
          if (previousState != mainState) {
            previousState = mainState;
            previousStep = millis();
            commandOk = sendModemAndProcessResponse("AT+SMCONN","OK");
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
          digitalWrite(startupLEDPin, true);
          manageProcess();

          break;
      }
}

bool sendModemAndProcessResponse(String ATcomm, String returnMsg){
  Serial.print("Sending AT command:");Serial.println(ATcomm);
  int retries=0;
  String receivedMsg = "";
  bool returnFound = false;
  Serial2.println(ATcomm);
  delay(1000);
  while(retries < 10 && receivedMsg.indexOf(returnMsg) == -1){
    receivedMsg = readModem();
    retries++;
    Serial.print("Try to receive expected return message:");Serial.print(returnMsg);Serial.print(" Attempt:");Serial.println(retries);
    delay(1000);
  }
  if(retries > 10) {
    Serial.print(returnMsg);Serial.print(" NOT found in return after sending command: ");Serial.print(ATcomm);Serial.println(" Sorry .... timed out / failed \n....RESET program, hang on for 10s");
    //reset the module so we won't get stuck in for example the send SMS terminal mode
    mainState = 0;
    return false;
  } else {
    Serial.print(returnMsg);Serial.print(" found in return after sending command: ");Serial.print(ATcomm),Serial.println(" succesful, all done!");
    return true;
  }
}

String readModem(){
  String msg="";
  bool lf = false;
  while (Serial2.available()) {
    byte byteUart = Serial2.read();
        
    msg += (char)byteUart; //typecast byte to char
    if(byteUart == '\n'){      
      lf = true;
    }
  }
  if(lf){
    return msg;
  }
}

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

void sendMessage(String message){
  int size = message.length();

  sendModemAndProcessResponse("AT+SMPUB=\"update\\test\",\"" + String(size) +  "\",1,1","AT+SMPUB");
  sendModemAndProcessResponse(message,"OK");
}

void GetGpsCoordinates(){
  String GPSCommand = "AT+CGNSINF";
  Serial.println("Getting gps coordinates");
  Serial2.println(GPSCommand);
}