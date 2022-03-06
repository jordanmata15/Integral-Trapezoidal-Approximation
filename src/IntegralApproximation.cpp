#include "IntegralApproximation.hpp"


long double IntegralApproximation::runApproximation(double x1, double x2){
  long double globalSum = 0;

  struct timeval startTime, endTime, elapsedTime;
  gettimeofday(&startTime, NULL);

  #pragma omp parallel num_threads(this->getNumThreads()) reduction(+:globalSum)
  {
    long double h, x, localSum;
    long double threadStart, threadEnd;
    int localN;
    int threadNum = omp_get_thread_num();
    int threadCount = omp_get_num_threads(); // the kernel may assign us less cores than requested. Ask it directly.

    h = (x2-x1)/this->getNumTrapezoids();
    localN = this->getNumTrapezoids()/threadCount;
    threadStart = x1 + threadNum*localN*h;
    threadEnd = threadStart + localN*h;
    localSum = ((*f)(threadStart)+(*f)(threadEnd))/2.0;

    for (int i=1; i<=localN-1; ++i){
      x = threadStart + i*h;
      localSum += (*f)(x);
    }
    localSum *= h;

    globalSum += localSum;
  }

  gettimeofday(&endTime, NULL);
  timersub(&endTime, &startTime, &elapsedTime);
  timeManager->recordTime(&elapsedTime);

  return globalSum;
}