void manageProcess(){
  static unsigned long lastPoll;

  received = readModem();

  if (isGpsResult(received)) {
    String msgToHandle = received.substring(received.indexOf("+CGNSINF:"), received.indexOf("\r\n\r"));
    Serial.println(msgToHandle);
    parseCGNSINF(msgToHandle);
  }  

  if (millis() - lastPoll > 15000) {
    Serial.println("polling GPS");
    GetGpsCoordinates();
    lastPoll = millis();
  }
}

bool isGpsResult(String msgToHandle){
  return msgToHandle.indexOf("+CGNSINF:") != -1;
}

void parseCGNSINF(String input) {
    // Remove the prefix "+CGNSINF: " to get the raw data
    int startIndex = input.indexOf(":") + 2;
    if (startIndex == -1) return;  // Return if not found

    input = input.substring(startIndex); // Extract only the data part
    
    // Array to store parsed values
    String values[20];  
    int index = 0;

    // Tokenize the input string
    int lastPos = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ',' || i == input.length() - 1) {
            if (i == input.length() - 1) i++;  // Include last character
            values[index++] = input.substring(lastPos, i);
            lastPos = i + 1;
        }
    }
    
    int fixStatus = values[8].toInt();
    int gnssUsed = values[15].toInt();
  
    checkSignalQuality(fixStatus, gnssUsed);
}

void checkSignalQuality(int available, int numberOfSatelites){
  if (available = 1 && numberOfSatelites >= 3)  {
    correctPosition = true;
    digitalWrite(positionAvailableLEDPin, true);
  }
  else {
    correctPosition = false;
    digitalWrite(positionAvailableLEDPin, false);
    Serial.println("Position unusable");
  }
}