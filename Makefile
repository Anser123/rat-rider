# Replace this with the path you get from `brew info sfml`
SFML_PATH = /opt/homebrew/Cellar/sfml@2/2.6.2_1
BOX2D_PATH = /Users/anserabbas/box2d

# Replace "src" with the name of the folder where all your cpp code is
# cppFileNames := $(shell find ./src -type f -name "*.cpp")
cppFileNames := $(shell find ./src -type f -name "*.cpp")

all: compile

compile:	
	mkdir -p bin
	g++ -std=c++17 $(cppFileNames) -I$(SFML_PATH)/include -I$(BOX2D_PATH)/include -o main -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -L$(BOX2D_PATH)/build/bin -lbox2d
