//================================
//define matrix object
//================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "matrix.h"

using namespace std ;

//----function prototype----
double cofex(const Matrix v) ;

int Matrix::Transpose(){
    if (sym_flag == 1)
    {
        return 0 ; //no operation if symmetric matrix.
    }
    int m, n ; //size of Matrix
    double tmp ;
    Matrix v ;
    m = this->length_row ;
    n = this->length_column ;
    if (m == n)
    {
        for (int i = 0; i < this->length_row; i++)
        {
            for (int j = i+1; j < this->length_column; j++)
            {
                tmp = cell[i][j] ;
                cell[i][j] = cell[j][i] ;
                cell[i][j] = tmp ;
            }
        }
    }else
    {
        v.Reserve(n,m) ;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                v.cell[i][j] = cell[j][i] ;
            }
        }
        cell = v.cell ;
        length_row = n ;
        length_column = m ;
    }
    return 0 ;
}

int Matrix::Inverse(){
    int length_column_exp = 2*this->length_column ; //expanded length.
    if(length_column != length_row)
    {
        cout << "Error : size is different from row and column. [calc_objects.cpp " << __LINE__ << "]\n" ;
        return -1 ;
    }
    Matrix L,U,I,Linv,Uinv,t,v ;

    t.cell = this->cell ;
    t.length_row = this->length_row ;
    t.length_column = this->length_column ;
    if(t.Lu(L,U) == 0 ){
        I.Reserve(length_row, length_column) ; //make unit matrix to get inverse of L and U
        for(int i=0;i<length_row;i++)
        {
            I.cell[i][i] = 1 ;
        }
        L = L|I ; // combine
        U = U|I ; // combine
        for(int i=0;i<length_row;i++)
        {
            double pivot_L = L[i][i] ; //pivot of matrix L
            for(int j=i;j<length_column_exp;j++)
            {
                L[i][j] = L[i][j]/pivot_L ; //row normalize for head is 1
            }
            for(int j=i+1;j<length_row;j++)
            {
                double head_L = L[j][i] ; //head column of this term about matrix L
                double head_U = U[length_row-1-j][length_column-1-i] ; //head column of this term about matrix U
                L[j][i] = 0 ;
                U[length_row-1-j][length_column-1-i] = 0 ;
                for(int k=i+1;k<length_column_exp;k++)
                {
                    L[j][k] = L.cell[j][k]-L[i][k]*head_L ;
                    U[length_row-1-j][k] = U[length_row-1-j][k]-U[length_row-1-i][k]*head_U ;
                }
            }
        }
        Linv.Reserve(length_row, length_column) ;
        Uinv.Reserve(length_row, length_column) ;
        for(int i=0;i< length_row;i++)
        {
            for(int j=0;j< length_column;j++)
            {
                Linv[i][j] = L[i][j+length_column] ;
                Uinv[i][j] = U[i][j+length_column] ;
            }
        }
        v = Uinv*Linv ;
        this->cell = v.cell ;
    }else{
        cout << "with no LU" << "\n" ;
        I.Reserve(length_row, length_column) ;
        for(int i=0;i<length_row;i++)
        {
            I[i][i] = 1 ;
        }
        t = t|I ;

        cout << t.length_row << " " << t.length_column ;

        for (int i = 0; i < t.length_row; i++) {
            for (int j = 0; j < t.length_column; j++) {
                t[i][j] = t[i][j]/t[i][i] ;
            }
            for (int j = i+1; j < t.length_row; j++) {
                double piv = t[j][i] ;
                for (int k = 0; k < t.length_column; k++) {
                    t[j][k] = t[j][k] - t[i][k]*piv ;
                }
            }
        }
        for (int i = length_row - 1 ; i >= 0; i--) {

        }
        t.Show() ;
    }
    return 0 ;
}

int Matrix::Reserve(int size_row, int size_column){
    Matrix v ;
    vector<double> zero_line ;
    v.cell.reserve(size_row) ;
    zero_line.reserve(size_column) ;
    this->length_row = size_row ;
    this->length_column = size_column ;
    for (int i = 0; i < size_column; i++)
    {
        zero_line.push_back(0) ;
    }
    for (int i = 0; i < size_row; i++)
    {
        v.cell.push_back(zero_line) ;
    }
    this->cell = v.cell ;
    return 0 ;
}

int Matrix::Show(){
    cout << "row    -> " << length_row << "\n" ;
    cout << "column -> " << length_column << "\n" ;
    for (int i = 0; i < length_row; i++)
    {
        for (int j = 0; j < length_column; j++)
        {
            cout << cell[i][j] << " " ;
        }
        cout << "\n" ;
    }
    return 0 ;
}

int Matrix::Lu(Matrix &L, Matrix &U)
{
    Matrix A;
    A = *this ;
    int n = length_row ;
    L.Reserve(n,n) ;
    U.Reserve(n,n) ;

    if(n <= 0){
        return 0 ;
    }

    for(int i = 0; i < n; ++i){
        // L
        for(int j = 0; j <= i; ++j){
            double lu = A[i][j];
            for(int k = 0; k < j; ++k){
                lu -= A[i][k]*A[k][j];    // l_ik * u_kj
            }
            A[i][j] = lu;
        }

        // U
        for(int j = i+1; j < n; ++j){
            double lu = A[i][j];
            for(int k = 0; k < i; ++k){
                lu -= A[i][k]*A[k][j];    // l_ik * u_kj
            }
            if (A[i][i] == 0) {
                return -1 ;
            }
            A[i][j] = lu/A[i][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                L[i][j] = A[i][j] ;
            }else if (i == j) {
                L[i][i] = A[i][i] ;
                U[i][i] = 1 ;
            }else{
                U[i][j] = A[i][j] ;
            }
        }
    }

    return 0;
}

