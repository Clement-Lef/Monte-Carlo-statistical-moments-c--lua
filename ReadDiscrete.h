//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_READDISCRETE_H
#define PCSC_MONTECARLO_READDISCRETE_H


#include "ReadFunction.h"
#include "DataPoint.h"
#include <vector>


/// This class is used to read a file containing data points (x,f(x)) and initialise a DiscreteFunction according to the data points.

class ReadDiscrete : public ReadFunction {
private:
    /// Helper function to sort along columns in 2d vectors (for sorting the data points according to x value)
    static bool compareXData(const DataPoint &Point1, const DataPoint &Point2);
    /// Sort the data Points in ascending order of the value of x
    void sortDataPoints(std::vector<DataPoint> &dataPoints) const;
    /** Check the validity of the data points. Assumes the data points are sorted.
     *  The points are not valid if there are multiple values of f(x) for the same x
     */
    void checkDataPoints(std::vector<DataPoint> const &dataPoints, std::string const& filename) const;
public :
    /**
     * Function used to read a CSV file which contains data points of a discrete function
     *      The first line of the file is used for headings : it will NOT be read
     *      Reads csv file containing the values of the function to read. Format : x,f(x)
     * @param filename : Name of the function file
     * @return A pointer on a new DiscreteFunction
     */
    Function* read(const std::string &filename) const;
};


#endif //PCSC_MONTECARLO_READDISCRETE_H
