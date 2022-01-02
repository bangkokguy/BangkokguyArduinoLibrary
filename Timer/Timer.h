/*
  Timer.h - Library for delay functionality
  Created by L. Gergely, May, 2021.
  Released into the public domain.
*/
#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer {
  private:    
    #define AUTORESET true
    #define NOAUTORESET false
    #define MICROSECONDS 0
    #define SECONDS 1
    #define MINUTES 2
    #define HOURS 3
    unsigned long startTime;
    unsigned long waitTime;
  public:  
    Timer(int timeValue, int timeUnit, bool autoreset);
    Timer(int timeValue, int timeUnit);
    Timer(int timeValue);
    Timer(int timeValue, bool autoreset);
    void debug();
    void reset (int ms = 0);
    bool timeout ();
    void flush ();
    unsigned long remaining ();
    int remainingHours ();
    int remainingMinutes ();
    int remainingSeconds ();
    unsigned long get ();
    bool autoReset;
};
#endif
