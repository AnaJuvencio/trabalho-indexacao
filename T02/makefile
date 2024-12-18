ORI_T02: ORI_T02.o
	gcc ORI_T02.o -o ORI_T02 -Wall

ORI_T02_HEADER.o: ORI_T02_HEADER.h ORI_T02_HEADER.c
	gcc -c ORI_T02_HEADER.c -Wall

ORI_T02.o: ORI_T02.c ORI_T02_HEADER.o
	gcc -c ORI_T02.c -Wall

clean:
	rm ORI_T02 *.o
