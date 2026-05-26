#!/bin/bash


for p in 1 2 4 8
do
    mpirun --oversubscribe -np $p ./matrix_mpi
done