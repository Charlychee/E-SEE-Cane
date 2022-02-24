// Author: Charles Lee - ccl002@ucsd.edu

#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    Timer(int interval, void (*function)());
    ~Timer();

    void run();
  
  private:
    unsigned long previous;
    int theInterval;
    void (*theFunction)();
};

#endif