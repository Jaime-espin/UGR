#ifndef MY_TIME_H
#define MY_TIME_H

#include <chrono>
#include <cassert>
using namespace std::chrono;

class MyTime{
private: 
    high_resolution_clock::time_point tantes, tdespues;

public: 
    MyTime() = default; 

    inline void start() {
        tantes = high_resolution_clock::now();
    }

    inline void end(){
        tdespues = high_resolution_clock::now();
    }

    [[nodiscard]] inline const double getTime() const{
        assert(tdespues > tantes);
        duration<double>  transcurrido = duration_cast<duration<double>>(tdespues - tantes); 
        return transcurrido.count();
    }

    [[nodiscard]] inline const double operator*() const {
        return getTime();
    }

};

#endif