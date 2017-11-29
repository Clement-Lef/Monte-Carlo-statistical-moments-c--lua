//
// Created by Vincent on 10/12/2016.
//

#ifndef PCSC_MONTECARLO_EXCEPTIONMANAGER_H
#define PCSC_MONTECARLO_EXCEPTIONMANAGER_H

#include "FileNotFoundException.h"
#include "FileFormatException.h"
#include "FunctionException.h"
#include "FunctionalityNotAvailableException.h"
#include "CriticalException.h"


/// ExceptionManager purpose is to catch the exceptions thrown while running the simulator
/**
 * It will deal with exceptions if possible, otherwise will throw a CriticalException
 * CriticalExceptions are caught in the main and causes the program to end
 */
class ExceptionManager {
private:
    //Private methods to handle the exceptions depending on their type (file loading problems, function evaluation problems, etc...)

    /**
 * Method handling the exceptions thrown when a config file, a data file for discrete function or a source file
 * for a continuous function could not be opened.
 * @param e                 : Exception caught, containing Problem message in its Problem member.
 * @param printer           : ostream used to print warnings, if necessary
 * @param errorPrinter      : ostream used to print errors, if necessary
 */
    void handle(FileNotFoundException& e, std::ostream& printer, std::ostream& errorPrinter) const;

    /**
 * Method handling the exceptions thrown when a data file could not be read properly.
 * @param e                 : Exception caught, containing Problem message in its Problem member.
 * @param printer           : ostream used to print warnings, if necessary
 * @param errorPrinter      : ostream used to print errors, if necessary
 */
    void handle(FileFormatException& e, std::ostream& printer, std::ostream& errorPrinter) const;

    /**
 * Method handling the exceptions thrown when a function could not be evaluated.
 * @param e                 : Exception caught, containing Problem message in its Problem member.
 * @param printer           : ostream used to print warnings, if necessary
 * @param errorPrinter      : ostream used to print errors, if necessary
 */
    void handle(FunctionException& e, std::ostream& printer, std::ostream& errorPrinter) const;

    /**
 * Method handling the exceptions thrown when a non-existing feature was ask by user.
 * @param e                 : Exception caught, containing Problem message in its Problem member.
 * @param printer           : ostream used to print warnings, if necessary
 * @param errorPrinter      : ostream used to print errors, if necessary
 */
    void handle(FunctionalityNotAvailableException& e, std::ostream& printer, std::ostream& errorPrinter) const;



public:
    /**
     *  Through the use of dynamical casting, this function will evaluate the type of the Exception.
     *  It will then call the adapted method to handle the exception
     * @param e_ptr         : pointer to the caught exception
     * @param printer       : ostream to print the warnings
     * @param errorPrinter  : ostream to print the errors messages
     */
    void handle(Exception* e_ptr, std::ostream& printer, std::ostream& errorPrinter) const;

};


#endif //PCSC_MONTECARLO_EXCEPTIONMANAGER_H
