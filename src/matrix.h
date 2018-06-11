//================================
//define matrix object
//================================

#ifndef MATX_H
#define MATX_H

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

using namespace std ;

class Matrix{
    public:
        //data elements
        vector< vector<double> > cell ;
        int length_row ;
        int length_column ;

        //methods
        int Transpose() ; //Transpote this.転置
        int Inverse() ; //Inverse this.逆行列
        int Reserve(int size_row, int size_column) ; //make 0 Matrix whose size is size_row and size_column. you can also use it for initializing matrix. 指定されたサイズの零行列を作る.初期化にも使える．
        int Show() ; //display Matrix on terminal.データを表示させる
        int Lu(Matrix &L, Matrix &U) ; //LU decomposition. LU分解
        double Det() ; //The function returns determinant.
        int Optimize() ; //automatically check symmetry and reduce half.
        int size(int i) ; //return matrix size. 0 as row size and 1 as column size.

        //overload
        Matrix operator+(const Matrix& x) ;
        Matrix operator-(const Matrix& x) ;
        Matrix operator*(const Matrix& x) ; //define multiplication.
        Matrix operator|(const Matrix& x) ; //define combine Matrix(side with side)
        double& operator()(int i,int j) ; //reference by index i,j but deprecated. or use symmmetric マトリックスにかっこで添え字を二つ指定するだけで成分が参照できる．ただしエディタ上で行列オブジェクトが関数と認識されてわかりにくいので非推奨．ただし対称行列のメモリセーブ機能を用いる場合はこれを用いる．       
        vector< double >& operator[](int i) ; //matrix element can be derived by define index by [] operators.

        //initialize constructor
        Matrix(){
            sym_flag = 0 ;
        } ;
        //you can define matrix size on first definission. defined by ().
        Matrix(int i, int j){
            Matrix v ;
            v.Reserve(i,j) ;
            this->cell = v.cell ;
            sym_flag = 0 ;
        } ;

    private:
        //data elements
        int sym_flag ; //1 if this is symmetric matrix
};

#endif
