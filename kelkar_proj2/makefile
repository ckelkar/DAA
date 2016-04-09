kelkar_pa2_stra.exe kelkar_pa2_floyd.exe kelkar_pa2_tro.exe:kelkar_pa2_stra.o kelkar_pa2_floyd.o kelkar_pa2_tro.o
	gcc kelkar_pa2_stra.o -o kelkar_pa2_stra.exe
	gcc kelkar_pa2_floyd.o -o kelkar_pa2_floyd.exe
	gcc kelkar_pa2_tro.o -o kelkar_pa2_tro.exe -lm
	
kelkar_pa2_stra.o:kelkar_pa2_stra.c
	gcc -c kelkar_pa2_stra.c
kelkar_pa2_floyd.o:kelkar_pa2_floyd.c
	gcc -c kelkar_pa2_floyd.c
kelkar_pa2_tro.o:kelkar_pa2_tro.c
	gcc -c -lm kelkar_pa2_tro.c 
	
clean:
	rm kelkar_pa2_stra.exe kelkar_pa2_floyd.exe kelkar_pa2_tro.exe kelkar_pa2_tro.o kelkar_pa2_floyd.o kelkar_pa2_stra.o 
