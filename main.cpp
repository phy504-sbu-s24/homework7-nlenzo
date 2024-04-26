#include <functional>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double f1(double x){
    return exp(-x*x);
}

double f2(double x){
    double eps = 1e-12;
    double u = 1/(x*(2-x)+eps);
    return sin(u)*sin(u);
}

/* Part a */
double trap(double a, double b, int N, std::function<double(double)> f){
    double deltaX = (b-a)/N;
    double sum = 0;
    for(int i=1; i<=N; i++){
        sum += (f(a+(i-1)*deltaX) + f(a+i*deltaX));
    }
    return 0.5*deltaX*sum;
}
/* Part b */
double montecarlo(double a, double b, double N, std::function<double(double)> f){
    double sum = 0;
    for(int i=1; i<= N; i++){
        double t = rand()/((double) RAND_MAX);
        double xi = a+(b-a)*t;
        sum += f(xi);
    }
    double avg_f = sum/N;
    return (b-a)*avg_f;
}


int main(){
    /* Part c */
    std::function<double(double)> func = f1;
    for(int N=8; N<=1024; N*=2){
        printf("%d,%.12lf,%.12lf\n",N,trap(-5,5,N,func),montecarlo(-5,5,N,func));
    }

    printf("\n\n");
    /* Part d */
    func = f2;
    for(int N=8; N<=1024; N*=2){
        printf("%d,%.12lf,%.12lf\n",N,trap(0,2,N,func),montecarlo(0,2,N,func));
    }
    return 0;
}