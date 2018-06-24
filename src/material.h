//=================================================
//the class is defined as the shape of the material
//=================================================

#ifndef MATER_H
#define MATER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdlib.h>

using namespace std ;

//define
const int dim = 2 ;//dimension

//function and class prototype
class Node ;
class Stress ;
class Strain ;

//main class
class Material{
    public:
        //data
        vector< vector<int> > elements ; //elements. index implay node number. values mean node numbaers.
        vector<Node> nodes ; //nodes. index implay node number. and Node class values means coordinations.
        vector< double > u ; //henni
        vector<Strain> strain_dist ; //stress. index as node num.
        vector<Stress> stress_dist ; //stress
        Matrix D ; //Dmatrix
        Matrix K ; //Kmatrix
        vector< double > force ;
        double t ; //thickness of material
        vector< int > fixx ;
        vector< int > fixy ;
        vector< int > fixz ;

        int unit ; //unit flag. 0 as metal

        //methods
        int Make_K() ; //Make K matrix

        //initialize constructor
        Material(){
            int s = (dim-1)*3 ;
            t=1 ; //default thickness
            D.Reserve(s,s) ;
            unit = 0 ;
        } ;
};

class Node{
    public:
        //data
        double coord[dim] ; //coordination
};

class Strain{
    public:
        //data
        double val[(dim-1)*3] ; //varepsilon xx,yy,xy(if 2D)

        //methods
        double& operator[](int i){
            return val[i] ;
        }
};

class Stress{
    public:
        //data
        double val[(dim-1)*3] ; //varepsilon xx,yy,xy(if 2D)

        //methods
        double& operator[](int i){
            return val[i] ;
        }
};

#endif
