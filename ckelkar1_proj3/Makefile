prim.out kruskal.out lcs.out:prim.o kruskal.o lcs.o
	gcc prim.o -o prim.out
	gcc kruskal.o -o kruskal.out
	gcc lcs.o -o lcs.out
	
prim.o:prim.c
	gcc -c prim.c
kruskal.o:kruskal.c
	gcc -c kruskal.c
lcs.o:lcs.c
	gcc -c lcs.c 
	
clean:
	rm prim.out kruskal.out lcs.out prim.o kruskal.o lcs.o 
