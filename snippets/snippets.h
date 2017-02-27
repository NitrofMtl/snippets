/*
  Copyright (c) 28/03/2016

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
  
#ifndef snippets_H
#define snippets_H

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif
#include <SD.h>

#include <Ethernet.h>
//#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <TimeLib.h>

#define LOCK 1

//template to pass array number of element to function
template <typename T, size_t N>
inline
size_t SizeOfArray( const T(&)[ N ] )
{
  return N;
}

//void getNTPTime();
void setClock(EthernetUDP *Udp);

time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
void printDigits(int digits);
void digitalClockDisplay();
void printTime();
void timeIp(IPAddress t_IP);
void setTimeZone(int zone);

uint8_t roundDown(int numToRound, int multiple);

String intToOnOff(byte inInt);
String onOffBool(bool inBool);
String toString(const char* inchar);
bool stringToBool(const char* inChar);
byte onOffToInt( const char* input);

class Snippets {
public:
	int funcDelay(int delay);
private:
	int lastMillis = 0; //marker for lag correction delay
};


class Backup {
public:
	Backup(){};
	void begin();
	char* get();
private:

};

class SetSchedule {
public:
	void interval(void (*function)(), int delay);
	void timeOut(int delay);
	void timeOut(int delay, bool lock);
	void timeOut(void (*function)());
	void reset();
private:
	unsigned long lastMillis = 0;
	bool chkLOCK = 0;
	unsigned long trigger = 0-1;
  bool timerOverflow = false;
};

class WebFileBuffer {
  public:
    WebFileBuffer(char* webFileName);
    char* name;
    File getWebFile();
  private:
    File *webFileBuffed = new File;
    char* get(File bckFile);
};

#endif
