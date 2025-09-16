int redPin = 9;
int greenPin =10;
int bluePin = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void loop() {
  // put your main code here, to run repeatedly:
  setColor(255,0,0);
  delay(2000);
  setColor(0,255,0);
  delay(2000);
  setColor(0,0,255);
  delay(2000);
  setColor(255,255,0);
  delay(2000);
  setColor(255,0,255);
  delay(2000);
  setColor(0,255,255);
  delay(2000);
  setColor(255,255,255);
  delay(2000);
  setColor(0,0,0);
  delay(2000);
}

//group 6 2023-14669
