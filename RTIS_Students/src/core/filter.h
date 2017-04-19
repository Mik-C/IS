
#ifndef RTIS_STUDENTS_FILTER_H
#define RTIS_STUDENTS_FILTER_H

#include "vector3d.h"
#include "film.h"
#include <cmath>

class Filter {
public:
    Filter();
    ~Filter();

    void printFilter();
    void convolution(Film* read, Film* write);

    void setMean(size_t w=3, size_t h=3);
    void setGauss(size_t w=3, size_t h=3, double sigma = 1.0);

protected:
    size_t width;
    size_t height;
    double* filter;

};

#endif //RTIS_STUDENTS_FILTER_H
