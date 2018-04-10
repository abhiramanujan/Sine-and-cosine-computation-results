#include <iostream>
#include <pthread.h>
#include <math.h>
#include <time.h>

double factorial(long n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

using namespace std;

#define MAX_THREADS 4 //Which can be changed according the laptops efficiency and the number of cores it has.
#define MAX 2000 //This number is the number of terms upto which each series needs to be computed to.
#define PI 3.14159265

double sineSum[MAX_THREADS];
double cosineSum[MAX_THREADS];
double sineResult, cosineResult;
int sinePart = 0, cosinePart = 0;
float rad = 0.0;
long x;
int task[MAX_THREADS+1];


void* sineArray(void *x)
{
    for(long i = task[(long)x]; i <task[(long)x+1]; i++) {   
        sineSum[sinePart] += (double)(pow(-1,i)*pow(rad,((2*i) + 1))/factorial((2*i) + 1));

    }
    sinePart++;
}

void* cosineArray(void *x)
{
    cosinePart++;
    for(long i = task[(long)x]; i <task[(long)x+1]; i++) {    
        cosineSum[cosinePart] += (double)(pow(-1,i)*pow(rad,(2*i))/factorial((2*i)));
    }
    
}

int main (int argc, char* argv[])
{
    float deg;
    struct timespec start, finish;
    double elapsed,sineTime,cosineTime;
    int i;
    double sineResult, cosineResult;

    float temp = atof(argv[1]);
    deg = fmod(temp,360.0);
    rad = deg*(PI/180);

    for(i = 0; i<MAX_THREADS; i++){ 
        task[i] = (i*MAX)/MAX_THREADS;
    }
    task[MAX_THREADS] = MAX;
    
    pthread_t sineThread[MAX_THREADS], cosineThread[MAX_THREADS];

    clock_gettime(CLOCK_MONOTONIC, &start);

    for(long l = 0; l < MAX_THREADS; l++) {
        pthread_create(&sineThread[l], NULL, sineArray,(void *)l);
    }

    for(long k = 0; k < MAX_THREADS; k++) {
        pthread_join(sineThread[k], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    sineTime = elapsed*1000;

    for(int k = 0; k < MAX_THREADS; k++) {
        sineResult += sineSum[k];
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    for(long j = 0; j < MAX_THREADS; j++) {
        pthread_create(&cosineThread[j], NULL, cosineArray, (void *)j);
    }

    for(int j = 0; j < MAX_THREADS; j++) {
        pthread_join(cosineThread[j], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cosineTime = elapsed*1000;
    
    for(int j = 0; j < MAX_THREADS; j++) {
        cosineResult += cosineSum[j];
    }
    

    cout.precision(10);
    cout<<"Sine of "<<deg<<" is : "<<sineResult<<"\nTime taken in sec to compute Sine : "<<sineTime<<"ms"<<endl;
    cout<<"Cosine of "<<deg<<" is : "<<cosineResult<<"\nTime taken in sec to compute Cosine : "<<cosineTime<<"ms"<<endl;
    return 0;
}
