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

int main(){
    Matrix A,L,U ;

    A.Reserve(4,4);
    A[0][0] = 8   ; A[0][1] = 16  ; A[0][2] = 24  ; A[0][3] = 32  ;
    A[1][0] = 2   ; A[1][1] = 4   ; A[1][2] = 12  ; A[1][3] = 17  ;
    A[2][0] = 6   ; A[2][1] = 17  ; A[2][2] = 32  ; A[2][3] = 59  ;
    A[3][0] = 7   ; A[3][1] = 22  ; A[3][2] = 46  ; A[3][3] = 105 ;

    A.Inverse();
    A.Show();
    L.Show();
    U.Show();
}
