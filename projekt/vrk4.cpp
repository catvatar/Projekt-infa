#include <stdlib.h>

void vrk4_dot(double t, double* X, double* F, double* C) {
    F[0] = X[1]; //x' = v
    F[1] = -C[3] * X[1] - C[4] * X[0]; //v' = - c/m * v - k/m * x
    return;
}

void vrk4(double t, double* X, double _dt, int n, void (*fun)(double, double*, double*, double*), double* C, double* X1) {
    double* k1 = (double*)malloc(n * sizeof(double));
    double* k2 = (double*)malloc(n * sizeof(double));
    double* k3 = (double*)malloc(n * sizeof(double));
    double* k4 = (double*)malloc(n * sizeof(double));
    double* tempOut = (double*)malloc(n * sizeof(double));
    double* tempIn = (double*)malloc(n * sizeof(double));

    //tempOut = fun(t,X)
    fun(t, X, tempOut, C);
    //k1 = dt*fun(X)
    //tempIn = Y + k1/2
    for (int i = 0; i < n; i++) {
        k1[i] = tempOut[i] * _dt;
        tempIn[i] = X[i] + k1[i] / 2.;
    }

    //tempOut = fun(t+dt/2,Y+k1/2)
    fun(t + _dt / 2., tempIn, tempOut, C);
    //k2 = dt*fun(Y + k1/2)
    //tempIn = Y + k2/2
    for (int i = 0; i < n; i++) {
        k2[i] = tempOut[i] * _dt;
        tempIn[i] = X[i] + k2[i] / 2.;
    }

    //tempOut = fun(t+dt/2,Y+k2/2)
    fun(t + _dt / 2., tempIn, tempOut, C);
    //k3 = dt*fun(t+dt/2,Y+k2/2)
    //tempIn = Y + k3
    for (int i = 0; i < n; i++) {
        k3[i] = tempOut[i] * _dt;
        tempIn[i] = X[i] + k3[i];
    }

    //tempOut = fun(t+dt,Y+k3)
    fun(t + _dt, tempIn, tempOut, C);
    //k4 = dt*fun(t+dt,Y+k3)
    for (int i = 0; i < n; i++) {
        k4[i] = tempOut[i] * _dt;
    }

    free(tempOut);
    free(tempIn);

    //X1 = Y + (k1 + 2*k2 + 2*k3 + k4)/6
    for (int i = 0; i < n; i++) {
        X1[i] = X[i] + (k1[i] + 2. * k2[i] + 2. * k3[i] + k4[i]) / 6.;
    }

    free(k1); free(k2); free(k3); free(k4);

    return;
}