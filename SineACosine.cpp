#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define MAX 2000
#define PI 3.14159265

double cosineResult,sineResult;

double factorial(long n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void sineSeries(float rad)
{
    for(int i = 0;i <= MAX; i++) {     
        sineResult += (double)(pow(-1,i)*pow(rad,(2*i) + 1)/factorial((2*i) + 1));
    }
}

void cosineSeries(float rad)
{   
    for(int i = 0; i <= MAX; i++) {     
        cosineResult  += (double)(pow(-1,i)*pow(rad,(2*i))/factorial((2*i)));
    }
}

int main (int argc, char* argv[])
{
    float deg,rad;
    struct timespec start, finish;
    double elapsed,sineTime,cosineTime;
    
    int i;
    float temp = atof(argv[1]);
    deg = fmod(temp,360.0);
    rad = deg*(PI/180);

    clock_gettime(CLOCK_MONOTONIC, &start);
    sineSeries(rad);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    sineTime = elapsed*1000;
  
    clock_gettime(CLOCK_MONOTONIC, &start);
    cosineSeries(rad);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cosineTime = elapsed*1000;
    
    cout.precision(10);
    cout<<"Sine of "<<deg<<" is : "<<sineResult;
    cout<<"\nTime taken to compute Sine : "<<sineTime<<"ms"<<endl;
    cout<<"Cosine of "<<deg<<" is : "<<cosineResult;
    cout<<"\nTime taken to compute Cosine : "<<cosineTime<<"ms"<<endl;
    
    return 0;
}
