#include "IntegralApproximation.hpp"

#include <iomanip>
#include <iostream>


double IntegralApproximation::runApproximation(int x, int y){
  double start=0, end=1;
  double intervalLen = (end-start)/this->numThreads;
  double sum = 0;

  #pragma omp parallel num_threads(this->numThreads)
  {
    double a,b, fa, fb;
    int threadNum = omp_get_thread_num();
    a = threadNum * intervalLen;
    b = a + intervalLen;
    // TODO if b is the residual (not a full interval)

    fa = (*f)(a);
    fb = (*f)(b);

    double localArea = ((fa+fb)*intervalLen);

    #pragma omp critical
    sum += localArea;
    /*std::cout << std::fixed << std::setprecision(5) << "Thread: " << threadNum 
              << ", start: " << a 
              << ", end: " << b 
              << std::endl;
    */     
  }
  return sum/2;

}