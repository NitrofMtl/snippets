#include <snippets.h>

SetSchedule timer1; // call instance of timer. 
SetSchedule timer2;
SetSchedule interval;
                    //each instance of timeout share variables. so 'LOCK' timeOut will have priority over unlocked. 
                    //function containing callback have to be in loop() to be trigged

char receivedChar;

void setup() {
  Serial.begin(9600);
}

void loop() {
  timer1.timeOut(example1); // monitor timeOut and call the Function
  timer2.timeOut(example2);
  if (Serial.available()) {
    receivedChar = Serial.read();
    if (receivedChar == '1') {
      timer1.timeOut(5000); //where set timeOut, if recall, overwrite delay and call only the last one
    }
    if (receivedChar == '2') {
      timer2.timeOut(10000, LOCK); //where set timeOut, if recall, keep the first delay until it's pass
    }
  }
  interval.interval(example3,2000); //call function and interval delay
  delay(1000);
}

void example1() {
  Serial.println("timer1 have been trigged");
}

void example2() {
  Serial.println("timer2 have been trigged");
}

void example3() {
    Serial.println("interval have been trigged");
}

