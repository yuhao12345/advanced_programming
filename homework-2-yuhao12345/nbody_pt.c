#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <pthread.h>

#define SOFTENING 1e-9f

/*pthread_mutex_t mutexsum;*/

typedef struct {
  float x, y, z;        /* particle positions */
  float vx, vy, vz;     /* particle momenta */
} Particle;

typedef struct param_{
    Particle *p;
    float dt;
    int nParticles;
    int start;   /*start point*/
    int nl;   /*local # of points precessed*/
} Params;

/* randomly initialize particle positions and momenta */
void ran_init(float *data, int n) {
  for (int i = 0; i < n; i++) {
    data[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
  }
}

/* calculate all interparticle forces and update instantaneous velocities */
void* calc_force(void *args) {
    Params *tp=(Params *)args;
    Particle *p=tp->p;
    float dt=tp->dt;
    int start=tp->start;
    int nl=tp->nl;
    int end=start+nl;

    for (int i = start; i < end; i++) {
        float Fx = 0.0f; float Fy = 0.0f; float Fz = 0.0f;

        for (int j = 0; j < tp->nParticles; j++) {
            /* calculate net particle for on i'th particle */
            float dx = p[j].x - p[i].x;
            float dy = p[j].y - p[i].y;
            float dz = p[j].z - p[i].z;
            float distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
            float invDist = 1.0f / sqrtf(distSqr);
            float invDist3 = invDist * invDist * invDist;

            Fx += dx * invDist3; Fy += dy * invDist3; Fz += dz * invDist3;

        }

        /* update instantaneous velocity based on force and timestep */
        /*pthread_mutex_lock (&mutexsum);*/
        p[i].vx += dt*Fx; p[i].vy += dt*Fy; p[i].vz += dt*Fz;

        /*pthread_mutex_unlock (&mutexsum);*/
    }
    return NULL;
}

int main(const int argc, const char** argv) {
    FILE *datafile    = NULL;      /* output file for particle positions */
    int i,tn;
    int   nParticles;      /* number of particles */
    int NT;  /*number of threads*/
    nParticles = atoi(argv[1]);
    NT  =   atoi(argv[2]);

    const float dt    = 0.01f; /* time step   */
    const int nIters  = 200;   /* number of steps in simulation */

    float *buf  =  malloc(nParticles*sizeof(Particle));
    Particle  *p          = (Particle *) buf;

    Params pa[NT];
    pthread_t threads[NT];

    ran_init(buf, 6*nParticles); /* Init pos and vel data */

    double totalTime  = 0.0;

    datafile = fopen("particles_pt.dat","w");
    fprintf(datafile,"%d %d %d\n", nParticles, nIters, 0);

    /* ------------------------------*/
    /*     MAIN LOOP                 */
    /* ------------------------------*/


    /*pthread_mutex_init(&mutexsum, NULL);*/
    for (int iter = 1; iter <= nIters; iter++) {
        printf("iteration:%d\n", iter);
        for (i = 0;i < nParticles; ++i)
            fprintf(datafile, "%f %f %f \n", p[i].x, p[i].y, p[i].z);


        StartTimer();
        for (tn=0;tn<NT;tn++){
            pa[tn].p=p;
            pa[tn].dt=dt;
            pa[tn].nl=nParticles/NT;
            pa[tn].start=tn*pa[tn].nl;
            pa[tn].nParticles=nParticles;
            pthread_create(&threads[tn],NULL,*calc_force,(void*)&pa[tn]);   /* compute interparticle forces and update vel */
        }

        /*void calc_force(Particle *p, float dt, int n) */
        for (tn=0;tn<NT;tn++){
            pthread_join(threads[tn],NULL);
        }


        for (i = 0 ; i < nParticles; i++) {  /* compute new position */
            p[i].x += p[i].vx*dt;
            p[i].y += p[i].vy*dt;
            p[i].z += p[i].vz*dt;
        }

        const double tElapsed = GetTimer() / 1000.0;
        if (iter > 1) {                          /* First iter is warm up */
            totalTime += tElapsed;
        }
    }

    fclose(datafile);
    double avgTime = totalTime / (double)(nIters-1);

    /*pthread_mutex_destroy(&mutexsum);*/

    printf("avgTime: %f   totTime: %f \n", avgTime, totalTime);
    free(buf);
    pthread_exit(NULL);
}
