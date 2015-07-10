#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);                                                      //your pins to serial communication
int valor;
String token = "gsm";      //your token to post value
#define trigPin A1
#define echoPin A0

void setup()
{
  mySerial.begin(19200);                                                            //the GPRS baud rate
  Serial.begin(19200);    
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  delay(1000);
}
void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 25.54;
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
  
    //int value = analogRead(A0);                                                     //read pin A0 from your arduino
    save_value(String(distance));                                                      //call the save_value function
    if (mySerial.available())
    Serial.write(mySerial.read());
}
//this function is to send the sensor data to Ubidots, you should see the new value in Ubidots after executing this function
void save_value(String value)
{
  int num;
  String le;
  String var;
  var="{\"value\"unsure emoticon""+ value + "\"}";
  num=var.length();
  le=String(num);
  for(int i = 0;i<1;i++)
  {
    mySerial.println("AT+CGATT?");                                                   //this is made repeatedly because it is unstable
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"web.vmc.net.co\"");                                    //replace with your providers' APN
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"bukidutility.appspot.com\",\"80\"");             //start up the connection
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1/farm/001");
  delay(100);
  ShowSerialData();
  mySerial.println(" HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Farm-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: bukidutility.appspot.com");
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication
  delay(1000);
  ShowSerialData();
}
void ShowSerialData()
{
  while(mySerial.available()!=0)
  Serial.write(mySerial.read());
}
