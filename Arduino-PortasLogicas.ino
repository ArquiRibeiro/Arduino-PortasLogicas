const int maxAnalogRead = 675;
const int displayPins[] = {2, 3, 4};
const int numberOfGates = sizeof(displayPins) / sizeof(displayPins[0]);
const uint8_t logicGateSelectorOutput = A0;
const int input1Pin = 13;
const int input2Pin = 12;
const int selectedLogicGateOutputPin = 11;

bool input1 = false;
bool input2 = false;
int selectedLogicGate= -1;

void updateDisplay(int selectedLogicGate){
  for(int i = 0; i < numberOfGates; i++){
    if(i == selectedLogicGate){
      digitalWrite(displayPins[i], LOW);
    }

    else{
      digitalWrite(displayPins[i], HIGH);
    }
  }
}

void runLogicGate(bool input1, bool input2, int selectedLogicGate){
  Serial.println((String)"Input1:" + input1 + (String)" - Input2:" + input2);
  switch (selectedLogicGate) {
    case 0:
      if(input1 == false){
        digitalWrite(selectedLogicGateOutputPin, HIGH);
      }

      else{
        digitalWrite(selectedLogicGateOutputPin, LOW);
      }
      break;
    
    case 1:
      if(input1 == true || input2 == true){
        digitalWrite(selectedLogicGateOutputPin, HIGH);
      }

      else{
        digitalWrite(selectedLogicGateOutputPin, LOW);
      }
      break;
    
    case 2:
      if(input1 == true && input2 == true){
        digitalWrite(selectedLogicGateOutputPin, HIGH);
      }

      else{
        digitalWrite(selectedLogicGateOutputPin, LOW);
      }
      break;
  }
}

void setup(){
  Serial.begin(9600);

  for(int i = 0; i < numberOfGates; i++){
    pinMode(displayPins[i], OUTPUT);
    //digitalWrite(i, HIGH);
  }
  
  pinMode(selectedLogicGateOutputPin, OUTPUT);
}

void loop(){
  if(selectedLogicGate != (analogRead(logicGateSelectorOutput)) / (maxAnalogRead / numberOfGates)){
    selectedLogicGate = (analogRead(logicGateSelectorOutput)) / (maxAnalogRead / numberOfGates);
    updateDisplay(selectedLogicGate);
  }
  
  input1 = (digitalRead(input1Pin) == LOW) ? false : true;
  
  input2 = (digitalRead(input2Pin) == LOW) ? false : true;

  runLogicGate(input1, input2, selectedLogicGate);
  delay(100); //REMOVER DEPOIS
}