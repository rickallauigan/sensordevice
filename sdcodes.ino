#include <SPI.h>
#include <SD.h>

File myFile;
String Mon = "8";
String Day = "22";
String Year="2015";
String GPSTime = "10102010";
int IR = 20;

void setup()
{
  Serial.begin(9600);
  Serial.print("LOADING SD..");

  if (!SD.begin(10)) {
    Serial.println("SD FAILED!");
    return;
  }
  Serial.println("Done LOADING.");

}

void loop(){
    int fc = 0;
    //to create a text File named Mon+Day+Year
    String txtFile = String(Mon+Day+Year)+".txt"; 
    
    //to check if the file is existing
    if (SD.exists(txtFile)) {
      Serial.println("Exists.");
    }
    else {
      Serial.println("Doesn't exist.");  
      cache(fc);
      fc++;
    }
    
}
void cache(int fcount){
  //create a file that can uses the MonDayYear and add a Counts to make it unique
  myFile = SD.open((Mon+Day+Year+fcount+".txt"), FILE_WRITE);
  if (myFile) {
    Serial.println(Year+Mon+Day+".txt");
    while (myFile.available()) {
            
      String v;
      int x;
      int y = -1;
      x =  myFile.read();
      if (x == 32){
           v = " ";
      }else{
         if ( x >= 48 && x <= 57 ){
           y = x - 48;
           v = String(y);
         }
      }
      Serial.print(v);
      //Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("ERROR Opening");
  }
  
}


