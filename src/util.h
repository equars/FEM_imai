//===============================
//utility functions
//===============================

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "matrix.h"
#include "material.h"
#include "variable.h"

using namespace std ;

//----function prototype----
int read_node(Material &obj, string filename) ; //read node data from the file
int read_elem(Material &obj, string filename) ; //read element data from the file
vector<string> split(const string &str, char sep) ; //the function that splits words.
vector<string> data_split(const string &str,char sep) ; //the function that splits words and delete empty data.
double evalu(string &equ , Vars &vars) ; //evaluation of equation that is string type.
int dump(Material &obj, string order) ;
int export_vtk(Material &obj, string filename) ;
int vec_find_int(std::vector<int> vec, int number) ;
double stringtodouble(string str) ;
int stringtoint(string str) ;
string inttostring(int number) ;
string doubletostring(double number) ;
#endif
