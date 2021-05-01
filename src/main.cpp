//============================================================================
//    FEM by IMAI
//    This is the finit element method program.
//    main.cpp : Executable file. initialize, read script, control program.
//    Actually main.cpp is compiled to FEM.exe.
//============================================================================
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

//----includes----
#include "matrix.h"
#include "text_data.h"
#include "core.h"
#include "util.h"
#include "variable.h"
#include "material.h"
#include "solve.h"

using namespace std ;

//----function prototype----
static int readscript(string filename = "0", string order = "0");

//----global value----
//    ----utility value----
int script_flag = 0 ; //scriptmode flag. 1 as script mode, 0 as terminalmode
int commandstate_flag = 0 ; //command flag 0 as normal, non 0 as error.
string message ; //command message (output message)
Vars vars_str ;
//    ----for solve, using for calculation----
Material obj ;
double elastic_constant = -1 ;
double poisson_ratio = 0 ;

//----main----
int main(int argc, char* argv[]){
    //----define value----
    string script_name;


    //----process when starts this.----
    if (argc==1)
    {
        cout << text_start ;
        readscript();
    }else if(argc==2)
    {
        if (strcmp(argv[1], "-h") == 0)
        {
            cout << text_help ;
            return 0 ;
        }else
        {
            script_name = string(argv[1]) ;
            readscript(script_name) ;
        }
    }
}


