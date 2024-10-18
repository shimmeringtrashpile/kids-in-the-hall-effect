const int hallPin = 2; // Hall effect sensor pin
const int ledPin = 13; // LED pin
int hallState = 0; // Hall effect sensor state

void setup() {
  // put your setup code here, to run once:
  // set the hallPin as an input
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // turn on the internal pull-up resistor
  digitalWrite(hallPin, HIGH);

  // initialize the serial communication
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
