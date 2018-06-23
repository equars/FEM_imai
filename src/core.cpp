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
#include "material.h"

using namespace std ;

int getDmatrix(Material &obj, int dim, double elastic_constant, double poisson_ratio){
    if (obj.unit == 0) {
        elastic_constant = elastic_constant * 1000 ;
    }
    double L = elastic_constant/((1+ poisson_ratio)*(1-2*poisson_ratio)) ;
    if(dim == 2)
    {
        obj.D[0][0] = (1 - poisson_ratio)*L ;
        obj.D[1][1] = (1 - poisson_ratio)*L ;
        obj.D[0][1] = poisson_ratio*L ;
        obj.D[1][0] = poisson_ratio*L ;
        obj.D[2][2] = L*(1 - 2*poisson_ratio)/2 ;
    }
    return 0 ;
}

int merge_Kmatrix(Material &obj, Matrix &Km){
    return 0 ;
}
