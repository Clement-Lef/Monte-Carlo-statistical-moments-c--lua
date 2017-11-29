//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_FUNCTIONDISCRETE_H
#define PCSC_MONTECARLO_FUNCTIONDISCRETE_H

#include "Function.h"
#include "DataPoint.h"
#include <algorithm>

/// This class correspond to the definition of a function through a set of points (x, f(x))
/**
 * The constructor assumes the data points are sorted in ascending order
 * It can only be used to define function taking double as argument, and returning double. (no 2D, 3D)
 */
class FunctionDiscrete : public Function {
public :
    /**
     *  The constuctor initialises the data points (x,f(x)). The data points must be sorted in ascending order ! (smaller at index 0)
     * @param dataPoints : data points sorted in ascendant order !
     */
    FunctionDiscrete(std::vector<DataPoint> &dataPoints);

    /**
     * Returns the value of the Function at coord, using the interpolation Method ask in argument
     * x is vector containing the point to evaluate the function
     * Interpolation are not defined in dimension higher than 1, so x must be a 1 dimension vector
     */
    double eval(std::vector<double> const& x, std::string const& interpolationMethod) const;

private:
    /// data Points (x,f(x))
    std::vector<DataPoint> dataPoints;


    /// Returns value of the function in coord, computed with a linear interpolation between the nearest data points
    double linearInterpolation(double coord) const;
    /// Returns the value of the function at the closest data point
    double approximateToClosest(double coord) const;
    /// Returns the value of the function at the closest inferior data point
    double approximateToInferior(double coord) const;
    /// Returns the value of the function at the closest superior data point
    double approximateToSuperior(double coord) const;

    /**
     * Returns the index of the nearest inferior value to argument coord
     * Throws an exception if the argument coord doesn't lie between to values of data points (that is if coord is not
     * in the interval where the function can be interpolated)
     * Assumes the data points are sorted for binary search
     */
    size_t getIndexOfNearestInferiorDataPoint(double coord) const;

    /// Compares coordinate and dataPoint : return true if coordinate is smaller than data x value
    static bool compareCoordinateAndDataPoint(double coord, DataPoint const& dataPoint);
};


#endif //PCSC_MONTECARLO_FUNCTIONDISCRETE_H
