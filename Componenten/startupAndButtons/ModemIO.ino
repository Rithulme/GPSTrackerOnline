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

bool sendModemAndProcessIP(String ATcomm){
  Serial.print("Sending AT command:");Serial.println(ATcomm);
  int retries=0;
  String receivedMsg = "";
  Serial2.println(ATcomm);
  delay(1000);
  while(retries < 10 && countOccurence(receivedMsg , '.') < 3){
    receivedMsg = readModem();
    retries++;
    Serial.println("read modem: " + receivedMsg);
    Serial.print("Try to receive expected return message:");Serial.print("Attempt:");Serial.println(retries);
    delay(1000);
  }
  if(retries >= 10) {
    Serial.print("Ip NOT found in return after sending command: ");Serial.print(ATcomm);Serial.println(" Sorry .... timed out / failed \n....RESET program, hang on for 10s");
    //reset the module so we won't get stuck in for example the send SMS terminal mode
    mainState = 0;
    return false;
  } else {
    Serial.print("IP found in return after sending command: ");Serial.print(ATcomm),Serial.println(" succesful, all done!");
    return true;
  }
}

void GetGpsCoordinates(){
  String GPSCommand = "AT+CGNSINF";
  Serial.println("Getting gps coordinates");
  Serial2.println(GPSCommand);
}