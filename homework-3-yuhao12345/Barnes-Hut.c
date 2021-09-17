#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "random_particle.h"

void ran_init(float *data, int n);
/* calculate all interparticle forces and update instantaneous velocities */
void calc_force(Particle *p, float dt, int n) {
    int i;
    float totalforce[2];
    qNode *nd=malloc(sizeof(qNode));   /*empty root*/
    qNode *temp;   /*the temp pointer to the last generate node after each insertion*/

    initializeNode(nd);
    /*printf("nd's half size %f\n",nd->half_side);*/
    qNode *root=nd;

    for (i = 0; i < n; i++) {     /* build tree*/
        /*printf("add %d th particle\n",i);*/
        if (abs(p[i].x)<10 && abs(p[i].y)<10){
            temp=insert(nd,NULL,NULL,&p[i]);
/*        printf("root count %d   ",root->count);
        printf("temp count %d\n",temp->count);*/
            updateParameter(temp);
/*        printf("after:  root count %d   ",root->count);
        printf("temp count %d\n",temp->count);*/
            /*printf("temp go back to root %d\n",temp==root);*/
        }
    }
    /*printTree(root);*/

    /*printf("%d\n",root->child[3]->count);*/
    for (i=0; i<n; i++){
/*        printf("a\n");
        printf("%d\n",nd->count);*/
        treeForce(&p[i],root,totalforce);
        /*printf("totalforce to i node %f\n",totalforce[0]);*/
        /* update instantaneous velocity based on force and timestep */
        p[i].vx += dt*totalforce[0]; p[i].vy += dt*totalforce[1];
    }
    free_Tree(root);
}

int main(const int argc, const char** argv) {
    FILE *datafile    = NULL;      /* output file for particle positions */
    int   nParticles  = 100000;      /* number of particles */
    int i,iter;
    const float dt    = 0.01f; /* time step   */
    const int nIters  = 1;   /* number of steps in simulation */

    float *buf        =  malloc(nParticles*sizeof(Particle));
    Particle  *p          = (Particle *) buf;

    ran_init(buf, 4*nParticles);

    float ini_momentum_x=0;
    for (i=0;i<nParticles;i++)
        ini_momentum_x+=p[i].vx;

/*    Particle *p=malloc(nParticles*sizeof(Particle));
    p[0].x=5; p[0].y=0; p[0].vx=0; p[0].vy=1/sqrt(20.0);
    p[1].x=-5; p[1].y=0; p[1].vx=0; p[1].vy=-1/sqrt(20.0);*/
    /*p[2].x=-0.7; p[2].y=-0.7; p[2].vx=0; p[2].vy=0;*//*
    double totalTime  = 0.0;*/

    datafile          = fopen("particles.dat","w");
    fprintf(datafile,"%d %d\n", nParticles, nIters);

    StartTimer();
    for (iter = 1; iter <= nIters; iter++) {
        printf("iteration:%d\n", iter);

        for (i = 0;i < nParticles; ++i)
            fprintf(datafile, "%f %f \n", p[i].x, p[i].y);



        calc_force(p, dt, nParticles);           /* compute interparticle forces and update vel */

        for (i = 0 ; i < nParticles; i++) {  /* compute new position */
            p[i].x += p[i].vx*dt;
            p[i].y += p[i].vy*dt;
        }

/*        const double tElapsed = GetTimer() / 1000.0;
        if (iter > 1) {                          *//* First iter is warm up *//*
            totalTime += tElapsed;
        }*/
    }

    fclose(datafile);
/*    double avgTime = totalTime / (double)(nIters-1);

    printf("avgTime: %f   totTime: %f \n", avgTime, totalTime);*/
    const double tElapsed = GetTimer() / 1000.0;
    printf("cost %f s\n",tElapsed);

    float final_momentum_x=0;
    for (i=0;i<nParticles;i++)
        final_momentum_x+=p[i].vx;

    printf("The initial momentum in x direction is %f\n The final momentum in x direction is %f\n The percent difference is %2.3f %%\n",\
           ini_momentum_x,final_momentum_x, (final_momentum_x-ini_momentum_x)/ini_momentum_x*100);
    free(buf);
}


/* randomly initialize particle positions and momenta */
void ran_init(float *data, int n) {
    int i;
    for (i = 0; i < n; i++) {
        data[i] = (2.0f * (rand() / (float)RAND_MAX) - 1.0f)*5;
    }
}
