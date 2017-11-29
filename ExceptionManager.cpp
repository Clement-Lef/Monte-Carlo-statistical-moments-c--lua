//
// Created by Vincent on 10/12/2016.
//

#include "ExceptionManager.h"

// handles the Exceptions raised when a file can not be open
void ExceptionManager::handle(FileNotFoundException& e, std::ostream &printer, std::ostream &errorPrinter) const {
    if (e.getTag() == "ConfigFile") {
        // The configuration file could not be open - print this to user
        e.printWarning(printer);
        // then return to go back to loop in the main, which ask for the config file.
    } else if (e.getTag() == "DiscreteDataFileNotFound") {
        // The data file could not be found.
        // Since the data file path is given in the Config file, throw critical exception to exit program so user can change the data file path
        throw CriticalException(errorPrinter, e.getProblem(), "Data file reading error");
    } else if (e.getTag() == "WritingFile") {
        // The results could not be written in the file specified by user (maybe access was denied).
        // Inform user and throw critical exception to exit the program.
        throw CriticalException(errorPrinter, e.getProblem(), "Writing to file error");
    } else if (e.getTag() == "LuaFileReadingFailed") {
        // The source file for a lua function (to define a continous function for the simulator) could not be found, or
        // could not interpreted correctly. Inform user and throw critical exception to exit the program.
        throw CriticalException(errorPrinter, e.getProblem(), "Function file reading error");
    } else {
        // Unexpected error was caught, inform user and throw critical exception to exit the program.
        throw CriticalException(errorPrinter, e.getProblem(), "Unexpected file error");
    }
}

// handles the Exceptions raised when a file could not be read properly
void ExceptionManager::handle(FileFormatException& e, std::ostream &printer, std::ostream &errorPrinter) const {
    if (e.getTag() == "DiscreteDataFileReading") {
        // The data file describing a discrete function could not be read (maybe CSV format not respected)
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "Data file reading error");
    } else if (e.getTag() == "NotEnoughPoints") {
        // The data file describing a discrete function contains only 1 point, which is not enough to interpolate.
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "Data file reading error");
    } else if (e.getTag() == "TypeMissMatch" || e.getTag() == "OutOFRange" || e.getTag() == "TooSmallDomain") {
        throw CriticalException(errorPrinter, e.getProblem(), "Error in " + e.getLocation());
    } else if (e.getTag() == "FileNotFound") {
        // A File could not be found, but we don't know which
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "File not found");
    }
    // Unexpected error occurred while searching for a file. Inform user and exit program by throwing a critical Exception.
    throw CriticalException(errorPrinter, e.getProblem(), "Unexpected file reading error");
}

// handles the Exceptions raised when a function could not be evaluated properly
void ExceptionManager::handle(FunctionException& e, std::ostream &printer, std::ostream &errorPrinter) const {
    if (e.getTag() == "MissingEvaluationMethod") {
        // The evaluation method for interpolating a discrete function was not specified in the config file.
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "Invalid interpolation method");
    } else if (e.getTag() == "FunctionEvaluationFailed") {
        // The function could not be evaluated (probably wrong input was given)
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "Error in function evaluation");
    }
    // Unexpected exception was caught. Inform user and exit program by throwing a critical exception.
    throw CriticalException(errorPrinter, e.getProblem(), "Unexpected function evaluation error");
}

// handles the Exceptions raised when the input of the program doesn't correspond to implemented features of the project
void ExceptionManager::handle(FunctionalityNotAvailableException& e, std::ostream &printer,
                              std::ostream &errorPrinter) const {
    if (e.getTag() == "Undefined interpolation method") {
        // The specified interpolation method (for evaluating discrete functions) doesn't exists.
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), e.getTag());
    } else if (e.getTag() == "InvalidDistribution") {
        // The specified distribution for the random creation of evaluation points doesn't exists.
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "Random Distribution error");
    } else if (e.getTag() == "InvalidFunctionType") {
        // The type of function is not available (Continuous, Discrete, ...)
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), "Function definition error");
    } else if (e.getTag() == "TooHighDimension") {
        throw CriticalException(errorPrinter, e.getProblem(), "Error in configuration file");
    } else if (e.getTag() == "Functionality not available") {
        // Generic Tag : the functionality is not precised
        // Inform user and exit program by throwing a critical exception.
        throw CriticalException(errorPrinter, e.getProblem(), e.getTag());
    }
    // Unexpected missing feature exception was caught.
    // Inform user and exit program by throwing a critical exception.
    throw CriticalException(errorPrinter, e.getProblem(), "Unexpected argument encountered");
}


void ExceptionManager::handle(Exception *e_ptr, std::ostream &printer, std::ostream &errorPrinter) const {
    FileNotFoundException *e_FileNotFound_ptr = dynamic_cast<FileNotFoundException *>(e_ptr);
    if (e_FileNotFound_ptr != nullptr) {
        ExceptionManager::handle(*e_FileNotFound_ptr, printer, errorPrinter);
        return;
    }
    FileFormatException *e_FileFormat_ptr = dynamic_cast<FileFormatException *>(e_ptr);
    if (e_FileFormat_ptr != nullptr) {
        ExceptionManager::handle(*e_FileFormat_ptr, printer, errorPrinter);
        return;
    }
    FunctionException *e_Function_ptr = dynamic_cast<FunctionException *>(e_ptr);
    if (e_Function_ptr != nullptr) {
        ExceptionManager::handle(*e_Function_ptr, printer, errorPrinter);
        return;
    }
    FunctionalityNotAvailableException *e_FunctionalityNotAvailable_ptr = dynamic_cast<FunctionalityNotAvailableException *>(e_ptr);
    if (e_FunctionalityNotAvailable_ptr != nullptr) {
        ExceptionManager::handle(*e_FunctionalityNotAvailable_ptr, printer, errorPrinter);
        return;
    }

    // Unknown error has be caught : inform user and exit program by throwing a critical exception.
    throw CriticalException(errorPrinter);
}
