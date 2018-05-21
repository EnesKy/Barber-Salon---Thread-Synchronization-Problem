#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int a, b, i, temp, sonuc = 0;
    a = atoi(argv[0]); // terminalden gelen string deðerini, int deðerine çevirmek için atoi() 				//	kullanıyoruz.
    b = atoi(argv[1]);
    
    for(i=a; i<=b; i++){
	sonuc = sonuc + i;
    }
    

    for(temp = a; temp <= b; temp++){

	if(temp == b){
	printf("%d = %d \n",b,sonuc);	
 	}
	else{
            printf("%d + ",temp);
        }
    } 
        
    return 0;
}
