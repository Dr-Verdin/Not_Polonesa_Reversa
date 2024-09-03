all: item.o Pilha.o rpn.o
	gcc item.o Pilha.o rpn.o -o rpn -std=c99 -Wall
item.o:
	gcc -c item.c -o item.o
Pilha.o:
	gcc -c Pilha.c -o Pilha.o
rpn.o:
	gcc -c rpn.c -o rpn.o
clean:
	rm *.o rpn
run: all
	./rpn