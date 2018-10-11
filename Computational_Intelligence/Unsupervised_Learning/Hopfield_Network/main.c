/*
 * Name:    Hopfield Network
 * Author:  Leonardo von Lerchenfeld
 * Date:    21.12.2017
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ncols 20
#define nrows 10
#define maximag 100
#define maxiter 50000
#define pushes 10


// #2 represent training & testing datasets as bipolar
    int converttoi(char patt){
        int bi=(int)patt-42;
        if(bi==4){
            bi=1;
        } else {
            bi=-1;
        }
        return bi;
    }

    char converttoc(int symbol){
        if(symbol>0){
            symbol=4;
        } else {
            symbol=0;
        }
        symbol=symbol+42;
        char sym=symbol;
        return sym;
    }

    int sign(int x) {
        return (x > 0) - (x < 0);
    }

    int main() {
        // Variable declaration
        int pattern[10][ncols*nrows]={0},npatt=0,row=0,col=0,goon=1,help=0,bug=1;
        int images[maximag][ncols*nrows]={0},nimag=0;
        char read[20]={0};

        // #1 acquire training pattaerns and testing (distorted) patterns
        // read patterns
        do {
            for(row=0;row<nrows;row++) {
                scanf("%s", &read);
                for (col = 0; col < ncols; col++) {
                    pattern[npatt][row*ncols+col] = converttoi(read[col]);
                }
                if(bug==1){//fix strange bug
                    help=pattern[0][0];
                    bug=0;
                }
            }
            scanf("%s", &read);
            if(read[2]=='-'){
                goon=0;
            }else{
                npatt++;
            }
        } while(goon==1);
        pattern[0][0]=help; //fix strange bug

        // read distorted images
        bug=1;
        do {
            for (row = 0; row < nrows; row++) {
                scanf("%s", &read);
                for (col = 0; col < ncols; col++) {
                    images[nimag][row*ncols+col] = converttoi(read[col]);
                }
                if(bug==1){//fix strange bug
                    help=images[0][0];
                    bug=0;
                }
            }
            nimag++;
        }while(scanf("%s",&read)!=EOF);
       // while(nimag<2); // A = 1 B = 2
        images[0][0]=help;



        // TRAINING PHASE
        int w[ncols*nrows][ncols*nrows]={0};
        for(int p=0;p<npatt;p++){ // #3
            for(int i=0;i<(ncols*nrows);i++){ // #4
                for(int j=0;j<(ncols*nrows);j++){ // #5
                    if(i!=j) w[i][j]+=pattern[p][i]*pattern[p][j]; // #6
                } // #7
            } // #8
        }  // #9

        // RECOVERY PHASE
        int denergy=0,ws=0,same=1,finish=0,nchanges=0;
        for(int imag=0;imag<nimag;imag++){
            for(int k=0;k<maxiter;k++) {
                nchanges=0;
                for (int n = 0; n < (nrows * ncols); n++) {
                    ws = 0;
                   /* srand((unsigned int)time(NULL));
                    int r = rand() % (ncols * nrows);
                    images[imag][r] = images[imag][r] * (-1); // flip the pixel
                    for (int matmul = 0; matmul < (nrows * ncols); matmul++) {
                        ws += w[n][matmul] * images[imag][matmul];
                    }
                    if (0 < (images[imag][r] * (-1) - (images[imag][r])) * ws) {
                        images[imag][r] = images[imag][r] * (-1);
                        // throw the change away
                    } else {nchanges++;}
                */

                    images[imag][n] = images[imag][n] * (-1); // flip the pixel
                    for (int matmul = 0; matmul < (nrows * ncols); matmul++) {
                        ws += w[n][matmul] * images[imag][matmul];
                    }
                    if (0 < (images[imag][n] * (-1) - (images[imag][n])) * ws) {
                        images[imag][n] = images[imag][n] * (-1);
                        // throw the change away
                    } else {nchanges++;}
                }
                // is it a pattern?
                for (int p = 0; p < npatt; p++) {
                    same = 1;
                    for (int n = 0; n < (ncols * nrows); n++) {
                        if (images[imag][n] != pattern[p][n]) {
                            same = 0;
                            break;
                        }
                    }
                    if (same == 1) {
                        finish = 1;
                        break;
                    }
                }
                if (finish == 1) {
                    finish = 0;
                    break;
                }
                // local minima?
                if(nchanges==0){
                    for (int j = 0; j < pushes; j++) {
                        srand(time(NULL));
                        int r = rand() % (ncols * nrows);
                        images[imag][r] = (-1)*images[imag][r];
                    }
                }

            }
        }
            // find the closest pattern
          /*  for (int im = 0; im < nimag; im++) {
                int selected = 0, nerror1 = ncols * nrows, nerror2 = 0;
                for (int p = 0; p < npatt; p++) {
                    nerror2=0;
                    for (int n = 0; n < (ncols * nrows); n++) {
                        if (images[im][n] != pattern[p][n]) {
                            nerror2 += 1;
                        }
                        }
                        if(nerror2>0.95*ncols*nrows){
                            for(int n=0;n<(ncols*nrows);n++){
                                images[im][n]=images[im][n]*(-1);
                            }
                            p--;
                            break;
                        }
                    if (nerror2 < nerror1) {
                        selected = p;
                        nerror1 = nerror2;
                    }
                }
                for(int n=0;n<(ncols*nrows);n++){
                    images[im][n]=pattern[selected][n];
                }
            } */


        // Print # 23
        char outc='0';
        for(int p=0;p<nimag;p++){
            for(int row=0;row<nrows;row++){
                for(int col=0;col<ncols;col++){
                    outc = converttoc(images[p][row*ncols+col]); //images=out
                    printf("%c", outc);
                }
                printf("\n");
            }
            if(p!=(nimag-1))printf("-\n");
        }

        return 0;
    }
