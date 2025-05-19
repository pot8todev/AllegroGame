CC = gcc

# ALLEGRO = allegro64

ifdef ALLEGRO
CFLAGS = -I${ALLEGRO}/include 
LDFLAGS = -L${ALLEGRO}/lib 
endif

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio moving.c

TARGETS = main

all: ${TARGETS}
	./${TARGETS}

${TARGETS}: ${TARGETS}.c

clean:
	rm ${TARGETS}
