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
            if (commandargnum >= 5 && script_line_splited[0] == "Number" && script_line_splited[1] == "of" && script_line_splited[2] == "nodes")
            {
                int node_len = stringtoint(script_line_splited[4]) ;

                //allocate arrays.
                obj.nodes.reserve(node_len+1) ;
                obj.force.reserve(node_len*dim) ;
                obj.u.reserve(node_len*dim) ;
                obj.K.Reserve(node_len*dim, node_len*dim) ;
                for (int i = 0; i < node_len+1; i++)
                {
                    Node n ;
                    obj.nodes.push_back(n) ;
                    if(i != node_len){
                        for (int i = 0; i < dim; i++) {
                            obj.force.push_back(0) ;
                            obj.u.push_back(0) ;
                        }
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
    ifstream ifs_elem(filename.c_str()) ;
    if (ifs_elem.fail())
    {
        return -1 ;
    }

    while (getline(ifs_elem, str))
    {
        //----define value----
        int comment_flag = -1 ;
        vector<string> script_line_splited ;
        int dataargnum = 0 ;

        script_line_num += 1 ;
        comment_flag = str.find("!") ;
        if (comment_flag >= 0)
        {
            str.erase(str.begin()+comment_flag, str.end() ) ;
        }
        if (str != "")
        {
            script_line_splited = data_split(str,' ') ;
            dataargnum = script_line_splited.size() ;
            if (dataargnum >= 5 && script_line_splited[0] == "Number" && script_line_splited[1] == "of" && script_line_splited[2] == "elements")
            {
                int elem_len = stringtoint(script_line_splited[4]) ;
                obj.elements.reserve(elem_len) ;
                vector<int> init;
                init.push_back(0) ;
                for (int i = 0; i < elem_len+1; i++)
                {
                    obj.elements.push_back(init) ;
                }
            }else if(dataargnum > 2)
            {
                int index = stringtoint(script_line_splited[0]) ;
                for (int i = 0; i < dataargnum-1; i++)
                {
                    if (i==0) {
                        obj.elements[index][0]=stringtoint(script_line_splited[i+1]) ;
                    }else{
                        obj.elements[index].push_back(stringtoint(script_line_splited[i+1])) ;
                    }
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
        cout << "dump data of D matrix ->\n" ;
        obj.D.Show() ;
        cout << "dump data of nodes ->\nnode num, [coordinations]\n" ;
        for (int i = 0; i < obj.nodes.size(); i++) {
            cout << i << " " ;
            for (int j = 0; j < dim; j++) {
                cout << obj.nodes[i].coord[j] << " " ;
            }
            cout << "\n" ;
        }

        cout << "\n" ;
        cout << "dump data of elements ->\nelement num, [nodes]\n" ;
        for (int i = 0; i < obj.elements.size(); i++) {
            cout << i << " " ;
            for (int j = 0; j < obj.elements[1].size(); j++) {
                cout << obj.elements[i][j] << " " ;
            }
            cout << "\n" ;
        }

        cout << "\n" ;
        cout << "dump data of displacement ->\n" ;
        for (int i = 0; i < obj.u.size(); i++) {
            cout << obj.u[i] << ", " ;
        }
        cout << "\n" ;

        cout << "\n" ;
        cout << "dump data of strain ->\n" ;
        for (int i = 0; i < obj.strain_dist.size(); i++) {
            cout << i+1 << " : " ;
            for (int j = 0; j < (dim-1)*3 ; j++) {
                std::cout << obj.strain_dist[i][j][0] << ',';
            }
            cout << "\n" ;
        }
        cout << "\n" ;

        cout << "\n" ;
        cout << "dump data of stress ->\n" ;
        for (int i = 0; i < obj.stress_dist.size(); i++) {
            cout << i+1 << " : " ;
            for (int j = 0; j < (dim-1)*3 ; j++) {
                std::cout << obj.stress_dist[i][j][0] << ',';
            }
            cout << "\n" ;
        }
        cout << "\n" ;
    }
    return -1;
}

int export_vtk(Material &obj, string filename){
    int nodes_len = obj.nodes.size();
    int node_len = 2; //as dimension.
    int elems_len = obj.elements.size();
    int elem_len = obj.elements[1].size();
    double mises ;
    ofstream outputfile(filename);
    outputfile<<"# vtk DataFile Version 4.1\nFEM_imai output vtk.\n";
    outputfile<<"ASCII\nDATASET UNSTRUCTURED_GRID\n\n";

    //write nodes
    outputfile<<"POINTS "<<nodes_len-1<<" float\n";
    for (int i = 1; i<nodes_len;i++){
        for (int j = 0; j<node_len;j++){
            outputfile<<fixed << setprecision(8)<<obj.nodes[i].coord[j]<<" ";
        }
        outputfile<<"0.0\n";
    }

    //write elems
    outputfile<<"\nCELLS "<<elems_len-1<<" " ;
    if (elem_len==3){ //2d3n elements
        outputfile<<(elems_len-1)*(elem_len+1)<<"\n" ;
        for (int i = 1; i<elems_len;i++){
            outputfile<<elem_len<<" " ;
            outputfile<<obj.elements[i][0]-1<<" " ;
            outputfile<<obj.elements[i][1]-1<<" " ;
            outputfile<<obj.elements[i][2]-1<<"\n" ;
        }
    }
    outputfile<<"\nCELL_TYPES "<<elems_len-1<<"\n" ;
    if (elem_len==3){ //2d3n elements
        for (int i = 1; i<elems_len;i++){
            outputfile<<"5\n" ;
        }
    }

    //write stress
    outputfile<<"\nCELL_DATA "<< elems_len-1<<"\n";
    outputfile<<"SCALARS Element_Mises float\nLOOKUP_TABLE default\n";
    for(int i=0;i<elems_len-1;i++){
        mises = pow(obj.stress_dist[i][0][0],2.0)+pow(obj.stress_dist[i][1][1],2.0);
        mises = mises + pow(obj.stress_dist[i][0][0]-obj.stress_dist[i][1][1],2.0);
        mises = sqrt(mises);
        outputfile<<mises<<"\n";
    }
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
