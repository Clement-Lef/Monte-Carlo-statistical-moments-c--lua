//
// Created by Clément Lefebvre on 21.11.16.
//

#ifndef PCSC_MONTECARLO_FUNCTION_H
#define PCSC_MONTECARLO_FUNCTION_H


#include <string>
#include <vector>
/// Abstract class used to represent a function
class Function {
public:
    /**
     * Return the value of the function in coord
     * argument interpolationMethod specifies the interpolation to use for evaluating a discrete Function un coord
     * (defined by couples of points (x,f(x)).
     * Default argument "" is to be used when evaluating a continuously defined function
     */
    virtual double eval(std::vector<double> const& x, std::string const& interpolationMethod = "") const = 0;

    virtual ~Function() {};


};



#endif //PCSC_MONTECARLO_FUNCTION_H
