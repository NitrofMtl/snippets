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

#include <Ethernet.h> ////now version 2.0 compatible with ethernet shield 1 and 2
#include <EthernetServer.h>
#include <EthernetUdp.h> //now version 2.0 compatible with ethernet shield 1 and 2
#include <TimeLib.h>

#define LOCK 1

//template to pass array number of element to function
template <typename T, size_t N>
inline
size_t SizeOfArray( const T(&)[ N ] )
{
  return N;
}

//time_t getNtpTime();
time_t getNtpTime(IPAddress &address);
void sendNTPpacket(IPAddress &address);
void printDigits(int digits, HardwareSerial& stream);
void digitalClockDisplay();
void digitalClockDisplay(time_t t, HardwareSerial& stream);
void printTime();
void setTimeZone(int zone);

String onOffBool(bool inBool);

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