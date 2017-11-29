//
// Created by Vincent on 05/12/2016.
//

#ifndef PCSC_MONTECARLO_DATAPOINT_H
#define PCSC_MONTECARLO_DATAPOINT_H


///Class used to store a point and its image for a discrete function

class DataPoint {
private:
    double x;
    double f_x;
public:
    /**
     * Constructor
     * @param x : Coordinate
     * @param f_x : Image of the function at x
     */
    DataPoint(double x, double f_x);
    ///Getter for the coordinate
    double getX() const;
    ///Getter for the image
    double getF_x() const;

};


#endif //PCSC_MONTECARLO_DATAPOINT_H
