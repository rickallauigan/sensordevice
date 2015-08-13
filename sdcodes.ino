#include <SoftwareSerial.h>
#include <SD.h>
SoftwareSerial gprsSerial(2, 3);

File sdLog;
void d(int dly){delay(dly);ShowSerialData();}
void setup()
{
  gprsSerial.begin(19200);
  Serial.begin(19200);
  Serial.print("Loading SDCARD_");
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("SD FAILED");
    return;
  }
  Serial.println("SD OK");
  
  d(1000);
}

void loop()
{
    int IR = pow(3027.4/analogRead(A0), 1.2134);
    Cache(String(IR));
    Send(String(IR));
    if (gprsSerial.available())
    Serial.write(gprsSerial.read());
    
}

void Cache(String data){
  sdLog = SD.open("DATA.txt", FILE_WRITE);
  if (sdLog) {
    Serial.print("Writing to DATA.txt...");
    sdLog.println("TEST STRING");
    sdLog.close();
    Serial.println("done.");
  } else {
    Serial.println("DATA.txt ERR!");
  }
}
void Send(String value)
{
  int num;
  String le;
  String var;
  var="{\"value\":\""+ value + "\"}";
  num=var.length();
  le=String(num);
  for(int i = 0;i<1;i++){
    gprsSerial.println("AT+CGATT?");
    delay(2000);
    ShowSerialData();
  }
  ("AT+CSTT=\"web.vmc.net.co\"");d(1000);
  gprsSerial.println("AT+CIPSTART=\"tcp\",\"Xinner-suprstate-820.appspot.com\",\"80\"");d(3000);
  gprsSerial.println("AT+CIPSEND");d(3000);
  gprsSerial.print("POST /api/v1/farm/1001/variable/0001");d(100);
  gprsSerial.println(" HTTP/1.1");d(100);
  gprsSerial.println("Content-Type: application/json");d(100);
  gprsSerial.println("Content-Length: "+le);d(100);
  gprsSerial.print("X-Farm-Token: ");d(100);
  gprsSerial.println("\"token\"");d(100);
  gprsSerial.println("Host: Xinner-suprstate-820.appspot.com");d(100);
  gprsSerial.println();d(100);
  gprsSerial.println(var);d(100);
  gprsSerial.println();d(100);
  gprsSerial.println((char)26);delay(5000);
  gprsSerial.println();ShowSerialData();
  gprsSerial.println("AT+CIPCLOSE");d(1000);
}
void ShowSerialData(){
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
}


