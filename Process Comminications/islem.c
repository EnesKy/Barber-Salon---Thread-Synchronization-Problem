#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int pipefd[2];
    int pid1, pid2, c1, c2;

    if (pipe(pipefd) < 0) { //pipe da hata olursa..
        perror("pipe");
        exit(1);
    }

    int fd1;
    char * myfifo = "/tmp/myfifo"; //oluşturulacak fifo adlı dosyanın path i

    mkfifo(myfifo, 0666); //fifo adlı dosya oluşturma
                          // 0666 = rw yani her kullanııya yazmak ve okumak için izin sağlar
                          // ama execute işlemini gerçekleştiremezler
    int sayi,sayi2;
    char gelen[80], giden[80];

    while (1) {
      fd1 = open(myfifo,O_RDONLY); //named pipe açılır.
      read(fd1, gelen ,80); //toplam.c'nin pipe'a yazdığı sayı alınır
      //printf("n = %s\n", gelen);
      close(fd1);

      sayi = atoi(gelen); // stringi integera çevirir.
      sayi2 = sayi;       
    
      pid1 = fork(); //fork işlemi yapılır.

    if (pid1 == 0) {   //child process
        write(pipefd[1], &sayi,sizeof(int)); // alınan sayı nkup.c'ye yollanır.
        c1 = execv("nkup", NULL); //nkup.c çalıştırılır.
        perror("nkup error");
    }
    else{    //parent process
      wait(&c1); // child beklenir
      int nkup;
      read(pipefd[0], &nkup, sizeof(int)); //nkup.c den gelen sonuc okunur.
      sayi = nkup;
      
      pid2 = fork();//2.fork işlemi yapılır.

      if(pid2 == 0){ //child process
         write(pipefd[1], &sayi,sizeof(int));// nkup.cden gelen sonuç nkupplus.n e yollanır.
         c2 = execv("nkupplus", NULL); //nkupplus.c çalıştırılır.
         perror("nkupplus error");
      }
      else {
        wait(&c2); //child beklenir
        int nkupplus;
        read(pipefd[0], &nkupplus, sizeof(int));//nkupplus.c den gelen sonuc okunur.
        printf("%d^3 + %d = %d\n",sayi2,sayi2,nkupplus);
        snprintf(giden,80,"%d",nkupplus); // stringe int ekleme metodu ile sonuc stringe aktarılır.
      }
    }
     
      fd1 = open(myfifo,O_WRONLY); //named pipe tekrar açılır
      write(fd1, giden, 80); //sonuc pipe a yazılır.
      close(fd1); //named pipe kapatılır.
    }
    close(pipefd[0]);//unnamed pipe kapatılır.
    close(pipefd[1]);
    return 0;
  }

