#!/bin/bash

g++ make_plate.cpp 
echo "Number of elements = 164" > d_plate_elem.dat
./a.out elem >> d_plate_elem.dat
echo "Number of nodes = 104" > d_plate_node.dat
./a.out node >> d_plate_node.dat
