CC=gcc
CFLAGS=-I. -lm
DEPS = timer.h
OBJ = timer.o nbody.o 
OBJ_pt=timer.o nbody_pt.o
OBJ_pt2=timer.o nbody_pt2.o
OBJ_omp=timer.o nbody_omp.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

nbody: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

nbody_pt: $(OBJ_pt)
	$(CC) -pthread -o $@ $^ $(CFLAGS)

clean:
	\rm -f *.o nbody *~ *#
