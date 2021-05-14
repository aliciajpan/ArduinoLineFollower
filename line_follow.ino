const int senseRight = A0; 
const int senseLeft = A1; 
byte motorPin[] = {3, 4, 5, 6};
int counter = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(senseRight, INPUT_PULLUP);
  pinMode(senseLeft, INPUT_PULLUP);
  for (int x=0; x<4; x++) {
    pinMode(motorPin[x], OUTPUT); 
  } 
}

void loop() {
  int proximityADCRight = analogRead(senseRight);
  int proximityADCLeft = analogRead(senseLeft);
  float proximityVRight = (float)proximityADCRight * 5.0 / 1023.0;
  float proximityVLeft = (float)proximityADCLeft * 5.0 / 1023.0;
  
  Serial.println(String(proximityVRight) + " and " + String(proximityVLeft));

  if (proximityVLeft >= 0.5 && proximityVRight >= 0.5) {
    drive(255, 0.5);
  } else if (proximityVLeft < 0.5 && proximityVRight >= 0.5) {
    turn(255,"r", 1);
  } else if (proximityVLeft >= 0.5 && proximityVRight < 0.5) {
    turn(255,"l", 1);
  } else {
    Serial.println("AM LOST");
    turn(255,"r", 0.5);
  }
}

void drive(int vel, int wait) { 
  analogWrite(motorPin[0], vel);
  analogWrite(motorPin[2], vel);
}

void turn(int vel, String dir, int wait) { 
  if (dir == "r") {
    analogWrite(motorPin[0], 0);
    analogWrite(motorPin[2], vel);
  } else if (dir == "l") {
    analogWrite(motorPin[0], vel);
    analogWrite(motorPin[2], 0);
  }
}
