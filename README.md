# Sine-and-cosine-computation-results
Sequential code - SineACosine.cpp, which computes the sine and cosine series sequentially.
Parallelised code(using Pthreads) - SinaCosPthreads.cpp,  which computes the sine and cosine series parallely using the number of threads as 4(which can be changed accordingly to the efficiency of a laptop core).
Parallelized code(using OpenMP) - sineOMP.cpp, which compoutes the sine and cosine series parallely using its method of calls to the system on choosing the number of threads.( This program is done in i7 core of a dell laptop).

Parallelizing a code depends upon the following :-
1. The type of decomposition required based on the problem faced.
2. The method of parallelization needs to be choosed based on the outcomes required.
3. The number of threads to be assigned based on the decomposition of the problem.
4. Using libraries and environmental variables properly based on the preferences of the outcome.
5. The account of time taken for executing and running of the program.
