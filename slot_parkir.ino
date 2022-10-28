/////////////////////////////////////////////////////////////////
//                   Dibuat Oleh : Mr. Sottong                 //
/////////////////////////////////////////////////////////////////



#include <Servo.h>    //Menambahkan Library Motor Servo
#include <U8x8lib.h>  //Menambahkan Library OLED

#define pinIRin 2     //PIN IR pintu masuk
#define pinIRout 3    //PIN IR pintu keluar
#define PinServo 9    //PIN Motor Servo
#define LEDM 5        //PIN LED Merah
#define LEDH 6        //PIN LED Hijau

#define tertutup 0    //palang pintu tertutup
#define terbuka 90    //palang pintu terbuka

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(12, 11, U8X8_PIN_NONE);   // OLEDs without Reset of the Display
Servo myservo; //Class Servo

int counter = 4; 
int lastState = 4;

void setup() {
  u8x8.begin();
  u8x8.setPowerSave(0);
  
  myservo.attach(PinServo); //
  myservo.write(0);
  
  pinMode(pinIRin, INPUT);
  pinMode(pinIRout, INPUT);
  pinMode(LEDM, OUTPUT);
  pinMode(LEDH, OUTPUT);
  Serial.begin (9600);
   
  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
  u8x8.drawString(1, 2, "SISA");
  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
  u8x8.drawString(1, 4, "SLOT");
  u8x8.inverse();
  u8x8.setFont(u8x8_font_inb33_3x6_n);
  u8x8.setCursor(11,1);
  u8x8.print("4");
  u8x8.noInverse();
  digitalWrite(LEDH, LOW);
  attachInterrupt(digitalPinToInterrupt(pinIRout), handleInterrupt, FALLING);  
  attachInterrupt(digitalPinToInterrupt(pinIRin), handleInterrupt1, FALLING); 
}

void loop() {
  if (counter == 0)
  {
    digitalWrite(LEDM, LOW);
    digitalWrite(LEDH, HIGH);
  }
  if (counter != 0){
    digitalWrite(LEDH, LOW);
    digitalWrite(LEDM, HIGH);
  }
  if (lastState > counter) {
    myservo.write(terbuka);
    delay(3000);
    myservo.write(tertutup);
    lastState = counter;
  }
  if (lastState < counter){
    lastState = counter;
  }
  
}

void handleInterrupt() {
  counter++;
  if(counter > 4){
    counter = 4;
  }
  
  u8x8.inverse();
  u8x8.setFont(u8x8_font_inb33_3x6_n);
  u8x8.setCursor(11,1);
  u8x8.print(counter);
}

void handleInterrupt1() {
  counter--;
  if(counter < 0){
    counter = 0;
  }
  
  u8x8.inverse();
  u8x8.setFont(u8x8_font_inb33_3x6_n);
  u8x8.setCursor(11,1);
  u8x8.print(counter);
}
