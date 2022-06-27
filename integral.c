#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* calculam integral simples pelos respectivos métodos */
double simpson(int,int,int);
double trapezoidal(int,int);
/* calculam integral composta de x0 a xn-1 pelos respectivos métodos */
double simpComp();
double trapComp();

int n = 7;
double dados[][4] = 
    {
     /* x  F(x) O(x)  F(x)cos(O(x)) */
        { 0,  0,    .5,  0     },
        { 5,  9,   1.4,  1.5297},    
        {10, 13,    .75, 9.5120},
        {15, 14,    .9,  8.7025},
        {20, 10.5, 1.3,  2.8087},
        {25, 12,   1.48, 1.0881},
        {30,  5,   1.5,   .3538}
    };

double simpson(int ia, int im, int ib) {
    if (0 <= ia && ia < ib && ib < 7 && im == (ia+ib)/2 && (ia+ib)%2 == 0)
        ;
    else
        return NAN;

    double result = (dados[ib][0]-dados[ia][0])/6*(dados[ia][3] + 4*dados[im][3] + dados[ib][3]);
    //printf("sim_%d = %lf\n", ia, result);
    return result;
}

double trapezoidal(int ia, int ib) {
    if (0 <= ia && ia < ib && ib < 7)
        ;
    else
        return NAN;

    double result = (dados[ib][0]-dados[ia][0])/2*(dados[ia][3]+dados[ib][3]);
    //printf("trap_%d = %lf\n", ia, result);
    return result;
}

double simpComp() {
    double integral = 0;

    for (int k = 0; k < n-2; k += 2)
        integral += simpson(k,k+1,k+2);

    return integral;
}

double trapComp() {
    double integral = 0;

    for (int k = 0; k < n-1; k++)
        integral += trapezoidal(k,k+1);

    return integral;
}

int main(int argc, char *argv[]) {
    
    printf("Resultado das integrações numéricas da função F(x)cos(0(x)):\n");
    printf("regra trapézio composto: %lf\n", trapComp());
    printf("regra  simpson composto: %lf\n", simpComp());

    return 0;
}

