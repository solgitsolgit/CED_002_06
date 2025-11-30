#define ENA 6
#define EN1 7
#define EN2 3
#define EN3 4
#define EN4 2
#define ENB 5

#define LT_MODULE_L A2
#define LT_MODULE_F A1
#define LT_MODULE_R A0

#define CAR_DIR_ST 1
#define CAR_DIR_FW 2
#define CAR_DIR_LF 3
#define CAR_DIR_RF 4

int speed = 200;
int g_carDirection = CAR_DIR_ST;

void init_line_tracer_modules(){
  pinMode(LT_MODULE_L, INPUT);
  pinMode(LT_MODULE_F, INPUT);
  pinMode(LT_MODULE_R, INPUT);
}

bool lt_isLeft()
{
  int ret = analogRead(LT_MODULE_L);
  Serial.print("left: ");
  Serial.print(ret);
  return (ret > 200) ? (true) : (false);
}

bool lt_isRight()
{
  int ret = analogRead(LT_MODULE_R);
  Serial.print("right: ");
  Serial.println(ret);
  return (ret > 200) ? (true) : (false);
}

bool lt_isForward()
{
  int ret = analogRead(LT_MODULE_F);
  Serial.print(" forward: ");
  Serial.print(ret);
  return (ret > 200) ? (true) : (false);
}

void lt_mode_update()
{
  bool ll = lt_isLeft();
  bool ff = lt_isForward();
  bool rr = lt_isRight();

  if (ll && ff && rr)
  {
    g_carDirection = CAR_DIR_ST;
  }
  else if (!ll && !ff && !rr)
  {
    g_carDirection = CAR_DIR_ST;
  }

  else if (ll)
  {
    g_carDirection = CAR_DIR_LF;
  }
  else if (rr)
  {
    g_carDirection = CAR_DIR_RF;
  }
  else if (ff)
  {
    g_carDirection = CAR_DIR_FW;
  }
}

void car_update()
{
  Serial.print("Car update: ");
  Serial.print(g_carDirection);
  if (g_carDirection == CAR_DIR_FW) // 전진
  {
    Serial.print("Forward   ");
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, speed);
    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, speed);
  }

  if (g_carDirection == CAR_DIR_LF) // 좌회전
  {
    Serial.print("Left   ");
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, speed);
    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, speed);
  }

  if (g_carDirection == CAR_DIR_RF) // 우회전
  {
    Serial.print("Right   ");
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, speed);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, speed);
  }

  if (g_carDirection == CAR_DIR_ST) // 정지
  {
    Serial.print("Stop   ");
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, 0);
  }
  
}

void setup() {
  Serial.begin(9600);
  init_line_tracer_modules();

  pinMode(ENA, OUTPUT); // ENA
  pinMode(EN1, OUTPUT); // EN1
  pinMode(EN2, OUTPUT); // EN2
  pinMode(ENB, OUTPUT); // ENB
  pinMode(EN3, OUTPUT); // EN3
  pinMode(EN4, OUTPUT); // EN4
}

void loop(){
  lt_mode_update();
  car_update();
  delay(100);
  }