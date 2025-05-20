CC = gcc

# ALLEGRO = allegro64

ifdef ALLEGRO
CFLAGS = -I${ALLEGRO}/include 
LDFLAGS = -L${ALLEGRO}/lib 
endif

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio functions/moving.c functions/colision.c

TARGETS = output/main

all: ${TARGETS}
	./${TARGETS}

output/main: main.c | output
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS} ${LDLIBS}

output:
	mkdir -p output

clean:
	rm -rf output
