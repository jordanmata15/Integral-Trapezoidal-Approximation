# Integral-Trapezoidal-Approximation
## Description
An approximation of an integral using the trapezoidal rule on parallel threads. We demonstrate this using the integral of the function (1/1+x*x) over [0,1] to approximate pi. By increasing the number of trapezoids, we can increase the accuracy of the algorithm. We reduce the runtime using more threads (we enforce #Threads < #Trapezoids as there is no added benefit for more threads).

## Usage
The following flags can be passed in when running the binary to manually set the number of threads or trapezoids used. Both are required to be an integer greater than 0.<br>
-p <number_of_threads><br>
-n <number_of_trapezoids>

eg. <br>
The following will approximate pi with 1000 trapezoids and split the work to 8 threads.<br>
./IntegralApproximation -p 8 -n 1000

## Notes
The algorithm is accurate when the number of threads evenly divides the number of trapezoids (ie. ```#Trapezoids % #Threads == 0```). The algorithm loses accuracy otherwise.
