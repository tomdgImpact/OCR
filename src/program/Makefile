# Makefile
CC = gcc -fsanitize=address -rdynamic
CPPFLAGS = -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -Werror -std=c99 -O3 -g -I../../include
LDFLAGS =
LDLIBS = -lm `pkg-config --libs gtk+-3.0 gmodule-2.0` `pkg-config --libs sdl` -lSDL_image

SRC = matrix_xor.c xor.c sdl_tools.c grayscale.c matrix_tools.c matrix.c  noise_cancelling.c  save.c  sdl_tools.c binarization.c  characterRecognition.c  enhancement.c  finalrotate.c segmentation.c  segmentation_tools.c main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

-include ${DEP}
