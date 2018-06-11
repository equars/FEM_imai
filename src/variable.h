//================================
//define variable object
//================================

#ifndef VAR_H
#define VAR_H

#include <iostream>
#include <vector>
#include <string>

using namespace std ;

class Variable{
    public:
        //data elements
        string name ; //the name of variable
        string value ; //value

        //methods
};

class Vars{
    public:
        //data elements
        vector< Variable > elem ;

        //moethods
        //U get(string name) ; //find var and return the content of it

        //overload
        string operator[](string name){
            for (int i = 0; i < elem.size(); i++)
            {
                if (elem[i].name == name)
                {
                    return elem[i].value ;
                }
            }
            return "" ;
        } ; //find var and return the content of it
};

#endif
