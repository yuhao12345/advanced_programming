#ifndef QuadTree
#define QuadTree


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "random_particle.h"

/*each node contains # of particles (sum_mass), coordinate of center of mass,
 the center and half side length of square, and 4 children*/
typedef struct qNode{
    float center_x;  /* center of square*/
    float center_y;
    float half_side;
    float mc_x;      /* mass center*/
    float mc_y;
    int count;   /*# of particles within this square*/
    struct qNode * child[4];
    struct qNode * parent;
} qNode;


float * position_of_child(qNode *nd,int i){
    /*return the center and half side length of i-th quadrant*/
    float half_side=nd->half_side;
    float center_x=nd->center_x;
    float center_y=nd->center_y;
    float geom[3];
    float x,y;
    if (i==1){
        x=center_x+half_side/2;
        y=center_y+half_side/2;
    }else if(i==2){
        x=center_x-half_side/2;
        y=center_y+half_side/2;
    }else if(i==3){
        x=center_x-half_side/2;
        y=center_y-half_side/2;
    }else{
        x=center_x+half_side/2;
        y=center_y-half_side/2;
    }
    geom[0]=x;
    geom[1]=y;
    geom[2]=half_side/2;
    return geom;
}

int belong_to_which_quadrant_xy(qNode *nd, float x, float y){   /* coordinate (x,y) belongs to which quadrant of node*/
    float diff_x,diff_y;
    diff_x=x-nd->center_x;
    diff_y=y-nd->center_y;
    if (diff_x>=0 && diff_y>0) return 1;   /*include positive y axis */
    if (diff_x<0 && diff_y>=0) return 2;
    if (diff_x<=0 && diff_y<0) return 3;
    return 4;
}

int belong_to_which_quadrant(qNode *nd, Particle *p){
    return belong_to_which_quadrant_xy(nd, p->x, p->y);
}



qNode* insert(qNode *nd,Particle *p){   /* return the finally generated node*/
    int i,j;
    float* geom;
    if (nd==NULL){    /* if nd is null, add the particle to nd*/
        nd=malloc(sizeof(qNode));
        nd->mc_x=p->x;
        nd->mc_y=p->y;
        nd->count=1;
        nd->half_side=1;
        nd->center_x=0;
        nd->center_y=0;
        return nd;
    }
    else if (nd->count==1){    /* nd is leaf, the new added one make the node has 4 children*/
        nd->child[0]=NULL; nd->child[1]=NULL; nd->child[2]=NULL; nd->child[3]=NULL;

        i=belong_to_which_quadrant_xy(nd, nd->mc_x, nd->mc_y);  /* the original particle belongs to i-th quandrant*/
        j=belong_to_which_quadrant(nd, p); /* new particle's quandrant*/

        geom=position_of_child(nd,i);     /* move original particle to i*/
        qNode *child_i, *child_j;
        child_i=malloc(sizeof(qNode));
        child_i->mc_x=nd->mc_x;
        child_i->mc_y=nd->mc_y;
        child_i->center_x=geom[0];
        child_i->center_y=geom[1];
        child_i->half_side=geom[2];
        child_i->count=1;
        child_i->parent=nd;
        nd->child[i-1]=child_i;
        if (i!=j){
            child_j=malloc(sizeof(qNode));   /* add new particle to j*/
            geom=position_of_child(nd,j);
            child_j->mc_x=p->x;
            child_j->mc_y=p->y;
            child_j->center_x=geom[0];
            child_j->center_y=geom[1];
            child_j->half_side=geom[2];
            child_j->count=1;
            child_i->parent=nd;
            nd->child[j-1]=child_j;
            return nd->child[j-1];
        }else{     /*i==j  two particles belong to the same children, this degenerate children still need split*/
            return insert(nd->child[i-1],p);
        }
    }
    else{         /*nd is not leaf*/
        j=belong_to_which_quadrant(nd, p);
        return insert(nd->child[j-1],p);
    }
}

void updateParameter(qNode *nd){    /* after insert a particle, update the parameter of the whole path until root*/
    int i;
    while (nd->parent!=NULL){
        float mc_x=0.0;
        float mc_y=0.0;
        int count=0;
        qNode* p=nd->parent;

        for (i=0;i<4;i++){
            if (p->child[i]!=NULL){
                count++;
                mc_x+=p->child[i]->mc_x;
                mc_y+=p->child[i]->mc_y;
            }
            mc_x/=count;
            mc_y/=count;
        }
        p->count=count;
        p->mc_x=mc_x;
        p->mc_y=mc_y;
        nd=p->parent;
    }
}


#endif