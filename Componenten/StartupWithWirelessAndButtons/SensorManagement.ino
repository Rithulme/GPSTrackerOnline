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
      if (panicState) {
        //todo send info to node red
      }
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
      if (fuelState) {
        //todo send info to node red
      }
      delay(20);
    }
  }
}

void manageLoading(){
  static bool previousState = false;
  bool state = digitalRead(loadingPin);

  if (state != previousState) {
    previousState = state;
    //send to node red
  }
}