/*
 * Name:    Vector Quantization
 * Author:  Leonardo von Lerchenfeld
 * Date:    17.01.2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// #include <string.h>
#define disttoprotos 0.000000000001
#define learningrate 0.015
#define niter 10000

int disttoprotoislarge(double *xproto, double *yproto, float xpoint, float ypoint, int noproto, float mindist);
int thenearestprototype(double *xproto, double *yproto, float xpoint, float ypoint, int noproto);
double euclideandist(double xone, double yone, double xtwo, double ytwo);
double manhattandist(double xone, double yone, double xtwo, double ytwo);

// #define neurons 4 // per layer
int main() {
    // Variable declaration
    float x[1000]={0},y[1000]={0}; // points
    float xmax=0,xmin=0,ymin=0,ymax=0,range=0,maxrange=disttoprotos*0.1,radius=disttoprotos;
    double protox[1000]={0},protoy[1000]={0}; // prototypes
    int nproto=0,i=0,npoints=0; // number of prototypes
    srand((unsigned int) time(NULL));

    // read data
    scanf("%i",&nproto);
    while(scanf("%f,%f",&x[i],&y[i])!=EOF){i++;}
    /*while(i<40){ //A=40 B=100 C=50
        scanf("%f,%f",&x[i],&y[i]);
        i++;
    }*/
    npoints=i;

    // find min and max values
    xmax=x[0];
    xmin=x[0];
    ymin=y[0];
    ymax=y[0];
    for(i=1;i<npoints;i++){
        if(x[i]<xmin)xmin=x[i];
        if(x[i]>xmax)xmax=x[i];
        if(y[i]<ymin)ymin=y[i];
        if(y[i]>ymax)ymax=y[i];
    }

    // determine a good distance between the points
    range=abs(xmax)+abs(xmin);
    if(range<abs(ymax)+abs(ymin))range=abs(ymax)+abs(ymin);
    while(maxrange<range){
        maxrange=maxrange*10;
        radius=radius*10;
    }

    // choose datapoints with big distance to each other as prototypes
    protox[0]=x[0];
    protoy[0]=y[0];
    int setproto=1,count=0,notset=0;
    while(setproto<nproto){ // for a given number of prototypes
        for(i=1;i<npoints;i++){
            if(setproto==nproto)break;
            if(disttoprotoislarge(protox,protoy,x[i],y[i],setproto,radius)==1){
                protox[setproto]=x[i];
                if(x[i]>0){
                    protox[setproto]+=range/(3*nproto);
                } else {
                    protox[setproto]-=range/(3*nproto);
                }
                protoy[setproto]=y[i];
                if(y[i]>0){
                    protoy[setproto]+=range/(3*nproto);
                } else {
                    protoy[setproto]-=range/(3*nproto);
                }
                setproto++;
            }
        }
        radius=radius*0.5;
        count++;
        if(count==5000){
            notset=1;
            break;
        }
    }
    for(i=setproto;i<nproto;i++){
        int ir = rand() % npoints;
        protox[i]=x[ir];
        protoy[i]=y[ir];
    }

    /* // TESTING
    printf("\nInitial Prototypes\n");
    for(i=0;i<nproto;i++){
        printf("%f,%f\n",protox[i],protoy[i]);
    }
    printf("\nComputed Prototypes\n"); */

    // COMPETITIVE LEARNING
    float eta=learningrate;
    int closestp=0;
    while(eta>0){
        double dprox[1000]={0},dproy[1000]={0};
        for(i=0;i<npoints;i++){
            if(nproto==0)break;
            closestp=thenearestprototype(protox,protoy,x[i],y[i],nproto);
            dprox[closestp]+=eta*(x[i]-protox[closestp]);
            dproy[closestp]+=eta*(y[i]-protoy[closestp]);
        }
        for(i=0;i<nproto;i++){
            protox[i]+=dprox[i];
            protoy[i]+=dproy[i];
        }
        eta=eta-learningrate/niter;
    }


    for(i=0;i<nproto;i++){
        printf("%f,%f\n",protox[i],protoy[i]);
    }

    return 0;
}

double euclideandist(double xone, double yone, double xtwo, double ytwo){
    return sqrt(pow((xone-xtwo),2)+(pow((yone-ytwo),2)));
}

double manhattandist(double xone, double yone, double xtwo, double ytwo){
    return abs(xone-xtwo)+abs(yone-ytwo);
}

int disttoprotoislarge(double *xproto, double *yproto, float xpoint, float ypoint, int noproto, float mindist){
    int islarge=0;
    for(int i=0;i<noproto;i++){
        if(manhattandist(xpoint,ypoint,*xproto,*yproto)>mindist){
            islarge=1;
        } else {
            islarge = 0;
            break;
        }
        xproto++;
        yproto++;
    }
    return islarge;
}

int thenearestprototype(double *xproto, double *yproto, float xpoint, float ypoint, int noproto){
    int theone=0;
    double distprev=0, distpost=0;
    distprev=euclideandist(xpoint,ypoint,*xproto,*yproto);
    for(int i=1;i<noproto;i++){
        xproto++;
        yproto++;
        distpost=euclideandist(xpoint,ypoint,*xproto,*yproto);
        if(distpost<distprev){
            theone=i;
            distprev=distpost;
        }

    }
    return theone;
}