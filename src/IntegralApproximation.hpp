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
    double radius;
    int numThreads;
    int numTrapezoids;
    DataManager* timeManager;
    std::function<double(double)>* f;

  public:

    IntegralApproximation(int numThreads, int numTrapezoids, DataManager* manager, std::function<double(double)>* f): radius(1),
                                                                                      numThreads(numThreads),
                                                                                      numTrapezoids(numTrapezoids),
                                                                                      timeManager(manager),
                                                                                      f(f){}
    
    /**
     * @brief Run the approximation algorithm and record the time elapsed in our timeManager.
     * 
     * @return double The approximation of pi.
     */
    double runApproximation(int x, int y);
};
