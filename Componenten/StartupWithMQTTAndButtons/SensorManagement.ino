void sensorStartup(){
  pinMode(panicButtonPin, INPUT_PULLDOWN);
  pinMode(fuelOpenendPin, INPUT_PULLDOWN);
  pinMode(loadingPin, INPUT_PULLDOWN);
}


void managePanicButton(){
  static bool previousState = false;
  bool state = digitalRead(panicButtonPin);

  if (state != previousState) { // todo only allow toggle when startup completly done
    previousState = state;
    if (state) {
      panicState = !panicState;
      String message = createSensorMessage("Panic", panicState);
      Serial.print("sending message: ");
      Serial.println(message);
      sendMessage(message);
      
      delay(20);
    }
  }
}

void manageFueling(){
  static bool previousState = false;
  bool state = digitalRead(fuelOpenendPin);

  if (state != previousState) { // todo only allow toggle when startup completly done
    previousState = state;    
    if (state) {
      fuelState = !fuelState;
      String message = createSensorMessage("Fuel", fuelState);
      Serial.print("sending message: ");
      Serial.println(message);
      sendMessage(message);

      delay(20);
    }
  }
}

void manageLoading(){
  static bool previousState = false;
  bool state = digitalRead(loadingPin);

  if (state != previousState) {
    previousState = state;
    loadingState = !state; //gesloten koffer = status hoog = loading state false. om consistent te zijn met paniek en fuel dat true 'slecht' is

    String message = createSensorMessage("Loading", loadingState);
    Serial.print("sending message: ");
    Serial.println(message);
    sendMessage(message);

    delay(20);
    
  }
}