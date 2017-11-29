//
// Created by Clément Lefebvre on 21.11.16.
//

#include <iostream>
#include <sstream>
#include "ReadDiscrete.h"
#include "Custom_Util.h"

// Exceptions :
#include "FileNotFoundException.h"
#include "FileFormatException.h"
#include "FunctionDiscrete.h"
#include "DataPointReadingException.h"

Function* ReadDiscrete::read(const std::string &filename) const {
    // Opening the file
    std::ifstream reader(filename.c_str());
    if (!reader.is_open()) {
        throw (FileNotFoundException("The file \"" + filename + "\"" + " defining the function"
                                     " could not be open.", "DiscreteDataFileNotFound"));
    }

    // Discarding the headings of the file
    std::string tmp_x;          // String to read x values
    getline(reader,tmp_x);

    std::string tmp_f_x = "";   // String to read f(x) values

    // reading x and f(x)
    std::vector<DataPoint> dataPoints;  // data points
    unsigned int line = 1;
    while(std::getline(reader,tmp_x,',')) { // Read the file
        std::getline(reader,tmp_f_x);
        line++;
        /* Use of stringToDouble method to interpret the string read. Will throw error if the values can not be interpreted
           as double, or in case of overflows  */
        dataPoints.push_back(DataPoint(Custom_Util::stringToDouble(tmp_x,"x at line " + Custom_Util::toString(line), "discrete function file"),
                                       Custom_Util::stringToDouble(tmp_f_x, "f(x) at line " + Custom_Util::toString(line), "discrete function file")));
    }

    if (reader.bad()) { // An error occurred during the reading
        throw FileFormatException("CSV format could not be interpreted in file \"" + filename  + "\""
                                  , "DiscreteDataFileReading", "discrete function file");
    }

    reader.close();

    // Sort the data points before initialising the function
    sortDataPoints(dataPoints);
    try {   // Check the validity of the data points (eg : not twice the same point, not 2 f(x) values for the same x ...)
        checkDataPoints(dataPoints, filename);
    } catch (DataPointReadingException e) {
        // The same data point appears twice : inform user and delete one of the points.
        if (e.getTag()=="Twice same data point") {
            e.printWarning(std::cerr);
            dataPoints.erase(dataPoints.begin() + e.getIndexOfProblematicDataPoint());
            checkDataPoints(dataPoints, filename);
        }
    }

    // Return new Function
    return new FunctionDiscrete(dataPoints);
}

void ReadDiscrete::checkDataPoints(std::vector<DataPoint> const &dataPoints, std::string const& filename) const{
    // The function must be defined by at least to points
    if (dataPoints.size() < 2)
        throw FileFormatException("The file \"" + filename + "\" contains less than 2 data points. "
                                  "At least 2 points are required to define a discrete function"
                                  , "NotEnoughPoints", "discrete function file");
    // Check if points appear more than once (assumes the data points are sorted)
    for (int i=0; i < dataPoints.size()-1; ++i) {
        if (dataPoints[i].getX() == dataPoints[i+1].getX()) {
            if (dataPoints[i].getF_x() == dataPoints[i+1].getF_x()) {
                // same x for same f(x) : one of the point will be discarded when catching the error.
                throw DataPointReadingException("Warning : The same data point appears twice in the discrete function file,"
                                                        " one will be ignored.", i+1);
            }
            // same x but f(x) different : the data file is not valid. Throw Exception to inform user
            throw FileFormatException("The point " + Custom_Util::toString(dataPoints[i].getX()) +
                                      "is defined twice with different values of the function : " +
                                      Custom_Util::toString(dataPoints[i].getF_x()) + " and " + Custom_Util::toString(dataPoints[i+1].getF_x())
                                      , "DiscreteDataFileReading", "discrete function file");
        }
    }
}

void ReadDiscrete::sortDataPoints(std::vector<DataPoint> &dataPoints) const{
    sort(dataPoints.begin(), dataPoints.end(),ReadDiscrete::compareXData);
}

bool ReadDiscrete::compareXData(const DataPoint &Point1, const DataPoint &Point2){
    return Point1.getX() < Point2.getX();
}