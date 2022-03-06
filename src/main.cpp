#include "main.hpp"

int main(int argc, char** argv){
  ArgParser ap = ArgParser();
  Arguments* args = ap.parseArgs(argc, argv);
  DataManager manager = DataManager();
  std::function<double(double)> myFunction = [](double x){ return 4/(1+(x*x)); };
  IntegralApproximation mca = IntegralApproximation(args->numThreads, args->numTrapezoids, &manager, &myFunction);
  
  // mca.runApproximation();
  std::cout << std::fixed << std::setprecision(10) << mca.runApproximation(0,1) << "," << manager.average() << std::endl;

  return 0;
}