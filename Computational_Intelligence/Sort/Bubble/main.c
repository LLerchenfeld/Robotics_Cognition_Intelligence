#include <stdio.h>
#include <mem.h>
int Issorted(char* letters);

int main() {
    char s[100];
    char tempo;
    int l,i,sorted;

    scanf("%s", s);

    // printf("Deine Eingabe ist: %s\n",s);
    l=strlen(s);
    if(l==1){ //If it is only one letter
        printf("%s\n",s);
    }
    else{
        sorted=Issorted(s);
        if(sorted) { //if it is already sorted
            printf("%s\n", s);
        }
        else{ //lets sort
             // printf("not");
            while(!Issorted(s))
            {
                for (i = 0; i < l-1; i++) {
                    if(s[i]>s[i+1]){
                        tempo=s[i];
                        s[i]=s[i+1];
                        s[i+1]=tempo;
                    }
                }
                printf("%s\n",s);
            }
        }

    }

    //printf("hello");
    return 0;
}

int Issorted(char* letters) {
    int ind, len, sort;
    sort=1;
    len = strlen(letters);
    char temp;
    for (int ind = 0; ind < len - 1; ind++) {

        if (letters[ind] > letters[ind+1]) {
            sort = 0;
        }
    }
    return (sort);
}
