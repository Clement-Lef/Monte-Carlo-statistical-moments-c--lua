//
// Created by Vincent on 05/12/2016.
//

#ifndef PCSC_MONTECARLO_EXCEPTION_H
#define PCSC_MONTECARLO_EXCEPTION_H

#include <iostream>

///This is the Mother class of all Exceptions in the project.
/**
 *  It contains two string members : Tag and Problem
 *  Tag is used by the program to recognize the Exceptions to chose how to deal with them
 *  Problem is used to describe the cause of the error to the user if necessary
 */
class Exception {
private:
    /// String identifier to the program
    std::string Tag;
    /// String describing the problem, used to inform user
    std::string Problem;

public:
    /// Constructor : the two field must ne initialised for correct utilisation
    Exception(std::string const &Problem, std::string const &Tag);
    virtual ~Exception();

    /// Prints the content of member Problem on the input ostream (used to inform user of non-critical error);
    void printWarning(std::ostream &out) const;

    /// Getters
    const std::string &getTag() const;
    const std::string &getProblem() const;

    /// Setters
    void setTag(const std::string &Tag);
    void setProblem(const std::string &Problem);
};


#endif //PCSC_MONTECARLO_EXCEPTION_H
