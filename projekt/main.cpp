// =========================== Dodanie bibliotek ===========================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "winbgi2.h"
#include "vrk4.h"

// ========================== Stale obliczeniowe ===========================
#define N 1000
#define dt .0001
#define l N*dt


// ================================= Main ==================================
int main(){

 // ========================== Alokacja zmiennych ==========================
    double x_0, v_0;
    double k, c, m;

 // ========================= Wczytanie zmiennych ==========================
    printf("\nProsze podac dane wejsciowe");

    printf("\nMasa m:");
    scanf("%lf", &m);

    printf("\nWspolczynnik sprezystosci k:");
    scanf("%lf", &k);

    printf("\nWspolczynnik tlumienia c:");
    scanf("%lf", &c);

    printf("\nWektor zagadnienia poczatkowego (x(0),v(0)):");
    scanf("%lf%lf", &x_0, &v_0);

    if (k < 0 || c < 0 || m <= 0 || x_0 == 0 || v_0 == 0) {
        printf("\nBledne dane wejsciowe, upewnij sie ze prawidlowo wprowadziles wartosci");
        return 0;
    }

    //printf("k:%lf,c:%lf,m:%lf,x_0:%lf,v_0:%lf", k, c, m, x_0, v_0);

 // ======================= Przygotowanie zmiennych ========================
    // Dla uproszczenia formulu pewnych funkcji oraz niewykonywania
    // wielokrotnie tych samych kosztownych operacji zamykam stale w 
    // jedna tablice C
    double* C = (double*)malloc(5 * sizeof(double));
    C[0] = k; C[1] = c; C[2] = m; C[3] = c / m; C[4] = k / m;

    // Deklaruje tablice wynikowa metody vrk4 ilosc liczonych punktow
    //jest stala i zdefiniowana na poczatku kodu
    double** X = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        X[i] = (double*)malloc(2 * sizeof(double));
    }
    X[0][0] = x_0;
    X[0][1] = v_0;

 // ===================== Rozwiazanie zagadnienia vrk4 =====================
    for (int i = 0; i < N-1; i++) {
        vrk4(i*dt,X[i],dt,2,vrk4_dot,C,X[i+1]);
    }
 // ============================ Wyznaczenie E =============================
    double* E = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        E[i] = C[2] / 2. * X[i][1] * X[i][1] + C[0] / 2. * X[i][0] * X[i][0]; // E = m/2*v^2 + k/2*x^2
    }

 // ============= Rozwiazanie zagadnienia analiza matematyczna =============
    
 // ========================== Wyznaczenie x v E ===========================
    
 // ========================= Wyswietlenie grafow ==========================
    double* _x = (double*)malloc(N * sizeof(double));
    double* _y = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        _x[i] = i * dt;
        _y[i] = X[i][0];
    }

    char name[50];
    char osx[50];
    char osy[50];
    sprintf(name, "k:%.2lf, c:%.2lf, m:%.2lf,",k,c,m);
    sprintf(osx, "t[s]");
    sprintf(osy, "x[m]");

    graphics(800, 800);
    chart(_x, _y, N, osx, osy,name);

 // ===================== Zwolnienie pamieci i wyjscie =====================
    
    for (int i = 0; i < N; i++) {
        free(X[i]);
    }
    free(_x);
    free(_y);
    free(X);
    free(C);
    wait();
    return 0;
}

