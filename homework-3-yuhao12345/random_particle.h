#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SOFTENING 1e-9f
#define size_distance_ratio_threshold 0.1

typedef struct Particle{
    float x, y;        /* particle positions */
    float vx, vy;     /* particle momenta */
} Particle;

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



void force(Particle* p,qNode* nd,float* f){
    float dx = nd->mc_x-p->x;
    float dy = nd->mc_y-p->y;

    float distSqr = dx*dx + dy*dy + SOFTENING;
    float invDist = 1.0f / sqrt(distSqr);     /*sqrtf does not work*/
    float invDist3 = invDist * invDist * invDist;

    f[0]= nd->count * dx * invDist3; f[1]= nd->count * dy * invDist3;
    return;
}


float size_distance_ratio(Particle* p,qNode *nd){
    return nd->half_side/sqrt((nd->mc_x-p->x)*(nd->mc_x-p->x)+(nd->mc_y-p->y)*(nd->mc_y-p->y));
}

void treeForce(Particle* p,qNode *nd, float* totalForce){
    float f[2];   /* temp individual force */
    int i;
    /**/
    if (nd->count==1 && abs(nd->mc_x-p->x)<1e-6 && abs(nd->mc_y-p->y)<1e-6){     /* the node is particle itself*/
        totalForce[0]=0.0f;
        totalForce[1]=0.0f;
        /*printf("meet self\n");*/
        return;
    }
    else if (nd->count==1 || size_distance_ratio(p,nd)<size_distance_ratio_threshold){
        force(p,nd,totalForce);
        /*printf(" individual force %5.4f   ", totalForce[0]);*/
        /*if (size_distance_ratio(p,nd)<size_distance_ratio_threshold)
            printf("cluster %d\n",nd->count);*/

        return;
    }
    else{
        totalForce[0] = 0.0f;
        totalForce[1] = 0.0f;
        /*printf(" child has %d\n ",nd->child[1]!=NULL);*/
        for (i=0;i<4;i++) {
            if (nd->child[i] != NULL) {

                treeForce(p, nd->child[i], f);
                totalForce[0] += f[0];
                totalForce[1] += f[1];

            }
        }

        return;
    }
}



