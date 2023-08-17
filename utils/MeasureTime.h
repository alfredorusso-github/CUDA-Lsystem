#ifndef MEASURETIME_H
#define MEASURETIME_H

#include <chrono>

// Wrapper in order to measure function execution time
template<typename T, typename F, typename... Args>
double MeasureTime(T *obj, F funzione, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    (obj->*funzione)(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

#endif
