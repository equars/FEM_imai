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
    Matrix A,B,C,L,U ;

    /*A.Reserve(4,4);
    A[0][0] = 8   ; A[0][1] = 16  ; A[0][2] = 24  ; A[0][3] = 32  ;
    A[1][0] = 2   ; A[1][1] = 7   ; A[1][2] = 12  ; A[1][3] = 17  ;
    A[2][0] = 6   ; A[2][1] = 17  ; A[2][2] = 32  ; A[2][3] = 59  ;
    A[3][0] = 7   ; A[3][1] = 22  ; A[3][2] = 46  ; A[3][3] = 105 ;
    */
    A.Reserve(8,8);
    A[0][0] =1 ; A[1][1] =1 ; A[2][2] =1 ;
    A[3][3] = 9   ; A[3][4] = 5  ; A[3][5] = 0  ; A[3][6] = -2  ; A[3][7] = -2  ;
    A[4][3] = 5   ; A[4][4] = 9   ; A[4][5] = 0  ; A[4][6] = -2  ; A[4][7] = -2  ;
    A[5][3] = 0  ; A[5][4] = 0  ; A[5][5] = 1  ; A[5][6] = 0  ; A[5][7] = 0  ;
    A[6][3] = -2   ; A[6][4] = -2  ; A[6][5] = 0  ; A[6][6] = 9 ; A[6][7] = 5  ;
    A[7][3] = -2   ; A[7][4] = -2  ; A[7][5] = 0  ; A[7][6] = 5 ; A[7][7] = 9  ;

    A.Lu(L,U);
    A.Inverse() ;
    B=L*U ;
    C=A*B ;
    A.Show();
    B.Show();
    C.Show();
    L.Show();
    U.Show();
}
