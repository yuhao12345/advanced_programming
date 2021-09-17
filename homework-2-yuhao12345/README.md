The 1st loop of function "calc_force" is parallelized.

1. PThreads

gcc -pthread -o nbody_pt timer.c nbody_pt.c -I. -lm

./nbody_pt 3000 4


The 1st input is # of particles, 2nd input is # of threads. 

Fix the # of particles as 3000.

Realtion between the average time for each iteration and the number of threads:

average_time(s),		num_threads

0.1151,		1

0.0726,		2

0.0441,		4

0.0259,		8



2. OpenMP

gcc -fopenmp -o nbody_omp timer.c nbody_omp.c -I. -lm

./nbody_omp 3000 4


average_time(s),		num_threads

0.1156,		1

0.0723,		2

0.0433,		4
	
0.0265,		8

The performance between OpenMp and PThreads are similar, 
the average time of each iteration follows a inversion relation with number of threads.



