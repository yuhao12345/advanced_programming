# Homework 6



./m  filename <#threads>
```
gcc -fopenmp -o m main.c timer.c graph.c heap.c

./m graph1.txt 12
```

Results are shown in output_graph1.txt and output_graph2.txt


Performance anaysis based on cs linux machine:


For graph1.txt, 
```
1 core, 15 s.

12 cores, 1.87 s
```

For graph2.txt
```
1 core, 7150s  (~2h)

12 cores, 1048s (~17.5min)

```
