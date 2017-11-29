//
// Created by Vincent on 05/12/2016.
//

#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(std::string const &Problem, std::string const &Tag)
: Exception(Problem, Tag) {

}
