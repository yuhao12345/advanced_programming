# HW3

Yuhao Kang


gcc -Wall -ansi -pedantic -o bh Barnes-Hut.c -lm

./bh

100 particles are randomly generated in 2D space and stored into QuadTree.
printTree function can list each node in the quadTree.


To test the correctness, consider the circular motion of two particles, when the centrifugal force is balanced by the gravity, two particles can rotate relative to their center.

By judicously choose the initial position and velocity, below shows the motion of two particles for 5000 iterations.

![trajectory_circle](https://user-images.githubusercontent.com/31739574/97132314-826e8d00-1714-11eb-9a6d-570b325563f1.jpg)


Here is a more generalized result for 100 random particles after 200 iterations:

![trajectory_100particles](https://user-images.githubusercontent.com/31739574/97504911-e2984580-1945-11eb-8bc7-1a792ee0e740.jpg)


Another correctness checking: Momentum conservation for these 100 particles. 

The initial total momentum in x direction is 49.284451. The final total momentum in x direction is 49.223984.  The percent difference is -0.123 %.


One shortcoming of this code is that the square boundary is fixed from (-10 -10) to (10 10), any particles moving outside of this boundary will not be considered. Thus, the number of iteration cannot be too large, otherwise most of particles may leave this boundary. A possible approach may be changing the boundary dynamically based on the spatial distribution of these particles after every 500 iterations. 

Running time: for one iteration, the relation between # of particles and elapsed time(s):
 
100,     0.00127s            

1000,    0.0197s      
 
10000,    0.254s
 
100000,   5.84s

When the number of particles increases 10 times, the time cost will increase 10-20 times, which is much smaller than 100. This is consistent with the argument that cost~O(nlgn).
