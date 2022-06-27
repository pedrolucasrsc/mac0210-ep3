#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
DETAILS ABOUT THE INTEGRAL THAT WE WANT TO EVALUATE
*/
const long double lower_limit = 3;
const long double higher_limit = 7;
//original function
long double f(long double x){
    return x*x*x;
}


/*
PROGRAM THAT APPROXIMATES THAT INTEGRAL
*/

//random number between 0 and 1
long double rnd(){
    long double r = rand()*1.0/RAND_MAX;
    return r;
}
//maps [0,1] to [lower_limit,higher_limit]
long double change_variable(long double x){
    return x*(higher_limit-lower_limit)+lower_limit;
}
//function g(original function after the change of variables)
long double g(long double x){
    return f(change_variable(x))*(higher_limit-lower_limit);
}
//approximates the value of the integral with Monte Carlo's method
long double monte_carlo(long long iterations){
    long double ans = 0;
    for(int i=0;i<iterations;i++){
        ans += g(rnd())/iterations;
    }
    return ans;
}
int main(){
    srand(time(NULL));
    printf("%Lf\n",monte_carlo(10000000));
}