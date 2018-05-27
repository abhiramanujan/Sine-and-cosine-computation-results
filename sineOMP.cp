#include <iostream>
#include <math.h>
#include <time.h>
#include<omp.h>
#include <stdlib.h>

using namespace std;

#define MAX 2000
#define PI 3.14159265

double cosineResult,sineResult;

double factorial(long n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main (int argc, char* argv[])
{
    float deg,rad;
    struct timespec start, finish,start2, finish2;
    double elapsed,elapsed2,sineTime,cosineTime;
    int nthreads=4,chunk=100,tid;
    int i;
    float temp = atof(argv[1]);
    deg = fmod(temp,360.0);
    cout<<"degree :"<<deg<<endl;
    rad = deg*(PI/180);
    cout<<omp_get_max_threads()<<endl;

	double st = omp_get_wtime();
    #pragma omp parallel shared(sineResult,cosineResult, nthreads,chunk) private(tid,i)
    {
	tid = omp_get_thread_num();
	if(tid == 0)
	{        
		nthreads = omp_get_num_threads();
		cout<<"starting with : " <<nthreads<<"  number of threads"<<endl;
	}

	#pragma omp for schedule(static, chunk)
            for(i = 0;i <= MAX; i++) {     
            	sineResult += (double)(pow(-1,i)*pow(rad,(2*i) + 1)/factorial((2*i) + 1));
            }        
	#pragma omp for schedule( static , chunk)
	    for(i = 0; i <= MAX; i++) {     
            	cosineResult  += (double)(pow(-1,i)*pow(rad,(2*i))/factorial((2*i)));
            }
    }
	double end = omp_get_wtime();
    cout.precision(10);
    cout<<"Sine of "<<deg<<" is : "<<sineResult<<endl;
    cout<<"Cosine of "<<deg<<" is : "<<cosineResult<<endl;
    cout<<"Total time taken is :"<<((end-st)*1000)<<"ms"<<endl;
    return 0;
}
