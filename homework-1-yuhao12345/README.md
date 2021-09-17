# Homework 1

Yuhao Kang  

gcc  -Wall -ansi -pedantic -o test  list.c test_list2.c -lm

./test




20000 points are generated in both doubly linked list and array.

Operation: Iterate every point and calculate the average distance of each point to all points.

10 tests are performed. 

For list, each test cost ~4s.

For array, each test cost ~3s.

In conclusion, array is faster than list for this operation. 
Compared with array, list is slower to retrive data in the i-th element since it needs go along to chain to find the element while array can access the data directly.




