#ifndef VRK_4
#define VRK_4

// ============================ Funkcje wlasne =============================

// Konwencja X i F : X[0] = x X[1] = v
// Konwencja C : C[0] = k C[1] = c C[2] = m C[3] = c/m C[4] = k/m
// Funkcja liczaca prawe strony rownan rozniczkowych
void vrk4_dot(double t, double* X, double* F, double* C);

// Funkcja wykonujaca jeden krok dt calkowania metoda Rugego-Kutty 4 rzedu 
// X jest tablica wartosci w punkcie t wielkosci n, X1 to wyznaczone wartosci ró¿niczek 
void vrk4(double t, double* X, double _dt, int n, void (*fun)(double, double*, double*, double*), double* C, double* X1);
#endif 