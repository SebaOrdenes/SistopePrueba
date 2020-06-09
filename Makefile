ejemplo_out = pipeline

ejemplo_headers = Etapa0.h Etapa1.h Etapa2.h Etapa3.h Etapa4.h Etapa5.h Etapa6.h
ejemplo_source = $(ejemplo_headers:.h=.c) main.c
ejemplo_objects = $(ejemplo_source:.c=.o)


CC=gcc
CFLAGS = -Wall
LIBS = -lm
JPEG = -ljpeg
depends = .depends

build: $(ejemplo_out)

$(ejemplo_out) : $(ejemplo_objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(JPEG)

$(objects):
	$(CC) $(CFLAGS) -c -o $@ $*.c

$depends: $(ejemplo_source) $(ejemplo_headers)
	@$(CC) -MM $(ejemplo_source) > $@

clean:
	$(RM) $(ejemplo_out) $(ejemplo_objects) $(zipfile) $(depends)

.PHONY: build zip clean

sinclude $(depends)
