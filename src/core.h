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

using namespace std ;

//----function prototype----
int getDmatrix(Matrix &D, int dim, double elastic_constant, double poisson_ratio) ;
int merge_Kmatrix(Matrix &K, Matrix &Km) ;
#endif