#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* calcula pesos para interpolação de Lagrange */
void barycentricWeights(double**);
/* avalia p(x) de Lagrange */
double avalLagrange(double);

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

    // x < x0 || xn-1 < x ?
    if (x < dados[0][0] || dados[6][0] < x)
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

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 1;

    double x;
    sscanf(argv[1],"%lf",&x);
    printf("%lf\n",avalLagrange(x));

    return 0;
}

