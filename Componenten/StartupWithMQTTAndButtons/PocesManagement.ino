void managePollingButton(){
  static bool previousState = false;
  bool state = digitalRead(startPollingButtonPin);

  if (state != previousState) { // todo only allow toggle when startup completly done
    previousState = state;
    if (state) {
      pollingActive = !pollingActive;
      delay(20);
    }
  }
}

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

  managePanicButton();
  manageFueling();
  manageLoading();
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

    JsonDocument message;
    message["Type"] = "Coordinates"; 
    message["Latitude"] = values[3].toFloat();
    message["Longitude"] = values[4].toFloat();
    message["Speed"] = values[6].toFloat();
    message["Course"] = values[7].toFloat();

    // Serialize JSON to a string
    String jsonString;
    serializeJson(message, jsonString);

    if(pollingActive && correctPosition){

      sendMessage(jsonString);

    }  
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

String createSensorMessage(String sensor, bool value){
  JsonDocument messageObject;

  messageObject["Type"] = sensor;
  messageObject["Value"] = value;

  String message;
  serializeJson(messageObject, message);

  Serial.println(message);

  return message;
}