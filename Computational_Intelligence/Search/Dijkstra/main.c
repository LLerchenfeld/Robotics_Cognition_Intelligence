#include <stdio.h>
#include<string.h>
// #include<stdlib.h>
// #include<math.h>
// #include <mem.h>

struct node{
    int exist;
    char color;
    int distant;
    char parent[100];
    //int children[27];
};
void enque(char *queue,int letter);
void deque(char *que, int lenq);
int stoi(char* letter,int forward); //convert char to int
int numbertoi(char number);
int numberstoi(char *numberptr,int forward); //convert string to number
char numbertoc(int num);
int ctoi(char letter);
char itoc(int num);
void dijkstra(int start,int* graph,struct node *ptr);
int main()
{
    int adjm[27][27]={0}; //adjacency matrix
    int startset=0,rows=0,cols=0,len=0,i=0;//cols=0,i
    int startnode=0;
    int cost=0;
    char read[100]={0};

    struct node alphabet[27]={0};
    int j=0; //while(scanf("%s",read)){
    while(scanf("%s",read)!=EOF){
        //while(j<676){ //28
        //scanf("%s",read);
        char a = read[0];
        // declare startnode
        if(startset==0){
            startnode=stoi(read,0);
            startset=1;
            alphabet[startnode].parent[0]=a;
            alphabet[startnode].parent[1]='-';
            alphabet[startnode].parent[2]='0';
            rows=startnode;
        } else {
            rows=stoi(read,0);
        }

        cols=stoi(read,2);
        cost=numberstoi(read,4);
        alphabet[rows].exist=1;
        alphabet[cols].exist=1;
        alphabet[rows].distant=30000; //30000 for infinity
        alphabet[cols].distant=30000;
        adjm[rows][cols]=cost;
        adjm[cols][rows]=cost;
            adjm[rows][rows]=0; // prevent nodes that show on them self
        cost=0;
        //alphabet[startnode].exist='g';

        j++; //for CLion
    }
    alphabet[startnode].distant=0;
    int * adjmp;
    adjmp = &adjm[0][0];
    dijkstra(startnode , adjmp, alphabet);
    //printf("%i",adjm[0][2]);
    return 0;
}

