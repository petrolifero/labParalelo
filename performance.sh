#!/bin/bash

#tenha certeza que o espaço de variaveis locais(a pilha)
#não esteja pequeno demais
ulimit -s unlimited 

echo Com MPI 
time mpirun -np 20 build/mainMPI
echo COm MPI e OpenMP
time mpirun -np 20 build/mainOpenMP_MPI
echo Com openMP 
time build/mainOpenMP

