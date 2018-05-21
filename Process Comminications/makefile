CC=gcc
CFLAGS=-c -Wall

all: toplam islem nkup nkupplus

toplam: toplam.c
	$(CC) toplam.c -o toplam

islem: islem.c
	$(CC) islem.c -o islem

nkup: nkup.c 
	$(CC) nkup.c -o nkup

nkupplus: nkupplus.c
	$(CC) nkupplus.c -o nkupplus -lm

clean: 
	rm -rf *o toplam
