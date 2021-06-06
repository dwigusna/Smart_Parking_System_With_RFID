//Sertakan library Servo
int button_Pin = 2;
int pos = 0;
int a = 0;
int x_Pin = A1; //Nama alias pin A1 yaitu xPin
int y_Pin = A0; //Nama aliasa pin A0 yaitu yPin
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD
#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
int x_Position = 0;
int y_Position = 0;
int buttonState = 0;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
/* Set your new UID here */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
MFRC522::MIFARE_Key key;
Servo myservo;  
void setup() {
  myservo.attach(3);  // servo terhubung pin 9
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(x_Pin, INPUT);
  pinMode(y_Pin, INPUT);
  //deklarasi buttonPin sebagai input dengan kondisi pull-up
  pinMode(button_Pin, INPUT);
  digitalWrite(button_Pin,HIGH);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("TEMPELKAN KARTU"); 
  lcd.setCursor(0, 1); 
  lcd.print("KTM ANDA");
  delay(1000);
}
 
void loop() {
myservo.write(170);
x_Position = analogRead(x_Pin);y_Position = analogRead(y_Pin);
buttonState = digitalRead(button_Pin);
//menampilkan hasil pada serial monitor
Serial.print("X: ");Serial.print(x_Position);
Serial.print(" | Y: ");Serial.print(y_Position);
Serial.print(" | Button: ");Serial.println(buttonState);
int nilai = map(x_Position,0,1023,7,12);
Serial.println(nilai);
digitalWrite (nilai,1);

 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "07 56 14 D8") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    a=a+1;
    myservo.write(30);
    delay(100);
    lcd.clear();
    lcd.print("Selamat Datang");
    lcd.setCursor(0, 1); 
    lcd.print("JUMLAH = "); lcd.print(a);
    delay(2000);
    delay(3000);
    delay(200); lcd.clear();
    lcd.print("TEMPELKAN KARTU"); 
    lcd.setCursor(0, 1); 
    lcd.print("KTM ANDA");
  }   
 else if (content.substring(1) == "15 68 21 37") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    a=a+1;
    myservo.write(30);
    delay(100);
    lcd.clear();
    lcd.print("Selamat Datang");
    lcd.setCursor(0, 1); 
    lcd.print("JUMLAH = "); lcd.print(a);
    delay(2000);
    delay(3000);
    delay(200); lcd.clear();
    lcd.print("TEMPELKAN KARTU"); 
    lcd.setCursor(0, 1); 
    lcd.print("KTM ANDA");}
    
else if (buttonState == 0) {
   a=a-1;
   myservo.write(30); 
   lcd.clear();
   lcd.print("Selamat Jalan");
   lcd.setCursor(0, 1); 
   lcd.print("JUMLAH = "); lcd.print(a);
    delay(6000); lcd.clear();
    lcd.print("TEMPELKAN KARTU"); 
    lcd.setCursor(0, 1); 
    lcd.print("KTM ANDA");
      }
    
 else   {
    Serial.println(" Access denied");
    myservo.write(170); 
    delay(100);
    lcd.clear();
    lcd.print("AKSES DITOLAK"); 
    lcd.setCursor(0, 1); 
    lcd.print("KARTU INVALID");
    delay(2000);
    delay(200); lcd.clear();
    lcd.print("TEMPELKAN KARTU"); 
    lcd.setCursor(0, 1); 
    lcd.print("KTM ANDA");}
    delay(2000); 
    delay(3000);
} 
