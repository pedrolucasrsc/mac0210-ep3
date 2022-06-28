#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* calcula pesos para interpolação de Lagrange */
void barycentricWeights(double**);
/* avalia p(x) de Lagrange */
double avalLagrange(double);

/* calculam integral simples pelos respectivos métodos */
double simpson(double,double);
double trapezoidal(double,double);
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

void barycentricWeights(double **weight) {
    double aux[n];
    for (int j = 0; j < n; j++)
        aux[j] = 1;
    
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++) {
            if (i == j) continue;

            aux[j] *= (dados[j][0] - dados[i][0]);
        }

    for (int j = 0; j < n; j++)
        (*weight)[j] = 1/aux[j];

    return;
}

double avalLagrange(double x) {
    // x == xi? i = 0...n-1
    for (int i = 0; i < n; i++)
        if (x == dados[i][0])
            return dados[i][3];

    double x0 = dados[0][0], xn_1 = dados[n-1][0];
    // x < x0 || xn-1 < x ?
    if (x < x0 || xn_1 < x)
        return NAN;

    double *weight, phi = 1, p = 0;
    weight = malloc(n * sizeof(double));

    barycentricWeights(&weight);

    for (int i = 0; i < n; i++)
        phi *= (x - dados[i][0]);

    for (int j = 0; j < n; j++)
        p += weight[j]*dados[j][3]/(x-dados[j][0]);
    
    return p*phi;
}

double simpson(double a, double b) {
    double x0 = dados[0][0], xn_1 = dados[n-1][0];
    if (x0 <= a && a < b && b <= xn_1)
        ;
    else
        return NAN;

    double result = (b-a)/6*(avalLagrange(a) + 4*avalLagrange((a+b)/2) + avalLagrange(b));
    //printf("sim_%d = %lf\n", ia, result);
    return result;
}

double trapezoidal(double a, double b) {
    double x0 = dados[0][0], xn_1 = dados[n-1][0];
    if (x0 <= a && a < b && b <= xn_1)
        ;
    else
        return NAN;

    double result = (b-a)/2*(avalLagrange(a)+avalLagrange(b));
    //printf("trap_%d = %lf\n", ia, result);
    return result;
}

double simpComp(double h) {
    // aplica simpson em k intervalos de tamanho 2h
    double x0 = dados[0][0], xn_1 = dados[n-1][0];
    int k = (xn_1-x0)/(2*h);
    double integral = 0;
    
    for (int i = 0; i < k; i++)
        integral += simpson(x0 + i*2*h, x0 + (i+1)*2*h);

    return integral;
}

double trapComp(double h) {
    // aplica trapezoidal em k intervalos de tamanho h
    double x0 = dados[0][0], xn_1 = dados[n-1][0];
    int k = (xn_1-x0)/h;
    double integral = 0;

    for (int i = 0; i < k; i++)
        integral += trapezoidal(x0 + i*h, x0 + (i+1)*h);

    return integral;
}

int main(int argc, char *argv[]) {
    double h;
    printf("\nIremos integrar a função F(x)cos(0(x)) a partir das regras compostas nos intervalos:\n");
    printf("trapézio: [x0,x0+h][x0+h,x0+2h]...[x0+(k-1)h,xn_1]\n");
    printf(" simpson: [x0,x0+2h][x0+2h,x0+4h]...[x0+(k-2)h,xn_1]\n\n");
    
    printf("Escolha um valor para o tamanho do intervalo h: ");
    scanf("%lf",&h);
    printf("\n");

    printf("Resultado das integrações numéricas da função F(x)cos(0(x)):\n");
    printf("regra trapézio composto: %lf\n", trapComp(h));
    printf("regra  simpson composto: %lf\n\n", simpComp(h));

    return 0;
}

