//
// Created by Vincent on 05/12/2016.
//

#include "Exception.h"

Exception::Exception(std::string const &Problem, std::string const &Tag) {
    Exception::Tag = Tag;
    Exception::Problem = Problem;
}

Exception::~Exception() {}

const std::string &Exception::getTag() const {
    return Tag;
}

const std::string &Exception::getProblem() const {
    return Problem;
}

void Exception::printWarning(std::ostream &out) const{
    out.flush();
    out << Problem + "\n";
    out.flush();
}

void Exception::setTag(const std::string &Tag) {
    Exception::Tag = Tag;
}

void Exception::setProblem(const std::string &Problem) {
    Exception::Problem = Problem;
}
