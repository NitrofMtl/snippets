#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <backup.h>


String str = "example";
String strArray[3] = {"array1", "array2", "array3"};

char charA = 'a';
char charArray[] = "charExample";

bool boolvar = false;
bool boolArray[] = {0, 1, 0};

int integer = 5;
int intArray[3] = {5, 6, 666};

unsigned int uintvar = 13;
unsigned uintArray[3] = {4, 5, 6};

byte byte8 = 255;
byte byteArray[3] = {56, 57, 58};

float floatv = 32.3;
float floatArray[3] = {3.3, 4.4, 5.5};

double doublev8b = 34;
double doubleArray[3] = {6, 7, 8};

long long32 = 34;
long longArray[3] = {6, 7, 8};

unsigned long ulongvar = 14;
unsigned long ulongArray[3] = {4, 5, 6};


backup data;


void setup() {
  Serial.begin(9600);
  digitalWrite(4, HIGH);
  digitalWrite(10, HIGH);
  SD.begin(4);
  data.begin();
  //data.restore(log); //restore data on boot

}

void loop() {
  evoluateData();
  printdata();
  data.save(log); //save data
  delay(10000);
}

void log() { //log all data to be backed
  data.add(&integer); //add integer 5
  data.add(&str);     //add String example
 // data.add(&charA);   //add single char a // to check if working
  data.add(&boolvar);        //add false
  data.add(&uintvar); //add unsigned int 13
  data.add(&byte8);   //...255
  data.add(&floatv);  //32.3
  data.add(&doublev8b); //34
  data.add(&long32);  //34
  data.add(&ulongvar);  //14
  for(byte i = 0; i< 3; i++){// pass an entire array
    data.add(&intArray[i]); //5,6,666
  }
//    data.add(charArray, 9);// to pass char dont put the '&' symbol not working

  //data.add(intArray, sizeof(intArray)); //backup whole arrays  //not working
}



void printdata(){
//Serial.print("integer ");Serial.println(integer);
//Serial.print("Stringt ");Serial.println(str);
//Serial.print("float ");Serial.println(floatv);
//Serial.print("char ");Serial.println(charA);
//Serial.print("char array ");Serial.println(charArray);
//Serial.print("one int from array ");Serial.println(intArray[3]);
//Serial.print("another int from array but static ");Serial.println(intArray[1]);
//Serial.print("bool " + boolvar);Serial.println();
  }


void evoluateData(){ //make the data changin to see if the follow there las value if rebooted
integer = integer+3;
floatv = floatv+5;
intArray[3] = intArray[3]+3;
  
}



