CFLAGS=-std=c99 -fstack-protector-all

progr:
	gcc $(CFLAGS) -c arvoreBinaria.c -o arvoreBinaria.o 
	gcc $(CFLAGS) -c retangulo.c -o retangulo.o 
	gcc $(CFLAGS) -c arvoreKd.c -o arvoreKd.o 
	gcc $(CFLAGS) -c listaDup.c -o listaDup.o
	gcc $(CFLAGS) -c path.c -o path.o 
	gcc $(CFLAGS) -c svg.c -o svg.o 
	gcc $(CFLAGS) -c circulo.c -o circulo.o 
	gcc $(CFLAGS) -c qry.c -o qry.o 
	gcc $(CFLAGS) -c leituraArquivos.c -o leituraArquivos.o 
	gcc $(CFLAGS) -c txt.c -o txt.o 
	gcc $(CFLAGS) -c calculos.c -o calculos.o 
	gcc $(CFLAGS) -c visibilidade.c -o visibilidade.o 
	gcc $(CFLAGS) main.c listaDup.o retangulo.o path.o svg.o qry.o leituraArquivos.o circulo.o arvoreKd.o arvoreBinaria.o txt.o calculos.o visibilidade.o -g -lm -o progr $(CFLAGS)

clean:
	rm *.o
	rm progr