double Matrix::Det(){
    Matrix v ;
    v.cell = this->cell ;
    if (v.cell.size() != v.cell[0].size())
    {
        cout << "Error : In the function Det, size is different from row and column. [calc_objects.cpp " << __LINE__ << "]\n" ;
        return -1 ;
    }else if (v.cell.size() == 1)
    {
        return v.cell[0][0] ;
    }

    return cofex(v) ;
}

int Matrix::Optimize(){
    //get matrix width and length once more.
    length_row = cell.size() ;
    length_column = cell[length_row - 1].size() ;

    //symmetry shaping
    int integ = 0 ; //for checking symmetric
    if (sym_flag == 0)
    {
        for (int i = 0; i < cell.size() ; i++)
        {
            for (int j = i; j < cell[0].size() ; j++)
            {
                if (cell[i][j] != cell[j][i])
                {
                    break ;
                    integ = 1 ;
                }
            }
            if (integ == 1)
            {
                break ;
            }
        }
    }
    if (integ == 0)
    {
        length_row = this->cell.size() ;
        length_column = this->cell[0].size() ;
        vector< vector<double> > v,w ;
        v = this->cell ;
        for (int i = 0; i < length_row; i++)
        {
            vector< double > data_line ;
            for (int j = 0; j < i; j++)
            {
                data_line.push_back(v[i][j]) ;
            }
            w.push_back(data_line) ;
        }
        this-> cell = w ;
    }
    return 0 ;
}


Matrix Matrix::operator+(const Matrix& x){
    Matrix v ;
    if (cell.size()!=x.cell.size() || cell[0].size()!=x.cell[0].size())
    {
        cout << "Error : when the + calculation, matrix addition failed. [calc_objects.cpp " << __LINE__ << "]\n" ;
        return v ;
    }
    v.Reserve(cell.size(),cell[0].size()) ;
    for (int i = 0; i < cell.size(); i++)
    {
        for (int j = 0; j < cell[0].size(); j++)
        {
            v.cell[i][j]=cell[i][j] + x.cell[i][j] ;
        }
    }
    v.length_row = length_row ;
    v.length_column = length_column ;
    return v ;
}

Matrix Matrix::operator-(const Matrix& x){
     Matrix v ;
    if (cell.size()!=x.cell.size() || cell[0].size()!=x.cell[0].size())
    {
        cout << "Error : Matrix subtraction failed. [calc_objects.cpp " << __LINE__ << "]\n" ;
        return v ;
    }
    v.Reserve(cell.size(),cell[0].size()) ;
    for (int i = 0; i < cell.size(); i++)
    {
        for (int j = 0; j < cell[0].size(); j++)
        {
            v.cell[i][j]=cell[i][j] - x.cell[i][j] ;
        }
    }
    v.length_row = length_row ;
    v.length_column = length_column ;
    return v ;
}

Matrix Matrix::operator*(const Matrix& x){
    Matrix v ;
    vector<double> data_line ; //a row
    double c = 0 ; //temp cell data
    int l = 0, m = 0, n = 0 ; //calculate A*B. A (l by m matrix), B (m by n matrix)

    l = length_row ;
    m = length_column ;
    n = x.length_column ;

    if (m != x.length_row)
    {
        cout << "Error : Matrix multiplication failed. [matrix.cpp : " << __LINE__ << "]\n" ;
        return v ;
    }
    for (int i = 0; i < l ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m ; k++)
            {
                c += cell[i][k]*x.cell[k][j] ;
            }
            data_line.push_back(c) ;
            c = 0 ;
        }
        v.cell.push_back(data_line) ;
        data_line.clear() ;
    }
    v.length_row = l ;
    v.length_column = n ;
    return v ;
}

Matrix Matrix::operator|(const Matrix& x) {
    Matrix v ;
    int l = 0, m = 0 ; //number of lines, this and x

    v = *this ; //v as this

    l = length_row ;
    m = x.length_row ;

    if (l != m)
    {
        cout << "Warnning : The number of rows is different from 2 matrixes. Continue? [matrix.cpp " << __LINE__ << "]\n" ;
        return v ;
    }
    for (int i = 0; i < l ; i++)
    {
        for (int j = 0; j < x.length_column; j++)
        {
            v[i].push_back(x.cell[i][j]) ;
        }
    }
    v.length_column = this->length_column + x.length_column ;
    return v ;
}

double& Matrix::operator()(int i,int j){
    if (sym_flag == 1 && i < j)
    {
        return cell[j][i] ;
    }
    return cell[i][j] ;
}

vector< double >& Matrix::operator[](int i){
    return cell[i] ;
}

//function of cofactor expansion
double cofex(const Matrix v){
    int lens = v.length_row ;
    if (lens == 2)
    {
        return v.cell[0][0]* v.cell[1][1] -v.cell[0][1]*v.cell[1][0] ;
    }else if(lens > 2)
    {
        double r = 0 ;
        for (int i = 0; i < lens; i++) //i means index of the matrix v column
        {
            Matrix x ; //cofactor expansion matrix
            x.cell.reserve(lens-1) ; //define size (attention! this uses reserve function in std:: not Reserve as defined by me)
            for (int j = 1; j < lens; j++)
            {
                vector< double > line ;
                for (int k = 0; k < lens; k++)
                {
                    if (i != k)
                    {
                        line.push_back(v.cell[j][k]) ;
                    }
                }
                x.cell.push_back(line) ;
            }
            r += pow(-1,i)*v.cell[0][i]*cofex(x) ;
        }
        return r ;
    }
    return -1;
}
