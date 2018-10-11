#include <stdio.h>
#include <mem.h>

struct node{
    int exist;
    int parent;
    char color;
    int distant;
    //int children[27];
};
void BFS(int start,int* graph,struct node *ptr);
void enque(char *queue,int length,int next);
char deque(char *que, int lenq);
int stoi(char* letter,int forward); //convert char to int
int ctoi(char letter);

int main()
{
    int adjm[27][27]={0}; //adjacency matrix
    int startset=0,rows=0,cols=0,len=0,i=0;//cols=0,i
    int startnode=0;
    char read[100]={0};

    struct node alphabet[27]={0};
    while(scanf("%s",read)!=EOF){
        i=2; // counter for scanning text
        len=strlen(read);
        //set 1st letter as input node, special case: start node -> see below
        if(startset==1)
        {
            rows=stoi(read,0);
            alphabet[rows].exist=1;
        }
        // declare startnode
        if(startset==0){
            startnode=stoi(read,0);
            startset=1;
            rows=startnode;
            alphabet[startnode].exist=1;
            alphabet[cols].exist='g';
        }
        // fill in adjacency matrix
        while(i<len){
            cols=stoi(read,i);
            adjm[rows][cols]=1;
            adjm[cols][rows]=1;
            alphabet[cols].exist=1;
            alphabet[cols].exist='w';
            i++;
        }
    }
    int * adjmp;
    adjmp = &adjm[0][0];
    BFS(startnode , adjmp, alphabet);
    //printf("%i",adjm[0][2]);
    return 0;
}

void BFS(int start,int* padj, struct node *palpha) {
    // Initialization of start node
    palpha+=start;
    palpha->parent=0;
    palpha->color='g';
    palpha->distant=0;
    palpha-=start; // set node pointer to beginning
    int *pn, *pv;
    int dist=0;
    pn = padj;  //pointer on node
    pv = padj; //pointer on neighbor
    char path[100]={0};
    int ipath=0;
    char que[27]={0};
    enque(que,0,start);
    while(que[0]){
        char nc=deque(que,27); //nc = node char(format)
        int childs=0;
        path[ipath]=nc;
        ipath++;
        palpha+=ctoi(nc);
        dist=palpha->distant; //get distant from current node
        palpha-=ctoi(nc); //reset alphabet pointer
        pn+=ctoi(nc);; //set pointer to corresponding row in adjacency matrix
        for(int neighbor=0;neighbor<27;neighbor++)
        {
            if(*pn==1) //has neighbor here
            {
                palpha+=neighbor; //set pointer to neighbor / vicino
                char colour=palpha->color;
                if(colour==0){//is neighbor unexplored?
                    palpha->color='g';
                    palpha->distant=dist+1;
                    palpha->parent=ctoi(nc);
                    enque(que,strlen(que),neighbor);
                }
                palpha-=neighbor; //reset pointer for neighbors
            }
            pn+=27; //go to next column
        }
        pn=padj;
        palpha+=ctoi(nc);
        palpha->color='b';
        palpha-=ctoi(nc);
    }

    /* char love = ptr->color; */
    printf("%s",path);
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

char itoc(int num){
    char c = num + 'A';
    return c;
}

void enque(char *queue,int length,int letter){
    queue +=length;
    char * next;
    next = queue;
    next ++;
    for(int i=0;i<length;i++){
        *next = *queue;
        next--;
        queue--;
    }
    *next = *queue;
    *queue=itoc(letter);
}

char deque(char *que, int lenq)
{
    char out=*que;
    char * next;
    next=que;
    next++;
    for(int j=0;j<lenq-1;j++)
    {
        *que=*next;
        next ++;
        que++;

    }
    *que='\0';
    return out;
}
