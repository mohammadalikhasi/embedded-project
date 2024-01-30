#include <LiquidCrystal_I2C.h>

#define NUM_CATEGORIES 4
#define MAX_DISTANCE 10
#define BUZZER_PIN 8
#define TRIGER_PIN 9
#define ECHO_PIN 10


LiquidCrystal_I2C lcd(0x27,16,2);  
int prediction;
int distance;

void usart_setup(){
  Serial.begin(115200);
  delay(2000);
}

void usart(int type) {
  Serial.println(type);
  delay(2000);
}

void buzzer_setup(){ 
   pinMode(BUZZER_PIN, OUTPUT); 
}

void buzzer(int type){
  
  tone(BUZZER_PIN, type*1000);
  delay(250);
  noTone(BUZZER_PIN);
}

unsigned int model() {
  return random(NUM_CATEGORIES)+1;
}

void distance_sensor_setup() {
  pinMode(TRIGER_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);
}

unsigned int distance_sensor() {
    long duration; 
    digitalWrite(TRIGER_PIN, LOW); 
    delayMicroseconds(2); 
    digitalWrite(TRIGER_PIN, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(TRIGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH); 
    return duration*0.034/2;
}

void lcd_setup(){
  lcd.init();
  lcd.clear();         
  lcd.backlight();
}

void lcd_print(char line1[16], int line2) { 
  lcd.setCursor(0, 0);   
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void setup() {
  lcd_setup();
  distance_sensor_setup();
  buzzer_setup();
  usart_setup();
}

void loop() {
    distance = distance_sensor();
    if (distance < MAX_DISTANCE){
       prediction = model();
       lcd_print("Type:", prediction);
       buzzer(prediction);
       usart(prediction);
       delay(1000);
    }
}