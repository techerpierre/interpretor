TARGET = .dist/interpeter
SOURCE = src/*.cpp \
	src/core/*.cpp \
	src/lexer/*.cpp \
	src/ast/*.cpp \
	src/parser/*.cpp \
	src/interpreter/*.cpp \
	src/utils/*.cpp 

.PHONY: build run

build:
	mkdir -p .dist
	g++ $(SOURCE) -o $(TARGET)

run:
	./$(TARGET)