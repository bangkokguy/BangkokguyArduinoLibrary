/*
  Timer.cpp - Library for delay functionality
  Created by L. Gergely, May, 2021.
  Released into the public domain.
*/
//#include <ESP8266WiFi.h>
#include <Timer.h>
#include <string.h>

//#define DEBUG if (1==2)

unsigned long __time;

Timer::Timer(int ms, int _time, bool autoreset) {
    startTime = millis();
    __time = _time;
    switch (_time) {
      case MICROSECONDS:
        waitTime = (unsigned long)ms;
        break;
      case SECONDS:
        waitTime = (unsigned long)(ms * 1000);
        break;
      case MINUTES:
        waitTime = (unsigned long)(ms * 1000 * 60);
        break;
      case HOURS:
        waitTime = (unsigned long)(ms * 1000 * 60 * 60);
        break;
      default:
        waitTime = (unsigned long)ms;
        break;
    }
    autoReset = autoreset;
}
Timer::Timer(int ms, int _time) {
    Timer(ms, _time, true);
}
Timer::Timer(int ms) {
    Timer(ms, MICROSECONDS, true);
}
Timer::Timer(int ms, bool autoreset) {
    Timer(ms, MICROSECONDS, autoreset);
}
void Timer::debug() {
    Serial.print("Timer serialized ");
    Serial.print(__time);
    Serial.print(" - ");
    Serial.print(waitTime);
    Serial.print(" - ");
    Serial.println(startTime);
}
void Timer::reset (int ms) {
    #ifdef DEBUG
    Serial.print("Timer reset "); 
    Serial.print(ms);
    Serial.print(" - ");
    Serial.println(startTime); 
    #endif
    startTime = millis();
    if (ms != 0) waitTime = (unsigned long)ms;
}
void Timer::flush () {
    #ifdef DEBUG
    Serial.print("Timer flush ");
    #endif
    startTime = 0;
}
unsigned long Timer::remaining () {
    #ifdef DEBUG
    Serial.print(" *** remaining: ");
    Serial.print(waitTime);
    Serial.print(" + ");
    Serial.print(startTime);
    Serial.print(" - ");
    Serial.print(millis());
    Serial.print("=");
    Serial.println(waitTime + startTime - millis());
    #endif
    if (millis() - startTime < waitTime)
        return waitTime + startTime - millis();
    else
        return 0;
}
int Timer::remainingHours () {
    return int(remaining () % 3600000);
}
int Timer::remainingMinutes () {
    return int(remaining () % 60000);
}
int Timer::remainingSeconds () {
    return int(remaining () / 1000);
}
unsigned long Timer::get () {return waitTime;}
bool Timer::timeout () {
  #ifdef DEBUG  
  Serial.print("timeout - ");
  Serial.print(startTime);
  Serial.print(" - ");
  Serial.println(millis());
  #endif
  if (millis() - startTime > waitTime) {
      #ifdef DEBUG
      Serial.print("Timeout reached "); 
      Serial.print(waitTime);
      Serial.println(autoReset);
      #endif
      if (autoReset) reset(waitTime);
      return true;
  } else { 
      return false;
  }
}