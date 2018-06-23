#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "matrix.h"

using namespace std ;

Matrix A ;

A.Reserve(3,3);
A[0][0] = 1 ; A[0][1] = 2 ; A[0][2] = 3 ;
A[1][0] = 1 ; A[1][1] = 1 ; A[1][2] = 1 ;
A[2][0] = 1 ; A[2][1] = 1 ; A[2][2] = 1 ;

A.Inverse();
A.Show();
