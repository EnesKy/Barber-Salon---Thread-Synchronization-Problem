#include <stdio.h>
#include <string.h>
  
int main(int argc, char *argv[]){

	char *str,*line;
	int i,j;
	int l = 0,flag = 0;
	str = argv[0];

        int h = strlen(str) - 1;
	line = str;

	 for(i = 0; line[i] != '\0'; ++i){ // gelen stringde bulunan alfabede olmayan karakterleri siler
        while (!( (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') || line[i] == '\0') ){
            for(j = i; line[j] != '\0'; ++j){
                line[j] = line[j+1];
            }
            line[j] = '\0';
        }
       }
 		
    // baştan ve sondan içe doğru karakterleri karşılaştırır
    while (h > l){
        if (str[l++] != str[h--]){	//aynı olmayan karakter varsa palindrom değildir.
	   flag=1;
        }
    }

    if (flag) {
        printf("%s => palindrom değildir.\n", str);
    }    
    else {
        printf("%s => palindromdur.\n", str);
    }

   return 0;
}
