#ifndef Timer_h
#define Timer_h

#include <Arduino.h>


class TimerGO {

  public:
    TimerGO(){};

    void start(uint32_t Timeout){
      _Tset = Timeout;
      _Told = millis();
    };

    bool Go(){
      if ((millis() - _Told) >= _Tset){
        resetGo();
        Serial.println("Timer go");
        return true;
      }
      return false;
    }

    bool setTime(uint32_t Timeout){
      _Tset = Timeout;
    }

    uint32_t getTimeRemains(){
      return (millis() - _Told);
    }

    uint32_t return_Tset(){
      return _Tset;
    }



    bool TimeReset(){
      _Told = millis();
    }


    void resetGo(){
      _Told = millis();
    }

    uint32_t _Told;
    uint32_t _Tset;

  private:



// TimerGO::TimerGO(){};


};

#endif
