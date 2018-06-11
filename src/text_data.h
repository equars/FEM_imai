//=============================
//set texts use in FEM program
//=============================

#ifndef TEXD_H
#define TEXD_H

#include <iostream>
#include <string>

using namespace std ;

string text_start = "\
This is the FEM Program made by IMAI. ver.1.0   \n\
\n" ;
string text_help = "\
This is the finit element method program.\n\
Usage : ./FEM [Option] [Filename]\n\
        [Option] : option\n\
        [Filename] : filename\n\
\n\
Option : -h         -> show help.\n\
         filename -> read script file.\n\
\n\
prompt mode if with no option.\n\
            \n" ;

#endif