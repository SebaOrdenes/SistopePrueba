ejemplo_out = pipeline
ejemplo_headers = $(wildcard ./INCLUDE/*.h)
ejemplo_source =$(wildcard ./SOURCECODE/*.c) 
ejemplo_objects = $(ejemplo_source:.c=.out)

CC=gcc
CFLAGS = -Wall 
LIBS = -lm
JPEG = -ljpeg
depends = .depends


build: $(ejemplo_out)
build: $(ejemplo_objects)

$(ejemplo_out):
	$(CC) $(CFLAGS) -o $@ main.c $(JPEG)

$(ejemplo_objects) : 
	$(CC) $(CFLAGS) -o $@ $*.c $(JPEG)



$depends: $(ejemplo_source) $(ejemplo_headers)
	@$(CC) -MM $(ejemplo_source) > $@
clean:
	$(RM) $(ejemplo_out) $(ejemplo_objects) $(zipfile) $(depends)

.PHONY: build zip clean

sinclude $(depends)
