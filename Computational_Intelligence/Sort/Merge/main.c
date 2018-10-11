#include <stdio.h>
#include <mem.h>

void mergesort(char * group);
void merge(char * left, char * right, char * group );

int main() {
    int i=50;
    char s[100]={0};
    scanf("%s",s);
    if(strlen(s)<2){
        printf("%s",s);
    }
    else
    {
        mergesort(s);
    }


    return 0;
}

void mergesort(char * group){
    int len=strlen(group);
    if (len>1){
    //    printf("%s\n",group);
    //} <2
    //else
    //{
        int half=len/2;
        char left[100]={0};
        char right[100]={0};
        for (int i=0;i<half;i++){
            left[i]=group[i];
        }
        for (int i=half;i<len;i++){
            right[i-half]=group[i];
        }
        mergesort(left);
        mergesort(right);
        merge(left,right,group);
    }
}

void merge(char * left, char * right, char * group ){
    int len=strlen(left);
    int i=0,j=0,k=0;
    while((i<len)&&(j<len)){
        if(left[i]<=right[j]){
            group[k]=left[i];
            i++;
        }
        else{
            group[k]=right[j];
            j++;
        }
        k++;
    }
    while(i<len){
        group[k]=left[i];
        i++;
        k++;
    }
    while(j<len){
        group[k]=right[j];
        j++;
        k++;
    }
    if(strlen(group)>1){
        printf("%s\n",group);
    }

}

