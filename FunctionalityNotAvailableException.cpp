//
// Created by Vincent on 09/12/2016.
//

#include "FunctionalityNotAvailableException.h"

FunctionalityNotAvailableException::FunctionalityNotAvailableException(const std::string &Problem,
                                                                       const std::string &Tag) : Exception(Problem,
                                                                                                           Tag) {}
