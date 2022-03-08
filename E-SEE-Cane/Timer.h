// Author: Charles Lee - ccl002@ucsd.edu
// Timer provides a synchronous way to run a provided function

#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    Timer(int interval, void (*function)());
    ~Timer();

    void run();
    void runNow();
  
  private:
    unsigned long previous;
    int theInterval;
    void (*theFunction)();
};

#endif
