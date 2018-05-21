#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int n;
  read(3,&n,sizeof(int));  // pipedan değeri okur
  int nkup= n*n*n; //n^3 alma işlemi
  write(4,&nkup,sizeof(int)); // sonucu pipe a yazar
  return 0;
}