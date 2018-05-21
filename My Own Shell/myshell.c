#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *words[100],*argx[3];
int flag = 0;
char *satir;
size_t bufsize = 50;

char getWords(char *str,char *ayirac);

void metodlar(char ** envp);

void makeArgx(char a[],char b[],char c[]);


int main(int argc, char **argv,char ** envp){
    
    int i;

    while(1) {
	flag = 0; // flag i tekrar başlangıç haline getirdik.
	memset(&words, 0, sizeof(words)); // words arrayini temizleriz.
	
	printf("myshell>>");

	getline(&satir, &bufsize, stdin); //satır okur.

	getWords(satir,"&"); // çift komut varsa komutları ayrı ayrı alır yoksa aynı kalır.

	if(words[1] == NULL && words[0] != NULL){ // eğer tek komut varsa...
		flag = 1;

		getWords(words[0]," \t\r\n\a"); // kelimelere ayrılır.
	
		if(strcmp(words[0],"exit")==0){ 
		 flag = 2;
		 break;
		}
		else if(strcmp(words[0],"clear")==0){
		 flag = 2;
	 	 system("clear");
		}
		else if(strcmp(words[0],"cat")==0){
		 int j,flag = 2;;
		 printf("cat : ");
			for(j = 1; words[j] != NULL; j++){
	 	 	printf("%s ",words[j]);
			}
		 printf("\n");
		}
		else if(flag != 2){
		metodlar(envp);		
		}		

   	 }

	else if (words[1] != NULL && flag != 1){ // çift komut varsa...

//ilk komutu çalıştırır.
		char *komut2 = words[1]; //ikinci girilen metot ve girdileri tutulur.

		getWords(words[0]," \t\r\n\a"); // kelimelere ayrılır.

		metodlar(envp);		
	
//ikinci komutu çalıştırır.
		getWords(komut2," \t\r\n\a"); // kelimelere ayrılır.

		metodlar(envp);
	
	}

    }//while
	
    return 0;
}

//----------------------functions-------------------

void makeArgx(char a[],char b[],char c[]){ // alt programları çalıştırmak için yeni dizi oluşturuyoruz.
	argx[0] = a,argx[1] = b,argx[2] = c;
}

char getWords(char *str,char *ayirac){
  char *word; 
  int i; 

  word = strtok (str,ayirac);//ilk kelimeyi ayırır

  for(i = 0; 1 ; i++){
	if(word == NULL){ 
	   break;
	}
	words[i] = word;
	//printf("%d.kelime = %s - %d|\n",i,words[i],strlen(words[i]));
      	word = strtok (NULL, ayirac);// diğer kelimeleri ayırır. kelime yoksa NULL döner.
  }

}

void metodlar(char ** envp){
	int i,pid,flag=0;
		
		if(strcmp(words[0],"asal")==0) {
			flag = 1;
		}

		pid = fork();

		if(pid==0){
			if(strcmp(words[0],"asal")==0){
				makeArgx(words[1],NULL,NULL);
				i = execv("asal", argx); 
			}
			else if(strcmp(words[0],"palindrom")==0){
			   makeArgx(words[1],NULL,NULL);
	 		   i = execv("palindrom", argx);
			}
			else if(strcmp(words[0],"toplam")==0){
			   makeArgx(words[1],words[2],NULL);
	 		   i = execve("toplam", argx,envp);
			}
			/*else if(strcmp(words[0],"cat")==0){ // asıl cat metodu...
			   makeArgx("cat","toplam.c",NULL);
	 		   i = execv("/bin/cat", argx,envp);
			}*/
			else
		 	  printf("Komut bulunamadı.\n");
		}
		else{
			if(flag == 0 )		   
			   wait(&i); // alt programı bekler
		}
	
}

















