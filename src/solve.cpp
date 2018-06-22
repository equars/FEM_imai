//===============================
//The function of solve
//===============================

#include <iostream>
#include <vector>

#include "core.h"
#include "material.h"
#include "solve.h"

int solve(Material &obj, int dim){
    Matrix B,Km,Bt ; //B, K matrix.
    int elem_num = obj.elements.size() ; //the number of elements
    int elem_type = obj.elements[0].size() ; //3 as triangle, 4 as square
    int node_num = obj.nodes.size() ; //the number of nodes

    obj.K.Reserve(dim*node_num,dim*node_num) ; //reserve K matrix

    if (elem_type == 3 && dim == 2) //triangle nodes(plane)
    {
        for (int i = 0; i < elem_num; i++)
        {
            //make B and K matrix for each elements(init)
            B.Reserve(elem_type,dim*elem_type) ;
            double x1,y1,x2,y2,x3,y3 ; //get coordination of elements
            x1 = obj.nodes[ obj.elements[i][0] ].coord[0] ;
            y1 = obj.nodes[ obj.elements[i][0] ].coord[1] ;
            x2 = obj.nodes[ obj.elements[i][1] ].coord[0] ;
            y2 = obj.nodes[ obj.elements[i][1] ].coord[1] ;
            x3 = obj.nodes[ obj.elements[i][2] ].coord[0] ;
            x3 = obj.nodes[ obj.elements[i][2] ].coord[1] ;

            //determinant of A
            double deta = x2*y3+x1*y2+x3*y1 - (x1*y3+x2*y1+x3*y2) ;

            //make B matrix
            B[0][0]= (y2-y3)/deta ;
            B[0][2]= (y3-y1)/deta ;
            B[0][4]= (y1-y2)/deta ;
            B[1][1]= (x3-x2)/deta ;
            B[1][3]= (x1-x3)/deta ;
            B[1][5]= (x2-x1)/deta ;
            B[2][0]= (x3-x2)/deta ;
            B[2][1]= (y2-y3)/deta ;
            B[2][2]= (x1-x3)/deta ;
            B[2][3]= (y3-y1)/deta ;
            B[2][4]= (x2-x1)/deta ;
            B[2][5]= (y1-y2)/deta ;

            //B^T *D*B *thickness * detA /2
            Bt = B ;
            Bt.Transpose() ;
            Km = Bt * obj.D ;
            Km = Km * B ;
            for (int j = 0; j < Km.length_row ; j++)
            {
                for (int k = 0; k < obj.K.length_column; k++)
                {
                    Km[j][k] = Km[j][k]*obj.t*deta/2 ;
                }
            }

            //merge K_m matrix to K(not yet)
            merge_Kmatrix(obj.K, Km) ;
            //merge K_m to K(test version) (delete if maerge_Kmatrix is deploy)
            
        }
        //boundary conditions
        for (int i = 0; i < obj.K[0].size(); i++) {

        }

        //solve
        obj.K.Inverse() ;
        for (int i = 0; i < obj.K[0].size(); i++) {
            for (int j = 0; j < obj.K[0].size(); j++) {
                double kval = obj.K[i][j] ;
                obj.u[i] += kval * obj.force[j] ;
            }
        }
    }
    return 0 ;
}