void position_of_child(qNode *nd,int i,float* geom){
    /*return the center and half side length of i-th quadrant*/
    float half_side=nd->half_side;
    float center_x=nd->center_x;
    float center_y=nd->center_y;
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
    return;
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

void initializeNode(qNode *nd){
    nd->mc_x=-10000;
    nd->mc_y=-10000;
    nd->count=0;
    nd->half_side=10;
    nd->center_x=0;
    nd->center_y=0;
    nd->child[0]=NULL; nd->child[1]=NULL; nd->child[2]=NULL; nd->child[3]=NULL;
    nd->parent=NULL;
}

qNode* insert(qNode *nd,qNode *parent, int quadrant, Particle *p){   /* return the finally generated node*/
    /* parent qNode and int quadrant is only needed when nd==NULL, then the geom information of nd should come from parent
     * parent cannot be NULL when nd==NULL*/
    int i,j;
    float geom[3];
    if (nd==NULL){          /* nd is a NULL leaf*/
        position_of_child(parent,quadrant,geom);
        nd=malloc(sizeof(qNode));
        nd->mc_x=p->x;
        nd->mc_y=p->y;
        nd->count=1;
        nd->parent=parent;
        nd->center_x=geom[0];
        nd->center_y=geom[1];
        nd->half_side=geom[2];
        nd->child[0]=NULL; nd->child[1]=NULL; nd->child[2]=NULL; nd->child[3]=NULL;
        parent->child[quadrant-1]=nd;
        /*printf("the new node belong to %d\n",555);*/
        return nd;
    }
    else if (nd->count==0){    /* if nd is empty root, add the particle to nd*/
        nd->mc_x=p->x;
        nd->mc_y=p->y;
        nd->count=1;
        return nd;
    }

    else if (nd->count==1){    /* nd is leaf, the new added one make the node has 4 children*/
        /*when two particles ar etoo close*/
/*        if (abs(nd->mc_x-p->x)<1e-3 && abs(nd->mc_y-p->y)<1e-3)
            return nd;*/
        i=belong_to_which_quadrant_xy(nd, nd->mc_x, nd->mc_y);  /* the original particle belongs to i-th quandrant*/
/*        printf("%f %f\n",nd->mc_x, nd->mc_y);
        printf("%f %f\n",nd->center_x, nd->center_y);*/
        j=belong_to_which_quadrant(nd, p); /* new particle's quandrant*/

        /*printf("node1 [%f %f] and node2 [%f %f] belong to %d %d\n",nd->mc_x, nd->mc_y,p->x,p->y,i,j);*/
        /* move original particle to i*/
        position_of_child(nd,i,geom);      /*return shape of the child node to geom*/
/*        printf("%f ",nd->half_side);
        printf("%f %f %f\n",geom[0], geom[1],geom[2]);*/

        nd->child[i-1]=malloc(sizeof(qNode));
        nd->child[i-1]->mc_x=nd->mc_x;
        nd->child[i-1]->mc_y=nd->mc_y;
        nd->child[i-1]->center_x=geom[0];
        nd->child[i-1]->center_y=geom[1];
        nd->child[i-1]->half_side=geom[2];

        nd->child[i-1]->count=1;
        nd->child[i-1]->parent=nd;
        nd->child[i-1]->child[0]=NULL; nd->child[i-1]->child[1]=NULL;
        nd->child[i-1]->child[2]=NULL; nd->child[i-1]->child[3]=NULL;

        if (i!=j){
            nd->child[j-1]=malloc(sizeof(qNode));   /* add new particle to j*/
            position_of_child(nd,j,geom);
            nd->child[j-1]->mc_x=p->x;
            nd->child[j-1]->mc_y=p->y;
            nd->child[j-1]->center_x=geom[0];
            nd->child[j-1]->center_y=geom[1];
            nd->child[j-1]->half_side=geom[2];
            nd->child[j-1]->count=1;
            nd->child[j-1]->parent=nd;
            nd->child[j-1]->child[0]=NULL; nd->child[j-1]->child[1]=NULL;
            nd->child[j-1]->child[2]=NULL; nd->child[j-1]->child[3]=NULL;
            /*printf("tp: %f %f\n",nd->child[j-1]->mc_x,nd->child[j-1]->mc_y=p->y);*/
            return nd->child[j-1];
        }
        else{     /*i==j  two particles belong to the same children, this degenerate children still need split*/
            /*printf("b\n");*/
            return insert(nd->child[i-1],NULL,NULL, p);  /*nd->child[i-1] is not null, so 2nd and 3rd are not needed*/
        }
    }
    else{         /*nd is not leaf*/
        j=belong_to_which_quadrant(nd, p);
        /*printf("this node is in %d\n",j);*/
        return insert(nd->child[j-1],nd,j,p);
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
                /*printf("c\n");*/
                count+=p->child[i]->count;
                /*printf("child[i] has %d\n",p->child[i]->count);*/
                mc_x+=p->child[i]->mc_x*p->child[i]->count;
                mc_y+=p->child[i]->mc_y*p->child[i]->count;
            }
        }
        /*printf("d\n");*/
        p->count=count;
        /*printf("p count %d\n",p->count);*/
        p->mc_x=mc_x/count;
        p->mc_y=mc_y/count;
        nd=p;
    }
}

void printTree(qNode *nd){
    if (nd!=NULL){
        printf("nodecount: %d\n",nd->count);
        if (nd->count==1){
            printf("node: [%f %f]\n",nd->mc_x,nd->mc_y);
            return;
        }

        if(nd->child[0]!=NULL){
            printTree(nd->child[0]);
        }
        if(nd->child[1]!=NULL){
            printTree(nd->child[1]);
        }
        if(nd->child[2]!=NULL){
            printTree(nd->child[2]);
        }
        if(nd->child[3]!=NULL){
            printTree(nd->child[3]);
        }
    }
}

void free_Tree(qNode *nd){
    int i;
    if (nd!=NULL){
        for (i=0;i<4;i++){
            free_Tree(nd->child[i]);
        }
        free(nd);
    }
}
