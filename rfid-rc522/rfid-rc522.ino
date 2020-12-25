#include <SPI.h>
#include <RFID.h>
#include <DS18B20.h>
#include <OneWire.h>
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
String rfidCard;

//the temperature input pin
DS18B20 ds(2);

//initializing variables
int ledPin = 7;
int data1 = 2;
int data2 = 3;

void temperature(String names)
{
  //if the card is recognized take temperature and save to the database
  while (ds.selectNext()) 
  {
    //get temperature thats more 30
    if(ds.getTempC() > 30.0)
    {
      //taking the temperature and making the led glow
      Serial.println("Taking temperature C` ...");
      digitalWrite(ledPin,HIGH);
      delay(1000);
      digitalWrite(ledPin,LOW);
      delay(1000);

      //when the led is off the temperature is recorded and sent to the database
      Serial.println(ds.getTempC());
      digitalWrite(8, HIGH);
      delay(2000);
      digitalWrite(8, LOW);
      Serial.println(names+"'s Temperature is taken and recorded");
      //Serial.println(rfidCard);
    }
    else
    {
      Serial.println("The temperature is lower then normal...");
      Serial.println(ds.getTempC());
      tone(8,100);
      digitalWrite(ledPin,HIGH);
      delay(3000);
      noTone(8);
      digitalWrite(ledPin,LOW);
      
    }
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();

  //this pin works with the temperature sensor
  pinMode(ledPin,OUTPUT);
  pinMode(data1,INPUT);
  pinMode(data2,INPUT);

  //pin for the buzzer for both the rfid and the sensor
  pinMode(8, OUTPUT);
}
void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) 
    {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      if (rfidCard == "124 243 161 22") 
      {
        //calling the temperature function with the user name
        temperature("Andreas");
      }
      else if (rfidCard == "92 25 82 34") 
      {
        temperature("Joseph");
      }
      else if (rfidCard == "167 163 239 216") 
      {
        temperature("Sidney");
      }
      else 
      {
        Serial.println("Unknown user... Unauthorised");
        Serial.println(rfidCard);
        digitalWrite(8, HIGH);
        digitalWrite(7, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        delay(100);
        digitalWrite(8, HIGH);
        digitalWrite(7, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        delay(100);
        digitalWrite(8, HIGH);
        digitalWrite(7, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        delay(100);
      }
    }
    rfid.halt();
  }
}
