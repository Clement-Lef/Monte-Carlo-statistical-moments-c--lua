//
// Created by Clément Lefebvre on 13.12.16.
//

#include <fstream>
#include <iostream>
#include "MomentComputerManager.h"

/// Will create a Configuration file to test the program
void createConfig(int tag);
/// Runs the test of the program, with relative precision to pass in argument precision
void test(int tag, double precision);
/// Compute the mean of the vector argument
double mean(std::vector<double> moments);
/// A test is considered passed if the relative error of value compared to analytical_value is less than precision
bool pass_Test(double value, double analytical_value, double precision);

int main() {

    double precision = 0.01;
    // Executing all tests
    createConfig(1);
    test(1, precision);
    createConfig(2);
    test(2, precision);
    createConfig(3);
    test(3, precision);
    createConfig(4);
    test(4, precision);
    createConfig(5);
    test(5, precision);
    createConfig(6);
    test(6, precision);
    createConfig(7);
    test(7, precision);

    return 0;
}

// The tests consist in comparing the value of some computed moments with analytical results.
// The tests are passed if the relative error on the computed result is less than 1%
void test(int tag, double precision) {
    // Vector to store the results of the tests
    std::vector<double> moments;
    // Initialisation of the simulation with the ConfigTest.dat file, created by a previous call of createConfig in the main
    MomentComputerManager manager("ConfigTest.dat");
    unsigned int momentOrder;   // Moment order depends on the test we want to make
    // We will compute the mean of the results
    double meanMoment = 0;

    // boolean to attest if the test is failed or passed
    bool success = true; // Initialized to true

    if (tag == 1) {
        // Test 1 is the computation of the first and second moment of a continuously defined function : f(x) = x
        // The points distribution is set to Uniform over [0,1]

        // First moment
        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        // Compute the mean of the moments
        meanMoment = mean(moments);
        // Analytical result is 0.5
        success = pass_Test(meanMoment, 0.5, precision);

        // Moment of order 2
        momentOrder = 2;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 1/3
        success = pass_Test(meanMoment, 1.0/3.0, precision) || success;

    }
    else if (tag == 2) {
        // Test 2 is the computation of the first and second order moments of a continuously defined function f(x) = x
        // The point follow a Normal distribution, with mu = 2 and sigma = 3

        // First moment
        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 2
        success = pass_Test(meanMoment, 2.0, precision);

        // Second moment
        momentOrder = 2;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 13
        success = pass_Test(meanMoment, 13.0, precision) || success;

    }
    else if (tag == 3) {
        // Test 3 is the computation of the fist moment of a continuously defined function f(x) = x
        // Points distribution is exponential, with parameter lambda = 1/3

        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 3
        success = pass_Test(meanMoment, 3.0, precision);

    }
    else if (tag == 4) {
        // Test 4 is the computation of first and second moments of f(x) = x^2
        // Points distribution is uniform on [0,1]

        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 1/3
        success = pass_Test(meanMoment, 1.0/3.0, precision);

    }

    else if (tag == 5) {
        // Test 5 is the computation of first and second moments of continuous function f(x,y) = x + y
        // Points distribution is uniform on [2,3]^2

        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 5
        success = pass_Test(meanMoment, 5.0, precision);

        momentOrder = 2;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        // Analytical value is 151/6
        success = pass_Test(meanMoment, 151.0/6.0, precision) || success;

    }

    else if (tag == 6) {
        // Test 6 is the computation of the first moment of f(x,y) = x + y
        // Points distribution is Normal, with mu = 2 and sigma = 3

        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        success = pass_Test(meanMoment, 4.0, precision);

    }

    else if (tag == 7) {
        // Test 7 is the computation of the first moment of f(x) = x^2
        // In this test f is discretely defined in the file "fx=x2"
        // Points distribution is Normal, with mu = 2 and sigma = 3

        momentOrder = 1;
        moments = manager.computeMoments(momentOrder);
        meanMoment = mean(moments);
        success = pass_Test(meanMoment, 26.0/3.0, precision);

    }

    if (success) {
        std::cout << "Test "<< tag <<" successful : Moments computed are equals to the analytical value." << std::endl;
    } else {
        std::cout << "Test "<< tag <<" failed : too much difference between analytical and computed value." << std::endl;
    }




    // Test Moment computed == moment written in output file for last test

    if (tag == 7) {
        manager.printMoments(moments, "Test_Suite_Output");
        std::ifstream output_file("Test_Suite_Output");

        std::vector<double> printedMoments;
        std::string tmp;
        while (getline(output_file, tmp)) {
            printedMoments.push_back(std::atof(tmp.c_str()));
        }
        output_file.close();

        success = true; // Initialized to true
        for (int i = 0; i < moments.size(); i++) {
            if (moments[i] - printedMoments[i] > 0.0001) {
                success = false;
            }
        }

        if (success) {
            std::cout << "Test successful : Moments printed in the file are equals to the computed moments."
                      << std::endl;
        } else {
            std::cout << "Test failed : the printed moments does not corresponds to the computed moments." << std::endl;
        }
    }

}


