#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int n, i, temp = 0;
    n = atoi(argv[0]); // terminalden gelen string değerini, int değerine çevirmek için atoi() kullanıyoruz.

    for(i=2; i<=n/2; ++i){
        if(n%i==0){
            temp=1;
            break;
        }
    }

    if (temp==0)
        printf("%d => asaldır.\n",n);
    else
        printf("%d => asal değildir.\n",n);
    
    return 0;
}
