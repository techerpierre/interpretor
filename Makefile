.PHONY: build run

build:
	mkdir -p .dist
	g++ src/*.cpp -o .dist/interpeter

run:
	./.dist/interpeter