void dijkstra(int start,int* adjm, struct node *palphabet) {
    //All nodes that exist already have a distant of 30000 (infinity)
    struct node *palpha;
    struct node *pneighbor;
    palpha = palphabet;
    pneighbor = palphabet;
    // add all nodes that exist to the que
    char que[27]={0}, onetoten='\0', tentohun='\0', huntomil='\0', mil='\0';
    char * pque;
    pque=que;
    int dist=0,ileastdist=0,max=0,itemplen=0,itempdist=0,itempdiff=0;
    int *padj;


    // Put all existing npde into the que
    for(int i=0;i<27;i++){
        if(palpha->exist>0){
            enque(que,i);
            max++;
        }
        palpha++;
    }
    palpha-=27; //reset pointer to the beginning from the alphabet

    // For all existing nodes
    while(max){
        char path[100]={0};
        padj=adjm; //set pointer to beginning of adjacency matrix

        //select node with least distance first
        dist=30000;
        for(int i=0;i<27;i++){
            if(ctoi(*pque)==i) //check for nodes in the que
            {
                if(palpha->distant < dist){ //check for minimum distance
                    dist=palpha->distant;
                    ileastdist=i;
                }
            }
            palpha++;
            pque++;
        }
        deque(que,ileastdist);
        //set pointer to current node
        palpha-=27;
        pque-=27;
        padj+=ileastdist;
        palpha+=ileastdist;

        // define distances
        for(int neighbor=0;neighbor<27;neighbor++){
            itempdist=0;
            if(*padj>0){ //there is a connection
                pneighbor+=neighbor;

                if(pneighbor->distant > (palpha->distant + *padj)){
                    pneighbor->distant=(palpha->distant + *padj);
                    // remove old parent
                    itemplen=strlen(pneighbor->parent);
                    for (int ii=0;ii<itemplen;ii++){
                        pneighbor->parent[ii]='\0';
                    }
                    // get new parent
                    itemplen = strlen(palpha->parent);
                    onetoten = palpha->parent[itemplen-1];
                    if(palpha->parent[itemplen-2]!='-'){ //number is bigger than ten
                        if(palpha->parent[itemplen-3]!='-'){ //number is bigger than hundred
                            if(palpha->parent[itemplen-4]!='-'){ //number is bigger than thousand
                                mil=palpha->parent[itemplen-4];
                                itempdist+=1000*numbertoi(mil);
                            }
                            huntomil = palpha->parent[itemplen-3];
                            itempdist+=100*numbertoi(huntomil);
                        }
                        tentohun = palpha->parent[itemplen-2];
                        itempdist+=10*numbertoi(tentohun);
                    }
                    itempdist+=numbertoi(onetoten);

                    // how much to copy from the parent path
                    itempdiff=1;
                    if(itempdist>10) itempdiff=2;
                    if(itempdist>100) itempdiff=3;
                    if(itempdist>1000)itempdiff=4;

                    // write path
                    path[0]=itoc(neighbor);
                    path[1]='-';
                    for (int run=0;run<itemplen-itempdiff;run++){ // copy path from node before
                        path[run+2]=palpha->parent[run];
                    }
                    itempdist+=*padj; //now this is the new dist
                    onetoten = numbertoc(itempdist%10);

                    if (itempdist/1000 > 0){ //very very big distances
                        mil = numbertoc(itempdist/1000);
                        huntomil= numbertoc((itempdist%1000)/100);
                        tentohun = numbertoc(((itempdist%1000)%100)/10);
                        path[strlen(path)]=mil;
                        path[strlen(path)]=huntomil;
                        path[strlen(path)]=tentohun;
                        path[strlen(path)]=onetoten;
                    }
                    else if(itempdist/100 > 0){//very big distances
                        huntomil = numbertoc(itempdist/100);
                        tentohun = numbertoc((itempdist%100)/10);
                        path[strlen(path)]=huntomil;
                        path[strlen(path)]=tentohun;
                        path[strlen(path)]=onetoten;
                    }
                    else if(itempdist/10 > 0){ //big distances
                        tentohun = numbertoc(itempdist/10);
                        path[strlen(path)]=tentohun;
                        path[strlen(path)]=onetoten;
                    }
                    else{
                        path[strlen(path)]=onetoten;
                    }
                    for(int run=0;run<strlen(path);run++){ // insert into new path
                        pneighbor->parent[run]=path[run];
                        //path[run]='\0';
                    }

                    // clear path
                    itempdiff=strlen(path);
                    for (int ii=0;ii<itempdiff;ii++){
                        path[itempdiff-1-ii]='\0';
                    }
                    itempdiff=0;
                }
                pneighbor-=neighbor;
            }
        padj+=27;
        }
        palpha-=ileastdist; //reset pointer to beginning of alphabet
        max--;
    }
    palpha=palphabet;
    for(int i=0;i<27;i++){
        if(palpha->exist>0){
            //remove errors, if there are changes between path and distant
            itemplen=strlen(palpha->parent);
            onetoten=palpha->parent[itemplen-1];
            itempdist=onetoten;
            if(palpha->parent[itemplen-2]!='-')
            {
                tentohun=palpha->parent[itemplen-2];
                itempdist+=tentohun*10;
                if(palpha->parent[itemplen-3]!='-'){
                    huntomil=palpha->parent[itemplen-3];
                    itempdist+=huntomil*100;
                    if(palpha->parent[itemplen-4]!='-'){
                        mil=palpha->parent[itemplen-4];
                        itempdist+=mil*1000;
                    }
                }
            }
            // if there is an error
            if(itempdist!=palpha->distant)
            {
                itempdist=palpha->distant;
                // delete path
                while(palpha->parent[strlen(palpha->parent)-1]!='-'){
                    palpha->parent[strlen(palpha->parent)-1]='\0';
                }
                onetoten = numbertoc(itempdist%10);

                if (itempdist/1000 > 0){ //very very big distances
                    mil = numbertoc(itempdist/1000);
                    huntomil= numbertoc((itempdist%1000)/100);
                    tentohun = numbertoc(((itempdist%1000)%100)/10);
                    palpha->parent[strlen(palpha->parent)]=mil;
                    palpha->parent[strlen(palpha->parent)]=huntomil;
                    palpha->parent[strlen(palpha->parent)]=tentohun;
                    palpha->parent[strlen(palpha->parent)]=onetoten;
                }
                else if(itempdist/100 > 0){//very big distances
                    huntomil = numbertoc(itempdist/100);
                    tentohun = numbertoc((itempdist%100)/10);
                    palpha->parent[strlen(palpha->parent)]=huntomil;
                    palpha->parent[strlen(palpha->parent)]=tentohun;
                    palpha->parent[strlen(palpha->parent)]=onetoten;
                }
                else if(itempdist/10 > 0){ //big distances
                    tentohun = numbertoc(itempdist/10);
                    palpha->parent[strlen(palpha->parent)]=tentohun;
                    palpha->parent[strlen(palpha->parent)]=onetoten;
                }
                else{
                    palpha->parent[strlen(palpha->parent)]=onetoten;
                }
            }

            // print
            char printer[100];
            // copy of string
            for(int I=0;I<100;I++){
                printer[I]=palpha->parent[I];
            }
            printf("%s\n",printer);
        }
        palpha++;
    }
    int uhu=0;
}

int stoi(char* letter, int forward){
    letter+=forward; //new pointer position
    *letter-='A'; //substract ASCII value
    int number=0;
    number = (int)*letter; //convert to int
    return number;
}

int ctoi(char letter){
    letter-='A'; //substract ASCII value
    int number=0;
    number = (int)letter; //convert to int
    return number;
}

char itoc(int num)
{
    char c = num + 'A';
    return c;
}

char numbertoc(int num)
{
    char c = num + '0';
    return c;
}

// Converts a number from char to int
int numbertoi(char number){
    int num=0;
    number-='0';
    num=(int)number;
    return num;
}

int numberstoi(char *numberptr,int forward){
    int number=0,help=0;
    numberptr+=forward; //new pointer position
    *numberptr-='0'; //substract ASCII value
    number = (int)*numberptr; //convert to int
    numberptr++;
    if(*numberptr>0){
        *numberptr-='0';
        help = (int)*numberptr;
        number = number*10;
        number += help;
    }
    return number;
}

void enque(char *queue,int letter){
    queue+=letter;
    *queue=itoc(letter);
}



void deque(char *que, int letter)
{
    que+=letter;
    *que='\0';
}
