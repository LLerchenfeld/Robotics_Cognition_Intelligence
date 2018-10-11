/*
 * Name:    Self Organizing Maps
 * Author:  Leonardo von Lerchenfeld
 * Date:    16.01.2018
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define nmax 1000
#define maxcityperneuron 20
#define nepochs 1000000
#define lr 1 // learning rate
#define additional 3 // make 3 (2.5) times prototypes than cities
//#define circlesize 1.5 //the bigger the smaller the kohonen ring
//#define PI 3.14159265

double eucldist(double xone, double yone, double xtwo, double ytwo){
    return sqrt(pow((xone-xtwo),2)+(pow((yone-ytwo),2)));
}
int topdist(int n,int bmu,int nproto){
    int dist1=abs(bmu-n);
    int dist2=nproto-abs(n-bmu);
    if(dist1<dist2){
        return dist1;
    }else{
        return dist2;
    }
}
double learningrate(float LR,int t,int lamda){
    return LR*exp(-t/lamda);
}
double neighborhood(double d, float a){
    return exp(-(d*d)/(2*a*a));
}
double sigma(double sigmanull,double t,double lamda){
    t=t+1; // to start iterate from 1 instead of 0
    return sigmanull*exp(-(t)/lamda);
}


int main() {
    // Variable declaration
    float x[nmax]={0},y[nmax]={0},wx[additional*nmax]={0},wy[additional*nmax]={0};
    float xmax=0,xmin=0,ymin=0,ymax=0,xmean,ymean,rf=0,a=lr;
    double dist1=0,dist2=0,arg=0,d=0;
    int city[nmax]={0},i=0,j=0,ncities=0,nprotos=0,bmu=0,addpro=0,toprint[nmax]={0};
    int ncitiestow[additional*nmax]={0},mapprototocity[additional*nmax][maxcityperneuron]={0};
    //time_t t0 = time(NULL);

    srand((unsigned int) time(NULL));

    // read data
    while(scanf("%i,%f,%f",&city[j],&x[j],&y[j])!=EOF){j++;}
    /*while(j<500){ //A=40 B=5 E=500
        scanf("%i,%f,%f",&city[j],&x[j],&y[j]);
        j++;
    }*/
    ncities=j;
    for(i=0;i<ncities;i++){toprint[i]=1;}

    // find min and max values
    xmax=x[0];
    xmin=x[0];
    ymin=y[0];
    ymax=y[0];
    xmean=x[0];
    ymean=y[0];
    for(j=1;j<ncities;j++){
        if(x[j]<xmin)xmin=x[j];
        if(x[j]>xmax)xmax=x[j];
        if(y[j]<ymin)ymin=y[j];
        if(y[j]>ymax)ymax=y[j];
        xmean+=x[j];
        ymean=y[j];
    }
    //xmean=xmean/ncities;
    //ymean=ymean/ncities;

    // # 1 Initialize each node`s weight
    nprotos=ncities*additional;
    // Kohonen Ring
    for(j=0;j<nprotos;j++){
        wx[j]=(rand()%(int)(xmax+abs((int)xmin))-abs((int)xmin));
        wx[j]=(rand()%(int)(ymax+abs((int)ymin))-abs((int)ymin));
        /*arg=2*PI*j/nprotos;
        wx[j]=cos(arg)*(xmax-xmin)/circlesize+xmin+xmean/2;
        wy[j]=sin(arg)*(ymax-ymin)/circlesize+ymin+ymean/2; */
    }

    int sigmazero=nprotos/(2*sqrt(2));
    double lambda=nepochs/log(sigmazero);

    for(int epoche=0;epoche<nepochs;epoche++) {
        // # 2 Pick a random vector from dataset and present it to the network
        int ir = rand() % ncities;
        // # 3 find the best matching unit (BMU)
        //for(int ir=0;ir<ncities;ir++) {
        dist1 = eucldist(x[ir], y[ir], wx[0], wy[0]);
        bmu = 0;
        for (j = 1; j < nprotos; j++) {
            dist2 = eucldist(x[ir], y[ir], wx[j], wy[j]);
            if (dist2 < dist1) {
                dist1 = dist2;
                bmu = j;
            }
        }
        // update weights
        for (j = 0; j < nprotos; j++) {
            d = neighborhood(topdist(j,bmu,nprotos), sigma(sigmazero,epoche,lambda));
            wy[j] += learningrate(lr,epoche,lambda) * d * (y[ir] - wy[j]);
            wx[j] += learningrate(lr,epoche,lambda) * d * (x[ir] - wx[j]);
        }
        //}

        // Check convergence
        /*  if(epoche==0) {
              printf("\nCities X: ");
              for (i = 0; i < ncities; i++) { printf("%f ; ", x[i]); }
              printf("\n");
              printf("Cities Y: "); for(i=0;i<ncities;i++){printf("%f ; ",y[i]);}printf("\n\n");
              printf("Xmin: %f - Xmax: %f - Ymin: %f - Ymax: %f \n\n",xmin,xmax,ymin,ymax);
          }
          if(epoche%(nepochs/10)==0||epoche==0){
              printf("Protos X: "); for(i=0;i<nprotos;i++){printf("%f ; ",wx[i]);}printf("\n");
              printf("Protos Y: "); for(i=0;i<nprotos;i++){printf("%f ; ",wy[i]);}printf("\n\n");
          } */

    }

    // Print result
    for(i=0;i<ncities;i++){
        dist1=eucldist(wx[0],wy[0],x[i],y[i]);
        bmu=0;
        for(j=1;j<nprotos;j++){
            dist2=eucldist(wx[j],wy[j],x[i],y[i]);
            if(dist2<dist1){
                dist1=dist2;
                bmu=j; //which prototype is closest to the city i
            }
        }
        mapprototocity[bmu][ncitiestow[bmu]]=i;
        ncitiestow[bmu]=ncitiestow[bmu]+1;
    }
    for(j=0;j<nprotos;j++){
        for(i=0;i<ncitiestow[j];i++){
            printf("%i\n",city[mapprototocity[j][i]]);
        }
    }

    /*time_t t1 = time(NULL);
    printf("\nThe application took %lu s \n", t1 - t0);*/
    return 0;
}