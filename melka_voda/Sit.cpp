#include "Sit.h"
#include <fstream>
#include <iostream>

using namespace std;

Sit::Sit(double _start, double _stop, int _n, double _x_b)
{
    start = _start; //x pocatecni nezadano
    stop = _stop; //x koncove nezadano
    n = _n; //pocet uzlu site
    x_barrier = _x_b; //souradnice prehrady
    dx = (stop - start)/n;

    xi.resize(n+1);

    fstream soubor_x("x.txt", ios::out);
    for (int i=0; i<n+1; i++){
        xi[i] = start + i*dx;
        soubor_x<<xi[i]<<" ";
    }
}
