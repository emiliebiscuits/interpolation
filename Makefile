ifeq ($(OS),Windows_NT)
	CFLAGS = 	-W -Wall -g \
				-Isrc \
				-Iextern/SDL2_mingw/SDL2-2.0.3/include \
				-Iextern/SDL2_mingw/SDL2-2.0.3/include/SDL2 \
				-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include \
				-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 \
				-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include \
				-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2
	LDFLAGS =   -L/usr/lib \
				-Lbin \
				extern/SDL2_mingw/libmingw32.a \
				extern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib/libSDL2main.a \
				extern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib/libSDL2.dll.a \
				extern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib/libSDL2_image.dll.a \
				extern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib/libSDL2_ttf.dll.a
else
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CFLAGS = 	-W -Wall -g -O2 \
				-Isrc \
				-Iextern/SDL2_mac/SDL2.framework/Versions/A/Headers/ \
				-Iextern/SDL2_mac/SDL2.framework/Versions/A/Headers/SDL2 \
				-Iextern/SDL2_mac/SDL2_image.framework/Versions/A/Headers \
				-Iextern/SDL2_mac/SDL2_ttf.framework/Versions/A/Headers
	LDFLAGS =   -L/usr/lib \
				-Lbin \
				extern/SDL2_mac/SDL2.framework/Versions/A/SDL2 \
				extern/SDL2_mac/SDL2_image.framework/Versions/A/SDL2_image \
				extern/SDL2_mac/SDL2_ttf.framework/Versions/A/SDL2_ttf \
				-rpath @executable_path/../extern/SDL2_mac \
				#-lSDL2 -lSDL2_ttf -lSDL2_image
else
	CFLAGS = 	-W -Wall -g -O2 \
				-Isrc \
				-I/usr/include/SDL2

	LDFLAGS =   -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_image
endif
endif

SRC=src/
OBJ=obj/
BIN=bin/
NAME=exec/myprog
CC=g++
TEST_NAME=unittest.out
OPTIONS=-Wextra -pedantic -std=c++11 -Wzero-as-null-pointer-constant -Wunreachable-code

DEVLIBS=
OBJECTS=$(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(wildcard $(SRC)*.cpp))
OBJECTS_TEST=$(SRC)unittest.c
INCLUSION=$(SRC)Point.hpp $(SRC)Simplex.hpp $(SRC)Matrice.hpp $(SRC)LecteurFichier.hpp $(SRC)Grapic.h $(SRC)Grapic_func.h $(SRC)Application.hpp


all: install $(NAME)
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(OPTIONS) $(DEVLIBS) -o $(NAME) $(LDFLAGS)

$(OBJ)main.o: $(INCLUSION) $(SRC)PointValue.hpp
$(OBJ)Grapic_func.o: $(SRC)Grapic_func.h $(SRC)Grapic.h
$(OBJ)Grapic.o: $(SRC)Grapic.h
$(OBJ)AffichagePoint.o: $(SRC)AffichagePoint.hpp
$(OBJ)LecteurFichier.o: $(SRC)LecteurFichier.hpp

$(OBJ)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(OPTIONS) $(LDFLAGS)

clean:
	rm -rf $(OBJ)*.o $(NAME) $(SRC)unittest.cc $(BIN)$(TEST_NAME)

test: parse compute throw

parse:
	./$(SRC)unitest.pl $(OBJECTS_TEST)

compute: $(OBJ)unittest.o
	@echo "Compilation du fichier de test !"
	$(CC) $^ $(OPTIONS) $(DEVLIBS) -o $(BIN)$(TEST_NAME)

# à maintenir ici !
$(OBJ)unittest.o : $(SRC)unitest.cc $(INCLUSION)
	@echo "Lancement des tests !"
	$(CC) -o $@ -c $< $(OPTIONS)

throw:
	./$(BIN)$(TEST_NAME)

test2: clean all test

install:
	@mkdir -p obj
	@mkdir -p exec
	@mkdir -p bin

exec: all
	./$(NAME)
