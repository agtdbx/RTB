TARGET = RTB

CC = g++

SRC = 	src/main.cpp \
		src/Background.cpp \
		src/Button.cpp \
		src/Camera.cpp \
		src/Functions.cpp \
		src/Game.cpp \
		src/Map.cpp \
		src/Menu.cpp \
		src/Personnage.cpp \
		src/Select.cpp \
		src/Switch.cpp \
		src/Tuile.cpp \
		src/Zone.cpp

INCLUDE = 	-I include/ \
			-I src/jsoncpp-src-0.5.0/include

SDL_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

JSON_FLAGS = -ljsoncpp


bin/$(TARGET) : $(SRC)
	$(CC) -o $@ $(INCLUDE) $^ $(SDL_FLAGS) $(JSON_FLAGS)


run : bin/$(TARGET)
	bin/$(TARGET)

clean :
	rm -f bin/$(TARGET)

re : clean bin/$(TARGET)

install :
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
	sudo apt-get install libjsoncpp-dev


.PHONY: run clean re install