#include <SoftwareSerial.h>
 
SoftwareSerial GPRS(7, 8);
unsigned char buffer[64]; // buffer array for data recieve over serial port
unsigned char bigBuffer[200];
long count=0;     // counter for buffer array 
int led=2;
int onOff=0;

void setup()
{
  pinMode(led, OUTPUT);
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  delay(5000);
  GPRS.write('\r\nATE0\r\n');          //Echo command off, makes reading the returned data easier
  GPRS.write('\r\nAT+CMGF=1\r\n');     //Changes SMS output to text instead of PDU 
  clearBuffer();
}
 
void loop(){
  if (GPRS.available()){
    delay(3000);
    clearBuffer();
    blinky();
  }
}

int checkIncoming(){
  if(GPRS.available()){
    int toRead=GPRS.available();
    for(int i=0; i<toRead ;i++){
      bigBuffer[i]=GPRS.read();
    }
  }
}

void blinky(){
  for(int x=0;x<10;x++){
    onOff=!onOff;
    digitalWrite(led, onOff);
    delay(500);
  }
  digitalWrite(led,0);
}

void clearBuffer(){
  count=GPRS.available();
  for(int i=0;i<count;i++){
    Serial.write(GPRS.read());
  }
}
