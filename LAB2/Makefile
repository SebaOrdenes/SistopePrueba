ejemplo_out = pipeline
ejemplo_out1 = ./SOURCECODE/Etapa1.out
ejemplo_out2 = ./SOURCECODE/Etapa2.out
ejemplo_out3 = ./SOURCECODE/Etapa3.out
ejemplo_out4 = ./SOURCECODE/Etapa4.out
ejemplo_out5 = ./SOURCECODE/Etapa5.out
ejemplo_out6 = ./SOURCECODE/Etapa6.out
ejemplo_headers = $(wildcard ./INCLUDE/*.h)
ejemplo_source =$(wildcard ./SOURCECODE/*.c) 


CC=gcc
CFLAGS = -Wall 
LIBS = -lm
JPEG = -ljpeg
depends = .depends

build: $(ejemplo_out1)
build: $(ejemplo_out2)
build: $(ejemplo_out3)
build: $(ejemplo_out4)
build: $(ejemplo_out5)
build: $(ejemplo_out6)
build: $(ejemplo_out)

$(ejemplo_out1): ./SOURCECODE/Etapa1.c
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/Etapa1.c $(JPEG) 

$(ejemplo_out2): ./SOURCECODE/Etapa2.c
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/Etapa2.c $(JPEG) 

$(ejemplo_out3): ./SOURCECODE/Etapa3.c
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/Etapa3.c $(JPEG) 

$(ejemplo_out4): ./SOURCECODE/Etapa4.c
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/Etapa4.c $(JPEG) 

$(ejemplo_out5): ./SOURCECODE/Etapa5.c
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/Etapa5.c $(JPEG)

$(ejemplo_out6): ./SOURCECODE/Etapa6.c
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/Etapa6.c $(JPEG) 

$(ejemplo_out): ./SOURCECODE/main.o
	$(CC) $(CFLAGS) -o  $@ ./SOURCECODE/main.o $(LIBS) $(JPEG) 

./SOURCECODE/main.o : ./SOURCECODE/main.c

$depends: $(ejemplo_source) $(ejemplo_headers)
	@$(CC) -MM $(ejemplo_source) > $@
clean:
	$(RM) $(ejemplo_out) ./SOURCECODE/main.o $(ejemplo_out1) $(ejemplo_out2) $(ejemplo_out3) $(ejemplo_out4) $(ejemplo_out5) $(ejemplo_out6) $(ejemplo_objects) $(zipfile) $(depends)

.PHONY: build zip clean

sinclude $(depends)