//the function that read scripts and then start programs as the script.
int readscript(string filename, string order){
    //----define value----
    char script_line_c[31] ;
    string script_line ;
    string str ; //get line from script file
    vector<string> script_line_splited ;
    int commandargnum = 0 ; //number of command argment.
    int end_flag = 0 ; //break whilei
    string errc ;

    //----terminal(prompt) mode---
    if (filename == "0")
    {
        while(end_flag == 0){
            commandstate_flag = 0 ;
            message = "" ;
            if (order == "0")
            {
                cout << "FEM> " ;
                errc = fgets(script_line_c, sizeof(script_line_c), stdin) ;
                script_line_c[strlen(script_line_c)-1] = '\0' ;
                script_line = string(script_line_c) ; //convert char to string
            }else
            {
                script_line = order ;
                end_flag = 1 ;
            }

            if (script_line != "")
            {
                //----Main process zone start !----
                //----more than 1 words in a terminal line----
                script_line_splited = data_split(script_line, ' ') ;
                commandargnum = script_line_splited.size() ;
                if (commandargnum > 0) {
                    if (script_line_splited[0] == "load") //----below this, write command name and its process and error or output message in each "if"----
                    {
                        if (commandargnum == 2)
                        {
                            readscript(script_line_splited[1],"0") ;
                            break ;
                        }else
                        {
                            commandstate_flag = __LINE__ ;
                            message = "Error : in command 'load'. command with an arguments(file name)?" ;
                        }
                    }if (script_line_splited[0] == "set")
                    {
                        if (commandargnum >= 3)
                        {
                            if (script_line_splited[1] == "variable")
                            {
                                Variable var ;
                                var.name = script_line_splited[2] ;
                                if (commandargnum == 4)
                                {
                                    var.value = script_line_splited[3] ;
                                }
                                vars_str.elem.push_back(var) ;
                            }
                        }

                    }else if (script_line_splited[0] == "unit") //to define unit set.
                    {
                        if (commandargnum == 2)
                        {
                            if (script_line_splited[1] == "metal") //L:[m] T:[s] M:[kg] elastic_constant:[GPa]
                            {
                                obj.unit = 0 ;
                            }
                        }else
                        {
                            commandstate_flag = __LINE__ ;
                            message = "Error : you should set parameter of unit command." ;
                        }
                    }else if (script_line_splited[0] == "mp") //to define material parameter
                    {
                        if (commandargnum == 4)
                        {
                            if (script_line_splited[1] == "elastic_constant")
                            {
                                elastic_constant = stringtodouble(script_line_splited[3]) ;
                            }else if (script_line_splited[1] == "poisson_ratio")
                            {
                                poisson_ratio = stringtodouble(script_line_splited[3]) ;
                            }else if (script_line_splited[1] == "thickness") {
                                obj.t = stringtodouble(script_line_splited[3]) ;
                            }

                            if (elastic_constant != -1 && poisson_ratio != 0)
                            {
                                getDmatrix(obj, 2, elastic_constant, poisson_ratio) ;
                            }
                        }
                    }else if (script_line_splited[0] == "read")
                    {
                        if (commandargnum == 3)
                        {
                            if (script_line_splited[1] == "node")
                            {
                                int stat ;
                                stat = read_node(obj, script_line_splited[2]) ;
                                if (stat == 0)
                                {
                                    message = "All nodes are normally read." ;
                                }else if(stat == -1){
                                    commandstate_flag = __LINE__ ;
                                    message = "Error : could not open " + script_line_splited[2] + "." ;
                                }else
                                {
                                    commandstate_flag = __LINE__ ;
                                    message = "Error : Some abnormality is on line " + inttostring(stat) + " in " + script_line_splited[2] + "." ;
                                }
                            }if (script_line_splited[1] == "element")
                            {
                                int stat ;
                                stat = read_elem(obj, script_line_splited[2]) ;
                                if (stat == 0)
                                {
                                    message = "All elements are normally read." ;
                                }else if(stat == -1){
                                    commandstate_flag = __LINE__ ;
                                    message = "Error : could not open " + script_line_splited[2] + "." ;
                                }else
                                {
                                    commandstate_flag = __LINE__ ;
                                    message = "Error : Some abnormality is on line " + inttostring(stat) + " in " + script_line_splited[2] + "." ;
                                }
                            }
                        }else
                        {
                            commandstate_flag = __LINE__ ;
                            message = "Error : Could not read data file." ;
                        }

                    }else if (script_line_splited[0] == "fix") {
                        if (commandargnum == 3) {
                            if (script_line_splited[2] == "pa") {
                                obj.fixx.push_back( stringtoint(script_line_splited[1]) ) ;
                                obj.fixy.push_back( stringtoint(script_line_splited[1]) ) ;
                            }else if (script_line_splited[2] == "px") {
                                obj.fixx.push_back( stringtoint(script_line_splited[1]) ) ;
                            }else if (script_line_splited[2] == "py") {
                                obj.fixy.push_back( stringtoint(script_line_splited[1]) ) ;
                            }
                        }
                    }else if (script_line_splited[0] == "force")
                    {
                        if (commandargnum == 5) {
                            if (script_line_splited[1] == "node") {
                                int nodenum = stringtoint(script_line_splited[2]) ;
                                int rownum = -1 ;

                                if (script_line_splited[3] == "x") {
                                    rownum = 0 ;
                                }else if (script_line_splited[3] == "y") {
                                    rownum = 1 ;
                                }else if(script_line_splited[3] == "z") {
                                    rownum = 2 ;
                                }else{
                                    commandstate_flag = __LINE__ ;
                                    message = "Error : You may miss set about force." ;
                                }

                                double force = stringtodouble(script_line_splited[4]) ;

                                obj.force[(nodenum-1)*dim+rownum] = force ;
                            }
                        }else{
                            commandstate_flag = __LINE__ ;
                            message = "Error : You may miss set about force." ;
                        }
                    }else if (script_line_splited[0] == "solve")
                    {
                        solve(obj,dim) ;
                    }else if (script_line_splited[0] == "write")
                    {
                        if (commandargnum == 3)
                        {
                            if (script_line_splited[1] == "node")
                            {
                                /*
                                ifstream ifs_dat(script_line_splited[2].c_str()) ;
                                if (ifs_dat.fail())
                                {
                                    cerr << "Error : Could not read file. [main.cpp  "<< __LINE__ << "] \n" ;
                                }
                                while(getline(ifs_dat, str))
                                {

                                }
                                */
                                cout << "node" ;
                            }
                        }else
                        {
                            commandstate_flag = __LINE__ ;
                            message = "Error : Could not write." ;
                        }
                    }else if(script_line_splited[0] == "dump")
                    {
                        int state = 0 ;
                        if (commandargnum == 3)
                        {
                            if (script_line_splited[1] == "material")
                            {
                                state = dump(obj, script_line_splited[2]) ;
                            }
                        }
                    }else if(script_line_splited[0] == "export")
                    {
                        int state = 0 ;
                        if(commandargnum == 3){
                            if (script_line_splited[1] == "vtk"){
                                state = export_vtk(obj, script_line_splited[2]) ;
                            }
                        }else{
                            commandstate_flag = __LINE__ ;
                            message = "Error : Command line error." ;
                        }
                    }else if(script_line_splited[0][0] == '$')
                    {
                        script_line_splited[0].erase(script_line_splited[0].begin(),script_line_splited[0].begin()+1) ;
                        script_line_splited[0].pop_back() ;
                        vector<string> eq = split(str, '=') ;
                        if (eq.size() == 2)
                        {
                            vars_str[ script_line_splited[0] ] = doubletostring( evalu(eq[1], vars_str)) ;
                        }
                    }else if (script_line_splited[0][0] == '/')
                    {
                        //check integrity commands
                        if (commandargnum == 1)
                        {
                            if (script_line_splited[0] == "/SOLU") //use before solve
                            {
                                cout << "maybe ok...(under construction.)\n" ;
                            }else if (script_line_splited[0] == "/PRE") //use before preprocessor
                            {
                                cout << "maybe ok...(under construction.)\n" ;
                            }else if (script_line_splited[0] == "/POS") //use before postprocessor
                            {
                                cout << "maybe ok...(under construction.)\n" ;
                            }else
                            {
                                commandstate_flag = __LINE__ ;
                                message = "Error : No such check command " + script_line_splited[0] + "." ;
                            }
                        }
                    }else if (script_line == "quit" || script_line == "exit")
                    {
                        cout << "Program will be terminated normally.\n" ;
                        end_flag = 1 ;

                    }else
                    {
                        commandstate_flag = __LINE__ ;
                        message = "Error : No such command '" + script_line_splited[0] + "'" ;
                    }
                }
            }
            if (script_flag != 1 && end_flag != 1)
            {
                if (commandstate_flag != 0)
                {
                    cout << message << " [main.cpp : " << commandstate_flag << " ]\n" ;
                }else if(message != "")
                {
                    cout << message << "\n" ;
                }
            }
        }
        return 0 ;
    }
    //----read script from file mode----
    else{
        script_flag = 1 ;
        int script_line_num = 0 ;
        ifstream ifs(filename.c_str()) ;
        if (ifs.fail())
        {
            cerr << "Error : Could not read file. [main.cpp  " << __LINE__ << "]\n" ;
            return -1 ;
        }

        while (getline(ifs, str))
        {
            int comment_flag = -1 ;
            int variable_flag = -1 ;
            script_line_num += 1 ;
            comment_flag = str.find("!") ;
            //variable_flag = str.find("$") ;
            if (comment_flag >= 0)
            {
                str.erase(str.begin()+comment_flag, str.end() ) ; //erace the part of comment
            }
            /*string::size_type pos = str.find("$") ; //substitution value to the variable
            while(pos > 1){
                int namesize = str.find(")", pos) - pos - 2 ;
                string var_name = str.substr(pos+2,namesize) ;
                if (vars_str[var_name] == "")
                {
                    cerr << "Error : " << var_name << "is undefined variable. [script line : " << script_line_num << " ]\n" ;
                }
                str.replace(pos, namesize+3, vars_str[var_name]) ;
                pos = str.find("$", pos + var_name.size()) ;
            }*/
            readscript("0", str) ;
            if (commandstate_flag != 0)
            {
                cerr << message << "[script line : " << script_line_num << " ] [main.cpp : " << commandstate_flag << " ]\n" ;
                break ;
            }else if(message != "")
            {
                cout << message << "\n" ;
            }
        }
        return 0 ;
    }
}
