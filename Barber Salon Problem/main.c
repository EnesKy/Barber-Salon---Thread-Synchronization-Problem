#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<time.h>

#define musteriSayisi 10
#define koltukSayisi 3 //0 dan başlattığım için 0,1,2,3 şeklinde 4 koltuk olur.

struct koltukYapisi{
  int thread_no;
  int doluMu;
};
 
struct koltukYapisi K[koltukSayisi];

sem_t salon; //berber salonu
sem_t trasKoltugu;  //1 adet thread alır. Yani mutex ile aynı işlevdedir.
sem_t tras; //tras zamanı...

int flag = 0, updateWorked = 0; 
  
void update(int num){  //"K1[T0] <> K2[T1] <> K3[T7] <> K0[T3]";

  if (K[1].doluMu){ //doluysa
    printf("K1[T%d] <> ",K[1].thread_no);
  }
  else{//boşsa
    if (updateWorked == 0){ //eğer bir işlem olmadıysa
      K[1].thread_no = num;
      K[1].doluMu = 1;
      printf("K1[T%d] <> ",K[1].thread_no);
      updateWorked = 1; //işlem yapıldı.
    }
    else{
      printf("K1[  ] <> ");
    }
  }

  if (K[2].doluMu){ 
    printf("K2[T%d] <> ",K[2].thread_no);
  }
  else{//boşsa
    if (updateWorked == 0){ //eğer bir işlem olmadıysa
      K[2].thread_no = num;
      K[2].doluMu = 1;
      printf("K2[T%d] <> ",K[2].thread_no);
      updateWorked = 1; //işlem yapıldı.
    }
    else{
      printf("K2[  ] <> ");
    }
  }

  if (K[3].doluMu){ 
    printf("K3[T%d] <> ",K[3].thread_no);
  }
  else{//boşsa
    if (updateWorked == 0){ //eğer bir işlem olmadıysa
      K[3].thread_no = num;
      K[3].doluMu = 1;
      printf("K3[T%d] <> ",K[3].thread_no);
      updateWorked = 1; //işlem yapıldı.
    }
    else{
      printf("K3[  ] <> ");
    }
  }

  if (K[0].doluMu){ //TRAŞ KOLTUĞU
    printf("K0[T%d]\n",K[0].thread_no);
  }
  else{//boşsa
    printf("K0[  ]\n");
    updateWorked = 1;
  } 

  updateWorked = 0;

}

void *islemler(int num){
  sem_wait(&salon); //salona giriş
    update(num); // koltuk durumlarını yazdırma
    //printf("K1[%d] <> K2[%d] <> K3[%d] <> K0[%d]\n",K[1].thread_no,K[2].thread_no,K[3].thread_no,K[0].thread_no);
  sem_wait(&trasKoltugu); //traş koltuğuna giriş
    time_t t;
    time(&t);
    for (int i = 0; i < koltukSayisi+1; ++i){ // traş koltuğuna oturan müşterinin 
                                              // kalktığı bekleme koltuğunu boşaltırız
      if (K[i].thread_no == num && K[i].thread_no != -1){ //eski koltuğu boşaltır.
        K[i].thread_no = -1;
        K[i].doluMu = 0;
      }
      else{}
    }
     printf("T%d <> %s", num,ctime(&t)); //koltuğa oturan th no <> sist. time yazdırır

    if(!K[0].doluMu){//traş koltuğunu doldurur.
      K[0].thread_no = num;
      K[0].doluMu = 1;
    }

  sem_post(&salon);
   
  sem_wait(&tras); // traş başlasın

  sleep(num);//traş olduktan sonra threadnosu kadar beklemede kalma durumu
  
  sem_post(&trasKoltugu); //koltuktan kalktı
    //printf("\nT%d in traşı bitti ve salondan çıktı.\n", num); 
    if (K[0].thread_no == num){
      K[0].thread_no = -1;
      K[0].doluMu = 0;
      //printf("\nT%d in traşı bitti ve salondan çıktı.\n", num);
    } 
    else{}
    update(num);
} 

void *berber(){ 
  while (!flag){
    sleep(2);//traş süresi 20 dk
    sem_post(&tras); //traş bitsin.
  }
  if (flag){
    printf("Müşteri kalmadı. İşlem bitti.\n");
  }
}

int main(int argc, char **argv){
  pthread_t tid[musteriSayisi]; 
  pthread_t berberTid;
  int mustNum[musteriSayisi],i;

  for (int i = 0; i < koltukSayisi+1; ++i){//tüm koltukları boş olarak tanımladık
    //K[i].doluMu = 0; 
    K[i].thread_no = -1; //thread numaralarını default olarak 0 değil -1 atadım.
  }

  for (i = 0; i < musteriSayisi; i++){ 
    mustNum[i] = i; 
  }

  sem_init(&salon, 0, koltukSayisi); 
  sem_init(&trasKoltugu, 0, 1);
  sem_init(&tras, 0, 0); 

  //Threadleri oluşturalım.
  for (i = 0; i < musteriSayisi; i++){
    pthread_create(&tid[i], NULL, islemler, mustNum[i]); 
  }

  pthread_create(&berberTid, NULL, berber, NULL); 

  // Threadlerin tamamlanmasını beklemek için her threade join yapalım. 
  for (i = 0; i < musteriSayisi; i++) { 
    pthread_join(tid[i],NULL); 
  }

  //Müşteriler bitince, berber threadini bitirelim
  flag = 1; 
  pthread_join(berberTid,NULL); 
  sem_destroy(&salon);
  sem_destroy(&trasKoltugu);
  sem_destroy(&tras);
  exit(0);
  return 0;
}