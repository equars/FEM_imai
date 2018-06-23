//===============================
//core function for solve the FEM
//===============================

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "matrix.h"
#include "material.h"

using namespace std ;

//----function prototype----
int getDmatrix(Material &obj, int dim, double elastic_constant, double poisson_ratio) ;
int merge_Kmatrix(Material &obj, Matrix &Km) ;
#endif
