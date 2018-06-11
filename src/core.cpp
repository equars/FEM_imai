//===============================
//core function for solve the FEM
//===============================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "core.h"
#include "matrix.h"

using namespace std ;

int getDmatrix(Matrix &D, int dim, double elastic_constant, double poisson_ratio){
    double L = elastic_constant/((1+ poisson_ratio)*(1-2*poisson_ratio)) ;
    if(dim == 2)
    {
        D[1][1] = (1 - poisson_ratio)/L ;
        D[2][2] = (1 - poisson_ratio)/L ;
        D[1][2] = poisson_ratio/L ;
        D[2][1] = poisson_ratio/L ;
        D[3][3] = (1 - 2*poisson_ratio)/(L*2) ;
    }
    return 0 ;
}

int merge_Kmatrix(Matrix &K, Matrix &Km){
    return 0 ;
}