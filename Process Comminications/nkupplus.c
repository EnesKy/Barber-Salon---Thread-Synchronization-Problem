#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int nkup,nkupplus,n = 0;
  double ndb;
  read(3,&nkup,sizeof(int));  // pipedaki değer okunur.
  ndb = cbrt((double)nkup); // kupkok alma metodu
  n = ndb / 1; // double ı integera çeviririz
  nkupplus = nkup + n;
  write(4,&nkupplus,sizeof(int)); // pipe a sonucu yazar
  return 0;
}