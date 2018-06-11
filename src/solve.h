//===============================
//The function of solve
//===============================

#ifndef SOL_H
#define SOL_H

#include <iostream>
#include <vector>

#include "material.h"
#include "core.h"

using namespace std ;

//----function prototype----
int solve(Material &obj, int dim) ; //make K matrix and solve them and get distribution of stress and strain.

#endif