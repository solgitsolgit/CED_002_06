const int RED = 5;
int i = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(i<20)
  {
    digitalWrite(RED,1);
    delay(100-5*i);
    digitalWrite(RED,0);
    delay(100-5*i);
    i = i+1;
  }
  else
  {
    digitalWrite(RED,1);
    delay(1);
    digitalWrite(RED,0);
    delay(1);
  }
}

// group 6 2023-14669
