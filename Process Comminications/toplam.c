#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
int main(){
    int fd;
    char * myfifo = "/tmp/myfifo"; //named pipe için oluşturulacak dosyanın pathi
    mkfifo(myfifo, 0666);// named pipe için myfifo adlı dosya oluşturulur.
    					// kullanıcılara bu dosyayı sadece okuma ve yazma yetkisi verilmiştir
 
    char gelen[80], giden[80], try[250];

    int ust;
    printf("Ust sinir icin giris yapiniz: ");
    scanf("%d",&ust);

    int alt,alt2;
    printf("Alt sinir icin giris yapiniz: ");
    scanf("%d",&alt);
    alt2 = alt; //alt değerin yedeği alınır.

    int sonuc = 0,sayi;
    char ayirac[5] = " + "; //çıktı için...

    while (1){

        fd = open(myfifo, O_WRONLY); //named pipe açılır
        snprintf(giden,80,"%d",alt); // alt sayısı, stringe aktarılır.
        write(fd,giden, strlen(giden)+1); // sayı pipe a yazılır
        close(fd);

        fd = open(myfifo, O_RDONLY);//named pipe açılır
		read(fd, gelen,80);//pipedan gelen sayı okunur

        if (ust == alt){ //bu kısım çıktı için...
            strcat(try,gelen); // stringe islem.c den gelen değer eklenir.
            printf("%s\n",try);
        }
        else if (alt == alt2){
            strcat(try,gelen);
            printf("%s\n",try);
            strcat(try,ayirac);
        }
        else{
            strcat(try,gelen);
            strcat(try,ayirac);
            printf("%s\n", try);
        }
        alt++; //alt değeri 1 arttırılır...
        sayi = atoi(gelen);// gelen stringindeki değer sayi integerına aktarılır.
        sonuc = sonuc + sayi;
        close(fd);

         if (alt>ust){// eğer alt sayısı ust sınırı geçtiyse program sonlanır.
            printf("Sonuc = %d\n", sonuc);
            break;
        }
    }
    return 0;
}