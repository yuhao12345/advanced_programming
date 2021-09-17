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




# homework-2
Parallelize nbody.c for a multicore processor using two different
approaches: PThreads, and OpenMP. You can determine the type of
scheduling and all other aspects of the parallelization, but the basic
idea is to have each thread (processor core) compute some fraction of
the force calculation in parallel. Getting the correct answer is a key
part of getting credit for this assignment, so be sure that you
develop a good testing strategy early. Speedup is another key aspect
-- report on performance improvements as a function of core count for
each strategy. For ease of grading, submit just two source code files
-- nbody_pt.c and nbody_omp.c. The repo will be checked on Sunday
night at 6pm.  and final versions are due Tuesday at 6pm. You will not
get full credit unless you have a mostly working version by Sunday
night. For the OpenMP version, only small changes will be allowed
after Sunday night.