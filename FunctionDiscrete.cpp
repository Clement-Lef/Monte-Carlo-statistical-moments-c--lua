//
// Created by Clément Lefebvre on 21.11.16.
//

#include <sstream>
#include "FunctionDiscrete.h"
#include "FunctionException.h"
#include "FunctionalityNotAvailableException.h"
#include "Custom_Util.h"

FunctionDiscrete::FunctionDiscrete(std::vector<DataPoint> &dataPoints) {
    FunctionDiscrete::dataPoints = dataPoints;
}



double FunctionDiscrete::eval(std::vector<double> const& x, std::string const& interpolationMethod) const {
    double coord = x[0]; //Transform the 1 dimension vector to a double for a simpler usage in the following functions


    if (interpolationMethod == "Linear") {
        return FunctionDiscrete::linearInterpolation(coord);
    } else if (interpolationMethod == "Closest") {
        return approximateToClosest(coord);
    } else if (interpolationMethod == "Lower") {
        return approximateToInferior(coord);
    } else if (interpolationMethod == "Upper") {
        return approximateToSuperior(coord);
    } else if (interpolationMethod == "") {
        throw FunctionException("The interpolation method has not been specified", "MissingEvaluationMethod");
    }
    throw FunctionalityNotAvailableException("Interpolation method \"" + interpolationMethod  + "\" is not available.",
                                             "Undefined interpolation method");
}

double FunctionDiscrete::linearInterpolation(double coord) const {
    // Get index of nearest inferior point to coord
    size_t index = FunctionDiscrete::getIndexOfNearestInferiorDataPoint(coord);
    // Compute the slope between the nearest inferior and nearest superior points
    double slope = (dataPoints[index+1].getF_x() - dataPoints[index].getF_x())/(dataPoints[index+1].getX() - dataPoints[index].getX());
    // Return the linear interpolation evaluated in coord
    return dataPoints[index].getF_x() + slope * (coord-dataPoints[index].getX());
}

double FunctionDiscrete::approximateToClosest(double coord) const {
    // Get index of nearest inferior point to coord
    size_t index = FunctionDiscrete::getIndexOfNearestInferiorDataPoint(coord);
    if (coord - dataPoints[index].getX()  < dataPoints[index+1].getX() - coord) {
        // the inferior point is the closest to coord : return it
        return dataPoints[index].getF_x();
    } else {
        // The superior point is the closest to coord, return it
        return dataPoints[index + 1].getF_x();
    }
}

double FunctionDiscrete::approximateToInferior(double coord) const {
    // Get index of nearest inferior points to coord
    size_t index = FunctionDiscrete::getIndexOfNearestInferiorDataPoint(coord);
    // return this point
    return dataPoints[index].getF_x();
}

double FunctionDiscrete::approximateToSuperior(double coord) const {
    // get index of nearest inferior point to coord
    size_t index = FunctionDiscrete::getIndexOfNearestInferiorDataPoint(coord);
    // next point is the closest superior to coord, return it
    return dataPoints[index+1].getF_x();
}

size_t FunctionDiscrete::getIndexOfNearestInferiorDataPoint(double coord) const {
    if (dataPoints[0].getX() > coord || dataPoints.back().getX() < coord) {
        // coord is not in the interval where the function is defined. Interpolation method can not work
        throw FunctionException("Function can not be evaluated : " + Custom_Util::toString(coord) +
                                " is not in the interval of definition of the function : [" +
                                Custom_Util::toString(dataPoints[0].getX()) + ", " + Custom_Util::toString(dataPoints.back().getX()) + "]");
    }
    // Coord is in the interval of definition, we can use the binary search function upper_bound to find the closest points
    std::vector<DataPoint>::const_iterator low;
    low = std::upper_bound(dataPoints.begin(), dataPoints.end()-1, coord, FunctionDiscrete::compareCoordinateAndDataPoint);
    //  Decrease of one to get the largest inferior value
    low--;
    return  low - dataPoints.begin();
}


 bool FunctionDiscrete::compareCoordinateAndDataPoint(double coord, const DataPoint &dataPoint) {
     return  coord < dataPoint.getX();
}