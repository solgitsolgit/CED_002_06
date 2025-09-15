int dataRead = 0;
String sentence;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Serial start");
}

void loop() {
  if(Serial.available()){

    dataRead = Serial.read();
    Serial.print("input ASCII data is : ");
    Serial.println(dataRead);
    Serial.print("input ASCII character is : ");
    Serial.write(dataRead);
    Serial.println();

    //sentence = Serial.readString();
    //Serial.print("input sentence is : ");
    //Serial.println(sentence);
    //serial.println();

  }
}