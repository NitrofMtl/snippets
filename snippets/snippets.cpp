/*
  Copyright (c) 20/05/2015

    By Nitrof

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "snippets.h"

#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <TimeLib.h>

IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
EthernetUDP *Udp2;

void timeIp(IPAddress t_IP){
  IPAddress timeServer(t_IP);
}

void setClock(EthernetUDP *Udp){
  Udp2 = Udp;
  setSyncProvider(getNtpTime);
}

int timeZone = -5;     // Eastern time

void setTimeZone(int zone){
  timeZone = zone;
}

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets


time_t getNtpTime()
{
  while (Udp2->parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  Serial.println("waiting");
  while (millis() - beginWait < 1500) {
    int size = Udp2->parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp2->read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

        // send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
Serial.println("sending packet");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp2->beginPacket(address, 123); //NTP requests are to port 123
  Udp2->write(packetBuffer, NTP_PACKET_SIZE);
  Udp2->endPacket();
}

time_t prevDisplay = 0; // when the digital clock was displayed

void printTime(){
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();  
    }
  }
 }


void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

uint8_t roundDown(int numToRound, int multiple){  // add to template
    if (multiple == 0) 
      return numToRound;
    int remainder = numToRound % multiple;
    if (remainder == 0) 
      return numToRound;
    return numToRound - remainder;
}




String onOffBool(bool inBool) {
  String OnOff;
  if (inBool)OnOff = "ON";
  else if (!inBool)OnOff = "OFF";
  return OnOff;
}

String intToOnOff(byte inInt) {
  String output;
  if (inInt == 0) {
    output = "Off";
  }
  else {
    output = "On";
  }
  return output;
}

String toString(const char* inchar) {
  String outString;
  for (byte i = 0; i < strlen(inchar); i++) {
    outString += inchar[i];
  }
  return outString;
}

bool stringToBool(const char* inChar) {
  if (inChar == "true") {
    return true;
  } else if (inChar == "false") {
    return false;
  }
}

byte onOffToInt( const char* input) {
  return (strcmp(input, "on") == 0) ? 1 : 0;
}



int Snippets::funcDelay(int delay) {  //delay with loop lag remove
  int delayOutput =  (delay - (millis() - lastMillis));
  delayOutput = constrain(delayOutput, 1, delay); //delay min 1 to remove possible bug on 0 delay.. ?
  lastMillis = millis();
  return delayOutput;
}

void Backup::begin(){
//if check sd folder backup not exist, create it.
  //then check if backup.txt not exist, create it.
  // on succes serial print "backup ready" on fail "Fail to create backup"

if (!SD.exists("backup")) SD.mkdir("backup");
if (SD.exists("backup")) Serial.println("backup folder present");
if (!SD.exists("backup/BACKUP.txt")) {
    File bck = SD.open("backup/BACKUP.txt", FILE_WRITE); 
    bck.close();
  }
if (SD.exists("backup/BACKUP.txt")) Serial.println("backup ready");
  else Serial.println("Fail to create backup"); 
delay(10); //for stability
}

char* Backup::get(){
    char* pBuffer;                              // Declare a pointer to your buffer.
    File bckFile = SD.open("backup/BACKUP.txt");        // Open file for reading.
    if (bckFile)
    {
        unsigned int fileSize = bckFile.size();  // Get the file size.
        pBuffer = (char*)malloc(fileSize + 1);  // Allocate memory for the file and a terminating null char.
        bckFile.read(pBuffer, fileSize);         // Read the file into the buffer.
        pBuffer[fileSize] = '\0';               // Add the terminating null char.
     //   Serial.println(pBuffer);                // Print the file to the serial monitor.
        bckFile.close();                         // Close the file.
    }
    return pBuffer;
    free(pBuffer);                              // Free the memory that was used by the buffer.
}




void SetSchedule::interval(void (*function)(), int delay){
  if (lastMillis < millis()){
    (function)();
    lastMillis = lastMillis + delay;
  }
}

void SetSchedule::timeOut(int delay){
  if(!chkLOCK){
    trigger = millis()+delay;
    unsigned long testvar = 0-1; // cach a var with maximum type long value
    if( (testvar-millis()) < delay) { //check if delay overflow millis timer
      lastMillis = millis(); // store check pointe
      timerOverflow = true; // set a lock for handler to wait millis overflow before activate 
    }
  }
}

void SetSchedule::timeOut(int delay, bool lock){
  if(!chkLOCK){
    trigger = millis()+delay;
    unsigned long testvar = 0-1; // cach a var with maximum type long value
    if( (testvar-millis()) < delay) { //check if delay overflow millis timer
      lastMillis = millis(); // store check pointe
      timerOverflow = true; // set a lock for handler to wait millis overflow before activate 
    }
    chkLOCK = 1;
  }
}

void SetSchedule::timeOut(void (*function)()){

  if(timerOverflow && lastMillis < millis()) return; //break function if delay have rool back millis until millis have rool back
  if (trigger < millis()) {
    (function)(); // do callback
    trigger = 0-1; //reset timer
    chkLOCK = 0; //reset lock
    lastMillis = 0; //reset last reading
    timerOverflow = false; //reset overflow detection
  }
}

void SetSchedule::reset(){
    trigger = 0-1;
    chkLOCK = 0; 
    lastMillis = 0; //reset last reading
    timerOverflow = false; //reset overflow detection 
}