void createConfig(int tag) {
    // Create test ConfigFiles

        if (tag == 1) {
            std::ofstream config1("ConfigTest.dat");
            config1 << "Type Of Function = \"Continuous\"" << std::endl;
            config1 << "Dimension = \"1\" " << std::endl;
            config1 << "Interpolation method = \"Linear\"" << std::endl;
            config1 << "File Name = \"Continuous_Function_Test1.lua\"" << std::endl;
            config1 << "Distribution = \"Uniform\"" << std::endl;
            config1 << "Domain Left Side = \"0\"" << std::endl;
            config1 << "Domain Right Side = \"1\"" << std::endl;
            config1 << "Mean = \"0\"" << std::endl;
            config1 << "Standard deviation = \"1\"" << std::endl;
            config1 << "Lambda = \"0.33\"" << std::endl;
            config1 << "Seed of random generator = \"0\"" << std::endl;
            config1 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config1 << "Number Of Simulation = \"100\"" << std::endl;
            config1.close();
        }
        else if (tag == 2) {
            std::ofstream config2("ConfigTest.dat");
            config2 << "Type Of Function = \"Continuous\"" << std::endl;
            config2 << "Dimension = \"1\" " << std::endl;
            config2 << "Interpolation method = \"Linear\"" << std::endl;
            config2 << "File Name = \"Continuous_Function_Test1.lua\"" << std::endl;
            config2 << "Distribution = \"Normal\"" << std::endl;
            config2 << "Domain Left Side = \"0\"" << std::endl;
            config2 << "Domain Right Side = \"1\"" << std::endl;
            config2 << "Mean = \"2\"" << std::endl;
            config2 << "Standard deviation = \"3\"" << std::endl;
            config2 << "Lambda = \"0.33\"" << std::endl;
            config2 << "Seed of random generator = \"0\"" << std::endl;
            config2 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config2 << "Number Of Simulation = \"100\"" << std::endl;
            config2.close();
        }

        else if (tag == 3) {
            std::ofstream config2("ConfigTest.dat");
            config2 << "Type Of Function = \"Continuous\"" << std::endl;
            config2 << "Dimension = \"1\" " << std::endl;
            config2 << "Interpolation method = \"Linear\"" << std::endl;
            config2 << "File Name = \"Continuous_Function_Test1.lua\"" << std::endl;
            config2 << "Distribution = \"Exponential\"" << std::endl;
            config2 << "Domain Left Side = \"0\"" << std::endl;
            config2 << "Domain Right Side = \"1\"" << std::endl;
            config2 << "Mean = \"2\"" << std::endl;
            config2 << "Standard deviation = \"3\"" << std::endl;
            config2 << "Lambda = \"0.33333333333\"" << std::endl;
            config2 << "Seed of random generator = \"0\"" << std::endl;
            config2 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config2 << "Number Of Simulation = \"100\"" << std::endl;
            config2.close();
        }

        else if (tag == 4) {
            std::ofstream config2("ConfigTest.dat");
            config2 << "Type Of Function = \"Discrete\"" << std::endl;
            config2 << "Dimension = \"1\" " << std::endl;
            config2 << "Interpolation method = \"Linear\"" << std::endl;
            config2 << "File Name = \"fx=x2\"" << std::endl;
            config2 << "Distribution = \"Uniform\"" << std::endl;
            config2 << "Domain Left Side = \"0\"" << std::endl;
            config2 << "Domain Right Side = \"1\"" << std::endl;
            config2 << "Mean = \"2\"" << std::endl;
            config2 << "Standard deviation = \"3\"" << std::endl;
            config2 << "Lambda = \"0.33\"" << std::endl;
            config2 << "Seed of random generator = \"0\"" << std::endl;
            config2 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config2 << "Number Of Simulation = \"100\"" << std::endl;
            config2.close();
        }

        else if (tag == 5) {
            std::ofstream config2("ConfigTest.dat");
            config2 << "Type Of Function = \"Continuous\"" << std::endl;
            config2 << "Dimension = \"2\" " << std::endl;
            config2 << "Interpolation method = \"Linear\"" << std::endl;
            config2 << "File Name = \"Continuous_Function_Test2.lua\"" << std::endl;
            config2 << "Distribution = \"Uniform\"" << std::endl;
            config2 << "Domain Left Side = \"2\"" << std::endl;
            config2 << "Domain Right Side = \"3\"" << std::endl;
            config2 << "Mean = \"2\"" << std::endl;
            config2 << "Standard deviation = \"3\"" << std::endl;
            config2 << "Lambda = \"0.33\"" << std::endl;
            config2 << "Seed of random generator = \"0\"" << std::endl;
            config2 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config2 << "Number Of Simulation = \"100\"" << std::endl;
            config2.close();
        }

        else if (tag == 6) {
            std::ofstream config2("ConfigTest.dat");
            config2 << "Type Of Function = \"Continuous\"" << std::endl;
            config2 << "Dimension = \"2\" " << std::endl;
            config2 << "Interpolation method = \"Linear\"" << std::endl;
            config2 << "File Name = \"Continuous_Function_Test2.lua\"" << std::endl;
            config2 << "Distribution = \"Normal\"" << std::endl;
            config2 << "Domain Left Side = \"2\"" << std::endl;
            config2 << "Domain Right Side = \"3\"" << std::endl;
            config2 << "Mean = \"2\"" << std::endl;
            config2 << "Standard deviation = \"3\"" << std::endl;
            config2 << "Lambda = \"0.33\"" << std::endl;
            config2 << "Seed of random generator = \"0\"" << std::endl;
            config2 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config2 << "Number Of Simulation = \"100\"" << std::endl;
            config2.close();
        }


        else if (tag == 7) {
            std::ofstream config2("ConfigTest.dat");
            config2 << "Type Of Function = \"Discrete\"" << std::endl;
            config2 << "Dimension = \"1\" " << std::endl;
            config2 << "Interpolation method = \"Linear\"" << std::endl;
            config2 << "File Name = \"fx=x2\"" << std::endl;
            config2 << "Distribution = \"Uniform\"" << std::endl;
            config2 << "Domain Left Side = \"1\"" << std::endl;
            config2 << "Domain Right Side = \"3\"" << std::endl;
            config2 << "Mean = \"2\"" << std::endl;
            config2 << "Standard deviation = \"3\"" << std::endl;
            config2 << "Lambda = \"0.33\"" << std::endl;
            config2 << "Seed of random generator = \"0\"" << std::endl;
            config2 << "Number Of Evaluation Points = \"10000\"" << std::endl;
            config2 << "Number Of Simulation = \"100\"" << std::endl;
            config2.close();
        }
}

double mean(std::vector<double> moments) {
    double meanMoment = 0;
    for (int i = 0; i < moments.size(); i++) {
        meanMoment += moments[i];
    }
    return meanMoment/moments.size();
}

bool pass_Test(double value, double analytical_value, double precision) {
    if (std::abs((value-analytical_value)/analytical_value) > precision)
        return false;
    return true;
}