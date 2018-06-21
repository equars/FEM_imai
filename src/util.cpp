//===============================
//utility functions
//===============================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "util.h"
#include "matrix.h"
#include "material.h"
#include "variable.h"

using namespace std ;

int read_node(Material &obj, string filename){
    //----define value----
    string str ; //get line from script file
    int script_line_num = 0 ; //line counter

    //----process----
    ifstream ifs2(filename.c_str()) ;
    if (ifs2.fail())
    {
        return -1 ;
    }

    while (getline(ifs2, str))
    {
        //----define value----
        int comment_flag = -1 ;
        vector<string> script_line_splited ;
        int commandargnum = 0 ;

        script_line_num += 1 ;
        comment_flag = str.find("!") ;
        if (comment_flag >= 0)
        {
            str.erase(str.begin()+comment_flag, str.end() ) ;
        }
        if (str != "")
        {
            script_line_splited = data_split(str,' ') ;
            commandargnum = script_line_splited.size() ;
            if (commandargnum >= 5 && script_line_splited[0] == "Number" && script_line_splited[1] == "of" && script_line_splited[2] == "Nodes")
            {
                int node_len = stringtoint(script_line_splited[4]) ;

                //allocate arrays.
                obj.nodes.reserve(node_len) ;
                obj.force.reserve(node_len*dim) ;
                obj.K.Reserve(node_len*dim, node_len*dim) ;
                for (int i = 0; i < node_len; i++)
                {
                    Node n ;
                    obj.nodes.push_back(n) ;
                    for (int i = 0; i < dim; i++) {
                        obj.force.push_back(0) ;
                    }
                }
            }else if(commandargnum > 2)
            {
                int index = stringtoint(script_line_splited[0]) ;
                for (int i = 0; i < commandargnum-1; i++)
                {
                    obj.nodes[index].coord[i] = stringtodouble(script_line_splited[i+1]) ;
                }
            }
        }
    }
    return 0 ;
}

int read_elem(Material &obj, string filename){
    //----define value----
    string str ; //get line from script file
    int script_line_num = 0 ; //line counter

    //----process----
    ifstream ifs2(filename.c_str()) ;
    if (ifs2.fail())
    {
        return -1 ;
    }

    while (getline(ifs2, str))
    {
        //----define value----
        int comment_flag = -1 ;
        vector<string> script_line_splited ;
        int commandargnum = 0 ;

        script_line_num += 1 ;
        comment_flag = str.find("!") ;
        if (comment_flag >= 0)
        {
            str.erase(str.begin()+comment_flag, str.end() ) ;
        }
        if (str != "")
        {
            script_line_splited = data_split(str,' ') ;
            commandargnum = script_line_splited.size() ;
            if (commandargnum >= 4 && script_line_splited[0] == "Number" && script_line_splited[1] == "of" && script_line_splited[2] == "elems")
            {
                int elem_len = stringtoint(script_line_splited[4]) ;
                obj.elements.reserve(elem_len) ;
                vector<int> init;
                init.push_back(0) ;
                for (int i = 0; i < elem_len; i++)
                {
                    obj.elements.push_back(init) ;
                }
            }else if(commandargnum > 2)
            {
                int index = stringtoint(script_line_splited[0]) ;
                for (int i = 0; i < commandargnum-1; i++)
                {
                    obj.elements[index][i]=stringtoint(script_line_splited[i+1]) ;
                }
            }
        }
    }
    return 0 ;
}

vector<string> split(const string &str, char sep){
    vector<string> v ;
    stringstream ss(str) ;
    string buffer ;
    while( getline(ss, buffer, sep) ) {
        v.push_back(buffer) ;
    }
    return v;
}

vector<string> data_split(const string &str,char sep){
    vector<string> splited1 ;
    splited1 = split(str,sep) ;

    for (int i = splited1.size()-1; i >=0; i--)
    {
        if (splited1[i]=="")
        {
            splited1.erase(splited1.begin() + i) ;
        }
    }
    return splited1 ;
}

double evalu(string &equ , Vars &vars){
    return 0 ;
}

int dump(Material &obj, string order){
    cout << "====DUMP ABOUT MATERIAL DATA.====\n" ;
    if (order == "all") {
        cout << "dump data of displacement ->\n" ;
        for (int i = 0; i < obj.u.size(); i++) {
            cout << obj.u[i] << ", " ;
        }
    }
    return -1;
}

int dump(string &obj, string filename){
    ofstream out(filename) ;
    out << "DUMP" ;
    return 0;
}

double stringtodouble(string str){
    double ret;
    stringstream ss;
    ss << str;
    ss >> ret;
    return ret;
}

int stringtoint(string str){
    int ret;
    stringstream ss;
    ss << str;
    ss >> ret;
    return ret;
}

string inttostring(int number){
  char *str ;
  sprintf(str, "%d", number);
  return str ;
}

string doubletostring(double number){
  char *str ;
  sprintf(str, "%lf", number);
  return str ;
}
