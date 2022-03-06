#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <iostream>
#include <getopt.h>

#define DEFAULT_THREADS 1
#define DEFAULT_TRAPEZOIDS 1000000
#define USAGE "\nusage: ./MonteCarloApproximation -n NUMTHREADS -p NUMTRAPEZOIDS\n"\
              "\t-n optional flag that reads in NUMTHREADS (NUMTHREADS > 0, integer)\n"\
              "\t-p optional flag that reads in NUMTRAPEZOIDS (NUMTRAPEZOIDS > 0, integer)\n"

/**
 * @brief Arguments object to hold the values of the desired inputs given by the user.
 * 
 */
class Arguments{
  public:
    int numThreads;
    int numTrapezoids;

    /**
     * @brief Construct a new Arguments object with default values.
     * 
     */
    Arguments():numThreads(DEFAULT_THREADS), 
                numTrapezoids(DEFAULT_TRAPEZOIDS){}
};


/**
 * @brief Class to read in command line arguments and validate them. Fills an Arguments 
 *        object with the users desired input.
 */
class ArgParser {

  private:
    /**
     * @brief Reads in an string and returns the converted integer.
     * 
     * @param value String value to convert to an integer. 
     * @return int The converted integer. Returns -1 if the string was not successfully converted.
     */
    int readInt(char* value);

    /**
     * @brief Prints out the usage of our program.
     * 
     */
    void printUsage(){ std::cout << USAGE << std::endl; }
  
  public:
    Arguments* args;

    /**
     * @brief Construct a new Arg Parser object. Dynamically allocate the memory.
     * 
     */
    ArgParser() { args = new Arguments(); }

    /**
     * @brief Destroy the Arg Parser object and free the allocated memory.
     * 
     */
    ~ArgParser(){ delete args; }

    /**
     * @brief Method used to parse the flags from the user. Validates integer arguments
     * and exits if invalid.
     * 
     * @param argc The argument count provided to main().
     * @param argv The argument list provided to main().
     * @return Arguments* A pointer to an argument structure from which the user inputs
     *         can be read.
     */
    Arguments* parseArgs(int argc, char** argv);
};

#endif // ARG_PARSER_HPP
