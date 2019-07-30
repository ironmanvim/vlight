// 2 for word
// 3 for space
// 4 for new line
#define SENSE_PIN A0 
#define READ_LED 8
#define DECODE_LED 9
#define FINISH_LED 10
void setup() {
  Serial.begin(9600);
  pinMode(READ_LED, OUTPUT);
  pinMode(DECODE_LED, OUTPUT);
  pinMode(FINISH_LED, OUTPUT);
}
unsigned long int now_time = 0;
int first_time_sensed = 0;
int spaced = 0;
int dotted = 0;
void loop() {
  /*if(senseAvailable()) {
    int value = senseData();
    Serial.println(value);
  }*/
  if(senseAvailable()) {
    digitalWrite(READ_LED, HIGH);
    digitalWrite(DECODE_LED, LOW);
    digitalWrite(FINISH_LED, LOW);
    first_time_sensed = 1;
    char value = senseCalculate();
    Serial.print(value);
    now_time = millis();
    spaced = 0;
    dotted = 0;
  }
  digitalWrite(READ_LED, LOW);
  if(millis() - now_time > 100 && first_time_sensed == 1 && spaced == 0) {
    digitalWrite(DECODE_LED, HIGH);
    Serial.print("2");
    spaced = 1;
  }
  if(millis() - now_time > 300 && first_time_sensed == 1 && dotted == 0) {
    digitalWrite(DECODE_LED, HIGH);
    Serial.print("32");
    dotted = 1;
  }
  if(millis() - now_time > 1000 && first_time_sensed == 1) {
    digitalWrite(FINISH_LED, HIGH);
    Serial.print("42");
    first_time_sensed = 0;
    now_time = millis();
  }
}
int senseData() {
  int sum = 0;
  while(analogRead(SENSE_PIN) >= 100) {
    sum++;
    delay(10);
  }
  return sum;
}
int senseAvailable() {
  if(analogRead(SENSE_PIN) >= 100) {
    return 1;
  }
  return 0;
}
char senseCalculate() {
    int value = senseData();
    // >= 6 for 0.05 && >= 25 for 0.2
    if(value >= 8)
      return '1';
    return '0';
}

