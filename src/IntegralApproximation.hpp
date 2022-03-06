#ifndef __INTEGRAL_APPROXIMATION_HPP__
#define __INTEGRAL_APPROXIMATION_HPP__

#include <functional>
#include <omp.h>
#include <random>
#include <sys/time.h>
#include "DataManager.hpp"

/**
 * @brief Simulation of Trapezoidal Rule algorithm for approximating an integral.
 * 
 */
class IntegralApproximation {

  private:
    int numThreads;
    int numTrapezoids;
    DataManager* timeManager;
    std::function<long double(long double)>* f;

  public:

    /**
     * @brief Construct a new Integral Approximation object. Ensures numThreads <= numTrapezoids
     * 
     * @param threads The number of threads to parallelize with.
     * @param trapezoids The number of trapezoids to use in our approximation.
     * @param manager The time manager object to store the time elapsed.
     * @param f The function to calculate the integral for.
     */
    IntegralApproximation(int threads,
                          int trapezoids,
                          DataManager* manager,
                          std::function<long double(long double)>* f){
      this->setNumTrapezoids(trapezoids);
      this->setNumThreads(threads);
      this->timeManager = manager;
      this->f = f;
    }
    
    /**
     * @brief Run the approximation algorithm and record the time elapsed in our timeManager.
     * 
     * @param x The starting x coordinate of the integral.
     * @param y The ending x coordinate of the integral.
     * @return long double The approximation of pi.
     */
    long double runApproximation(long double x, long double y);

    /**
     * @brief Set the Num Threads object. Enforces numThreads <= numTrapezoids.
     * 
     * @param numThreads The number of threads to parallelize with.
     */
    void setNumThreads(int numThreads){
      if (numThreads > this->numTrapezoids) this->numThreads = this->numTrapezoids;
      else this->numThreads = numThreads;
    }

    /**
     * @brief Get the Num Threads count
     * 
     * @return int The number of threads to use.
     */
    int getNumThreads(){return this->numThreads;}

    /**
     * @brief Set the Num Trapezoids count
     * 
     * @param numTrapezoids The number of trapezoids to approximate with.
     */
    void setNumTrapezoids(int numTrapezoids){this->numTrapezoids = numTrapezoids;}

    /**
     * @brief Get the Num Trapezoids object
     * 
     * @return int The number of trapezoids to use.
     */
    int getNumTrapezoids(){return this->numTrapezoids;}
};

#endif // __INTEGRAL_APPROXIMATION_HPP__