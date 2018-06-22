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

class Material{
    public:
        //data
        vector< vector<int> > elements ; //elements. index implay node number. values mean node numbaers.
        vector<Node> nodes ; //nodes. index implay node number. and Node class values means coordinations.
        vector< double > u ; //henni
        vector< double > stress ; //stress
        Matrix D ; //Dmatrix
        Matrix K ; //Kmatrix
        vector< double > force ;
        double t ; //thickness of material
        vector< int > fixall ; //Condition of constraint
        vector< int > fixx ;
        vector< int > fixy ;
        vector< int > fixz ;

        //methods
        int Make_K() ; //Make K matrix

        //initialize constructor
        Material(){
            int s = (dim-1)*3 ;
            D.Reserve(s,s) ;
        } ;
};

class Node{
    public:
        //data
        double coord[dim] ; //coordination
};

#endif
