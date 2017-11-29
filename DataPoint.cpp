//
// Created by Vincent on 05/12/2016.
//

#include "DataPoint.h"

DataPoint::DataPoint(double x, double f_x) {
    DataPoint::x = x;
    DataPoint::f_x = f_x;
}

double DataPoint::getX() const {
    return x;
}

double DataPoint::getF_x() const {
    return f_x;
}