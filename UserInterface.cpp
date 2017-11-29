//
// Created by Clément Lefebvre on 21.11.16.
//

#include <iostream>
#include "MomentComputerManager.h"
#include "FileNotFoundException.h"
#include "FileFormatException.h"
#include "FunctionException.h"
#include "FunctionalityNotAvailableException.h"
#include "ExceptionManager.h"
#include "Custom_Util.h"


int main() {

    // This is in preparation for a graphic interface
    std::ostream &printer = std::cout;
    std::ostream &errorPrinter = std::cerr;

    /* Initialization of the Monte Carlo Simulator */
    printer << "Welcome to the Monte Carlo Simulator to compute Statistical Moments !" << std::endl;

    std::string configFile = "";       // string to read the configuration file (or quit to stop the program)
    ExceptionManager exceptionManager; // Initialization of the error manager

    /* Following this comment is the terminal interface for the program */
    while (configFile != "quit") {

        // ask for the configuration file
        printer << "Please input the name of your configuration file : (quit to exit program) ";
        getline(std::cin, configFile);

        try {
            if (configFile != "quit") {
                MomentComputerManager manager(configFile);          // Initialisation of the SimulationManager reading the config file
                printer << "\n Your configuration is the following : " << std::endl;
                manager.printConfig(printer);
                printer << "\n";

                std::string choiceMoment = "yes";               // We will compute moments as long as the user wants
                while (choiceMoment != "no") {
                    if (choiceMoment == "yes") {
                        std::vector<double> moments;            // vector to store the moments
                        printer << "Which order of the moment do you want to compute ? : ";
                        unsigned int moment_order = 0;

                        bool wrongInput = true;                 // read moment order from user
                        while (wrongInput) {
                            std::string moment_order_String;
                            getline(std::cin,moment_order_String);
                            try {
                                moment_order = Custom_Util::stringToUnsignedInt(moment_order_String, "Moment order", "main");
                                wrongInput = false;
                            } catch (FileFormatException &e) {
                                // Moment order could not be interpreted as an unsigned int
                                printer << "Please input a positive integer : ";
                            }
                        }

                        std::string output_name;                // Ask user for an output file to write the moments to
                        printer << "Please enter the name of the output file : ";
                        getline(std::cin, output_name);

                        printer << "Computing ..." << std::endl;

                        moments = manager.computeMoments(moment_order); // Compute the moment
                        manager.printMoments(moments, output_name); // Print the moment in the output file
                    }
                    printer << "Do you want to compute another moment ? (yes, no) ";
                    getline(std::cin, choiceMoment);
                }
            }
        } catch (Exception &e) {
            // Here we catch all Exceptions thrown during the execution of the program (except the moment order reading)
            /* The exceptions are given to the Exception Manager which will handle them depending on their derived type
             * To ensure polymorphism, we need to pass the Exception manager a pointer to the exception caught.
             */
            Exception *e_ptr = &e;
            try {   // If the exception can not be dealt with by the program, the Exception Manager throws a critical exception
                exceptionManager.handle(e_ptr,printer, errorPrinter);
            } catch (CriticalException e) {
                // Critical exception has been thrown, informing the user of the error. The simulator stops.
                return EXIT_FAILURE;
            }
        }
    }


    return 0;
}

