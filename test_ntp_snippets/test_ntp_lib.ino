/*
 * Time_NTP.pde
 * Example showing time sync to NTP time source
 *
 * This sketch uses the Ethernet library
 */
 
#include <TimeLib.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <snippets.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
IPAddress ip(192, 168, 0, 110);


// NTP Servers:
//IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov


//const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)


EthernetUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

void setup() 
{
  Serial.begin(9600);
Serial.println("begin");
  delay(250);
digitalWrite(4,HIGH);
  Ethernet.begin(mac, ip);
  Serial.print("Ip address; "); Serial.println(Ethernet.localIP());
  Udp.begin(localPort);
  Serial.println("waiting for sync");
      //list of timezone:
      //https://en.wikipedia.org/wiki/List_of_UTC_time_offsets
//  setTimeZone(-5); //for eastern time us canada, set by default in library to -5
//  timeIp(IPAddress(132, 163, 4, 101)); //default in library
    setClock(&Udp);
}

void loop()
{
  printTime();  
  delay(1000);
}
