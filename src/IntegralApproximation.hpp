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
    std::function<double(double)>* f;

  public:

    IntegralApproximation(int threads,
                          int trapezoids,
                          DataManager* manager,
                          std::function<double(double)>* f){
      this->setNumTrapezoids(trapezoids);
      this->setNumThreads(threads);
      this->timeManager = manager;
      this->f = f;
    }
    
    /**
     * @brief Run the approximation algorithm and record the time elapsed in our timeManager.
     * 
     * @return long double The approximation of pi.
     */
    long double runApproximation(double x, double y);

    void setNumThreads(int numThreads){
      if (numThreads > this->numTrapezoids) this->numThreads = this->numTrapezoids;
      else this->numThreads = numThreads;
    }

    int getNumThreads(){return this->numThreads;}

    void setNumTrapezoids(int numTrapezoids){this->numTrapezoids = numTrapezoids;}

    int getNumTrapezoids(){return this->numTrapezoids;}
};