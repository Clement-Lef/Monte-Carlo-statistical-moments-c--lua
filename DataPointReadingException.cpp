//
// Created by Vincent on 05/12/2016.
//

#include "DataPointReadingException.h"

DataPointReadingException::DataPointReadingException(std::string const &Problem, size_t indexOfProblematicDataPoint, std::string const &Tag)
: Exception(Problem, Tag)
{
    DataPointReadingException::indexOfProblematicDataPoint = indexOfProblematicDataPoint;
}

size_t DataPointReadingException::getIndexOfProblematicDataPoint() const {
    return indexOfProblematicDataPoint;
}
