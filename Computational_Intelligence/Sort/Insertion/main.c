#include <stdio.h>
#include <mem.h>

int main() {
    char s[100];
    char current;
    int len,i,j,k;

    scanf("%s", s);
    len=strlen(s);

    if(len==1){ //If it is only one letter
        printf("%s\n",s);
    }
    else{ //lets sort
        for (i = 1; i < len;i++) {
            j=0;
            while(j<len) {
                if ((s[i] < s[j])&&(j<i)) {
                    current = s[i];
                    for (k=0; k<(i-j); k++) {
                       s[i-k]=s[i-k-1];
                    }
                    s[j]=current;
                    j = len;
                }
                j++;
            }
            printf("%s\n",s);
        }
    }
    //printf("hello");
    return 0;
}
