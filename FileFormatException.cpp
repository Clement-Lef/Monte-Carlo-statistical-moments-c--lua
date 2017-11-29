//
// Created by Vincent on 05/12/2016.
//

#include "FileFormatException.h"

FileFormatException::FileFormatException(std::string const &Problem, std::string const &Tag, std::string const &location)
: Exception(Problem, Tag) {
    FileFormatException::location = location;
}

void FileFormatException::setLocation(const std::string &location) {
    FileFormatException::location = location;
}

const std::string &FileFormatException::getLocation() const {
    return location;
}
